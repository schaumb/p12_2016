#ifndef XML_COMPOSER_H
#define XML_COMPOSER_H

#include "my_option_parser.h"
#include "rule.h"
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <unordered_map>
#include <set>

class xml_composer
{
    using ptree = boost::property_tree::ptree;
    my_option_parser::options options;

    std::vector<ptree> xmls; 
    std::unordered_map<std::string, rule> rules;
    ptree output;
    
    ptree select(std::set<const ptree*, rule>& trees) const;
    rule getRule(const std::string& key) const;
    void merge(const std::vector<ptree>& inputNodes, ptree& outputNode);
public:
    xml_composer(const my_option_parser::options options);
    
    bool readFiles();
    bool readRuleFile();
    bool writeComposedRuleFile();
    void compose();
};

#endif // XML_COMPOSER_H
