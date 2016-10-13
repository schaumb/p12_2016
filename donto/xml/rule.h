#ifndef RULE_H
#define RULE_H

#include <deque>
#include <string>
#include <boost/property_tree/ptree.hpp>

class rule
{
    using ptree = boost::property_tree::ptree;
public:
    enum class Type { ADDITIVE, EQUAL, GREATER, LESS };
    static const char* typeToConstCharPtr(Type type);
private:
    Type type;
    std::string tag;
    std::deque<std::string> args;
    
public:
    Type getType() const;
    const std::string& getTag() const;
    const std::deque<std::string>& getArgs() const;
    static bool isValid(const std::string& line, rule& outArg, bool& badFile);
    
    rule();
    rule(Type type, std::string&& tag, std::deque<std::string>&& args);
    
    bool operator()(const ptree* p1, const ptree* p2) const
    {
        for(std::string arg : args)
        {
            double d1 = std::stod(p1->get_child(getTag() + ".<xmlattr>." + arg).data());
            double d2 = std::stod(p2->get_child(getTag() + ".<xmlattr>." + arg).data());
            
            if(d1 != d2)
                return d1 < d2; 
        }
        
        return p1 < p2;
    }
};

#endif // RULE_H
