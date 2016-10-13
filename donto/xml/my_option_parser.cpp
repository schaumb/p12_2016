#include "my_option_parser.h"
#include <boost/exception/all.hpp>
#include <boost/system/error_code.hpp>

my_option_parser::my_option_parser(int argc, char** argv) :
    argc(argc), argv(argv), optionDescription("aludjunkRa team xml composer arguments")
{
    namespace po = boost::program_options;

    optionDescription.add_options()
        ("xsd,x", po::value<std::string>(&parsedOptions.xsdFile)->required(), "XSD describer file")
        ("input,i", po::value<std::vector<std::string>>(&parsedOptions.xmlFiles)->multitoken()->composing()->required(), "input XML files")
        ("output,o", po::value<std::string>(&parsedOptions.outputFile)->required(), "output file (with path)")
        ("rule,r", po::value<std::string>(&parsedOptions.ruleFile), "rule file")
        ("help,h", po::bool_switch(&help), "This help message");
}

bool my_option_parser::parse()
{
    namespace po = boost::program_options;

    try
    {
        po::parsed_options parsed = po::command_line_parser(argc, argv).options(optionDescription).run();
        store(parsed, variableMap);
        po::notify(variableMap);
        if(parsedOptions.xmlFiles.size() < 2)
        {
            why = "least 2 input file required";
        }
        
        if(help)
        {
            why = "the requested parameters:";
        }
    }
    catch (const std::exception& e)
    {
        why = e.what();
    }
        
    return why.empty();
}

int my_option_parser::printWhyAndReturn(std::ostream& output) const
{
    output << why << std::endl << std::endl;
    optionDescription.print(output);
    output << std::endl << "Example: " << argv[0] << " -i <xml1> <xml2> [xmlX]... -x <xsd> -o <out xml> [-r <rule>] [-h]" << std::endl << std::endl;
    
    output << "Return values: " << std::endl
        << "0 if OK, or help requested" << std::endl
        << "1 if arguments not meet the requirements" << std::endl
        << "2 if input files are not exists" << std::endl
        << "3 if input files not contains the expected format" << std::endl
        << "4 if program has no access to write" << std::endl
        << "-1 not expected error" << std::endl; 
    
    return help ? 0 : 1;
}

const my_option_parser::options& my_option_parser::getOptions() const
{
    return parsedOptions;
}
