#include "xml_composer.h"
#include <iterator>
#include <exception>
#include <sstream>
#include <set>
#include <map>
#include <boost/algorithm/string.hpp>

xml_composer::xml_composer(const my_option_parser::options options) :
    options(options)
{
    rules["Root"] = rule(rule::Type::EQUAL, "Root", {});
}


bool xml_composer::readFiles()
{
    try
    {
        std::transform(options.xmlFiles.begin(), options.xmlFiles.end(), std::back_inserter(xmls), [](auto& fileName)
        {
            ptree result;
            boost::property_tree::read_xml(fileName, result, boost::property_tree::xml_parser::trim_whitespace);
            return result;
        });
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return false;
    }
    return true;
}

bool xml_composer::readRuleFile()
{
    std::ifstream ruleFile(options.ruleFile);
    std::string line;
    
    while(std::getline(ruleFile, line))
    {
        line = line.substr(0, std::min(line.find('#'), line.find("//")));
        boost::trim(line);
        
        bool badFile = false;
        rule newRule;
        if(rule::isValid(line, newRule, badFile))
        {
            rules[newRule.getTag()] = newRule;
        }
        if(badFile)
        {
            return false;
        }
    }
    return true;
}


bool xml_composer::writeComposedRuleFile()
{
    if(!std::ofstream(options.outputFile).is_open()) return false;
    
    boost::property_tree::xml_writer_settings<char> settings('\t', 1);
    boost::property_tree::write_xml(options.outputFile, output, std::locale(), settings);
    
    return true;
}

rule xml_composer::getRule(const std::string& key) const
{
    auto it = rules.find(key);
    return it != rules.end() ? it->second : rule(rule::Type::ADDITIVE, std::string(key), {});
}

xml_composer::ptree xml_composer::select(std::set<const ptree*, rule>& trees) const
{
    rule r = trees.key_comp();
    if(r.getArgs().empty() || trees.empty()) {
        return {};
    }
    
    switch(r.getType())
    {
    case rule::Type::EQUAL:
        {
            // attribute -> value -> {ptrees} 
            std::map<std::string, std::map<std::string, std::set<const ptree*>>> otherAttr;
            for(auto& ptreePtr : trees)
            {
                for(auto& attr : ptreePtr->get_child(r.getTag() + ".<xmlattr>"))
                {
                    otherAttr[attr.first][attr.second.data()].insert(ptreePtr);
                }
            }
            ptree attrs;
            
            for(auto& attr : otherAttr)
            {
                auto args = r.getArgs();
                bool notRuledArgument = !std::count(args.begin(), args.end(), attr.first);

                // remove not applicable trees
                for(auto& pair : attr.second)
                {
                    for(auto it = pair.second.begin(); it != pair.second.end();)
                    {
                        if(!trees.count(*it))
                        {
                            it = pair.second.erase(it);
                        }
                        else
                        {
                            ++it;
                        }
                    }
                }

                // max search 
                std::string maxAttr;
                int maxi = 0;
                for(auto& p : attr.second)
                {
                    if(maxi < p.second.size())
                    {
                        maxi = p.second.size();
                        maxAttr = p.first;
                    } else if(notRuledArgument && maxi == p.second.size()) {
                        maxAttr = "";
                    }
                }
                
                if(!maxAttr.empty())
                {
                    attrs.push_back({attr.first, ptree(maxAttr)});
                }

                // not ruled argument but more stuff
                if(notRuledArgument && attr.second.size() > 1)
                {
                    for(auto& p : attr.second)
                    {
                        if(p.first != maxAttr)
                        {
                            for(auto ptreePtr : p.second)
                            {
                                trees.erase(ptreePtr);
                            }
                        }
                    }
                }
            }
            
            return attrs;
        }
    case rule::Type::GREATER:
        return (*trees.rbegin())->get_child(r.getTag() + ".<xmlattr>");
    case rule::Type::LESS:
        return (*trees.begin())->get_child(r.getTag() + ".<xmlattr>");
    }
    return {};
}

void xml_composer::merge(const std::vector<ptree>& nodes, ptree& outputNode)
{
    std::map<std::string, std::set<const ptree*, rule>> attributes;
    
    for(const ptree& tree : nodes)
    {
        for(auto& pair : tree)
        {
            auto it = attributes.find(pair.first);
            
            if(it == attributes.end()) 
            {
                it = attributes.insert(attributes.begin(), std::make_pair(pair.first, std::set<const ptree*, rule>(getRule(pair.first))));
            }
            it->second.insert(&tree);
        }
    }
    
    for(auto& pair : attributes)
    {
        if(pair.first == "<xmlcomment>" || pair.first == "<xmlattr>")
        {
            continue;
        }
        
        ptree result;
        rule attrRule = getRule(pair.first);
        
        switch(attrRule.getType())
        {
        case rule::Type::ADDITIVE:
            outputNode.push_back({"<xmlcomment>", ptree(std::string(" Used rule: ") + rule::typeToConstCharPtr(attrRule.getType()) + " ")});
            for(auto& ptreePtr : pair.second)
            {
                for(auto& child : *ptreePtr)
                {
                    if(child.first == pair.first)
                    {
                        outputNode.push_back(child);
                    }
                }
            }
            break;
        default:
            ptree attributes = select(pair.second);
            
            if(pair.second.empty())
            {
                continue;
            }
            
            if(!attributes.empty())
            {
                result.push_back({"<xmlattr>", attributes});            
            }
            
            std::vector<ptree> childs;
            for(auto& ptreePtr : pair.second)
            {
                for(auto& child : *ptreePtr)
                {
                    if(child.first == pair.first)
                    {
                        childs.push_back(child.second);
                    }
                }
            }
            
            merge(childs, result);
            outputNode.push_back({"<xmlcomment>", ptree(std::string(" Used rule: ") + rule::typeToConstCharPtr(attrRule.getType()) + " ")});
            outputNode.push_back({pair.first, result});
            break;
        }
    }
}


void xml_composer::compose()
{
    merge(xmls, output);
}

