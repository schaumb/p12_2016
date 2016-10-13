#ifndef MY_OPTION_PARSER_H
#define MY_OPTION_PARSER_H

#include <vector>
#include <string>
#include <boost/program_options.hpp>

class my_option_parser
{
public:
    struct options
    {
        std::vector<std::string> xmlFiles;
        std::string xsdFile;
        std::string outputFile;
        std::string ruleFile;
    };

private:
    bool help;
    int argc;
    const char* const* argv;
    std::string why;
    options parsedOptions;
    boost::program_options::options_description optionDescription;
	boost::program_options::variables_map variableMap;

public:
    my_option_parser(int argc, char** argv);
    bool parse();
    int printWhyAndReturn(std::ostream& output) const;
    const options& getOptions() const;
};

#endif // MY_OPTION_PARSER_H
