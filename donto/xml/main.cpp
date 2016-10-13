#include <iostream>
#include <vector>
#include <algorithm>
#include <boost/filesystem/operations.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include "my_option_parser.h"
#include "xml_composer.h"

int main(int argc, char** argv)
{

    my_option_parser parser(argc, argv);
    
    // step 1
    if(!parser.parse()) {
        return parser.printWhyAndReturn(std::cerr);
    }
    
    const my_option_parser::options& parsedOptions = parser.getOptions();
    
    if(!std::all_of(parsedOptions.xmlFiles.begin(), parsedOptions.xmlFiles.end(), 
        [](auto& fileName){ return boost::filesystem::exists(fileName); }) || 
        !boost::filesystem::exists(parsedOptions.xsdFile) || 
        (!parsedOptions.ruleFile.empty() && !boost::filesystem::exists(parsedOptions.ruleFile)))
    {
        std::cerr << "One or more input file is not exist" << std::endl;
        return 2;
    }
    
    // step 2
    xml_composer composer(parsedOptions);
    
    if(!composer.readFiles())
    {
        std::cerr << "input files not contains the expected format" << std::endl;
        return 3;
    }
    
    // step 3
    
    if(!composer.readRuleFile())
    {
        std::cerr << "rule files not contains the expected format" << std::endl;
        return 3;
    }
    
    
    // step 4
    
    composer.compose();
    
    // step 5
    
    if(!composer.writeComposedRuleFile())
    {
        std::cerr << "cannot able to write output file" << std::endl;
        return 4;
    }
   
    return 0;
}
