#include <iostream>
#include <fstream>
#include "fiveinarowchecker.h"

std::vector<std::string> readTokens(std::istream& input, char delimiter)
{
    std::vector<std::string> result;
    std::string tmp;
    while(std::getline(input, tmp, delimiter))
    {
        result.push_back(std::move(tmp));
    }
    return result;
}

int main(int argc, char* argv[])
{
    std::cerr << "Varakozas ujsor karakterrel elvalasztott fajlnevekre a standard inputon, EOF-ig" << std::endl;
    for(const std::string& fileName : readTokens(std::cin, '\n'))
    {
        std::string message = FiveInARowChecker(std::ifstream(fileName)).getMessage();

        // remove file extension (.csv) and add a text (.txt) suffix
        std::string outputFileName = fileName.substr(0, fileName.find_last_of('.')) + ".txt";

        std::ofstream(outputFileName) << message << std::endl;
        std::cerr << fileName << " kimenete (" << outputFileName << "): " << message << std::endl;
    }
}
