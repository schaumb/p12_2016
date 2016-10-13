#include <iostream>
#include <fstream>
#include <sstream>

#include "Sample.hpp"

int main() {

    std::ifstream inputFile("train2.csv");

    int pixel;
    std::string line, str;

    Sample inputSample;
    while(std::getline(std::cin, str, ','))
    {
        inputSample.addPixel(std::stoi(str));
    }

    int minPixelDifference = -1, minLabel = -1;

    while(inputFile >> line)
    {
        std::stringstream liness(line);
        bool cucc = true;
        Sample currentSample;

        while(std::getline(liness, str, ','))
        {
            if(cucc)
            {
                currentSample.setLabel(std::stoi(str));
                cucc = false;
            }
            else
            {
                currentSample.addPixel(std::stoi(str));
            }
        }

        int pixelDifference = Sample::compare(inputSample, currentSample);

        if(minPixelDifference == -1 || pixelDifference < minPixelDifference)
        {
            minLabel = currentSample.getLabel();
            minPixelDifference = pixelDifference;
        }

    }

    inputFile.close();

    std::cout << "Kesz!" << std::endl;
    std::cout << "Max kulonbseg: " << minPixelDifference << std::endl;
    std::cout << "Cimke: " << minLabel << std::endl;

    return 0;
}