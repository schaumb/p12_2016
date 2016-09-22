#include <iostream>
#include <fstream>
#include "cellularautomatafinder.h"

int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        std::cerr << "Rossz argumentumokkal lett meghivva a program" << std::endl;
        return 1;
    }
    std::ofstream(argv[2]) << CellularAutomataFinder(std::ifstream(argv[1])).find() << std::endl;
}
