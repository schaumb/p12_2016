#include "rule.h"
#include <boost/algorithm/string.hpp>

const char* rule::typeToConstCharPtr(Type type)
{
    switch(type)
    {
    case rule::Type::ADDITIVE:
        return "ADDITIVE";
    case rule::Type::EQUAL:
        return "EQUAL";
    case rule::Type::GREATER:
        return "GREATER";
    case rule::Type::LESS:
        return "LESS";
    default:
        return "UNKNOWN";
    }
}

rule::Type rule::getType() const
{
    return type;
}

const std::string& rule::getTag() const
{
    return tag;
}

const std::deque<std::string>& rule::getArgs() const
{
    return args;
}

rule::rule() {}

rule::rule(Type type, std::string&& tag, std::deque<std::string>&& args) :
    type(type), tag(std::move(tag)), args(std::move(args))
{}

bool rule::isValid(const std::string& line, rule& outArg, bool& badFile)
{
    if(line.empty()) return false;
    
    std::size_t open = line.find("<");
    std::size_t close = line.find(">");
    
    if(open != 0 || close == std::string::npos) 
    {
        std::cout << "open, close"  << open << " " << close << std::endl;
        badFile = true;
        return false;
    }
    
    std::string tagAndAttribute = line.substr(open + 1, close - open - 1);
    boost::split(outArg.args, tagAndAttribute, boost::is_any_of(" "));

    if(outArg.args.empty())
    {
        std::cout << "args empty"  << std::endl;
        badFile = true;
        return false;
    }
    
    outArg.tag = outArg.args.front();
    outArg.args.pop_front();
    
    std::string typeString = line.substr(close + 1);
    boost::trim(typeString);
    
    if(typeString == "ADDITIVE")
    {
        outArg.type = rule::Type::ADDITIVE;
    }
    else if(typeString == "EQUAL" || typeString == "EQUALS")
    {
        outArg.type = rule::Type::EQUAL;
    }
    else if(typeString == "GREATER")
    {
        outArg.type = rule::Type::GREATER;
    }
    else if(typeString == "LESS")
    {
        outArg.type = rule::Type::LESS;
    }
    else
    {
        std::cout << "typestring: "  << typeString  << std::endl;
        badFile = true;
        return false;
    }
    
    return true;
}
