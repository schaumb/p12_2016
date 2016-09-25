#include "cellularautomatafinder.h"
#include <iostream>
#include <boost/algorithm/string.hpp>

CellularAutomataFinder::CellularAutomataFinder(std::istream&& file)
{
    readRule(file);
    readCellulars(file);
    readPattern(file);
    file >> maxIter;
}

void CellularAutomataFinder::readRule(std::istream& file)
{
    for(int i = 0; i < 5; ++i)
    {
        (file >> rule[i]).ignore();
    }
}

void CellularAutomataFinder::readCellulars(std::istream& file)
{
    std::string result;
    do
    {
        std::getline(file, result);
        boost::trim(result);
    }
    while(result.empty());
    
    width = result.size();
    
    std::string tmp;
    while(std::getline(file, tmp) && tmp.size() >= width)
    {
        boost::trim(tmp);
        result = result + tmp;
    }
    height = result.size() / width;
    
    std::reverse(result.begin(), result.end());
    cellulars = boost::dynamic_bitset<>(result);
}

void CellularAutomataFinder::readPattern(std::istream& file)
{
    std::string line;
    do
    {
        std::getline(file, line);
        if(line == "\r") line.clear();
    }
    while(line.empty());
    if(line.back() == '\r') line.pop_back();
    
    patternWidth = line.size();
    patternHeight = 0;
    pattern1s.resize(cellulars.size());
    pattern0s.resize(cellulars.size());
    int patternIndex = 0;
    do
    {
        ++patternHeight;
        for(char c : line)
        {
            if(c == '\r') continue;
            if(c == '1')
                pattern1s[patternIndex] = true;
            if(c == '0')
                pattern0s[patternIndex] = true;
            ++patternIndex;
        }
        if(patternIndex % width != 0)
        {
            patternIndex += width - (patternIndex % width);        
        }
        
        std::getline(file, line);
        if(line == "\r") line.clear();
    }
    while(!line.empty());
}


std::string CellularAutomataFinder::find()
{
    for(std::uint32_t t = 0; t < maxIter; ++t)
    {
        boost::dynamic_bitset<> nextCellulars(cellulars.size());
        boost::dynamic_bitset<> nextFlippedCellulars(cellulars.size());
        
        #pragma omp parallel for if(width > 256)
        for(std::size_t i = 0; i < height; ++i)
        {
            for(std::size_t j = 0; j < width; ++j)
            {
                nextCellulars[i * width + j] = nextCellularAt(i, j);
                nextFlippedCellulars[i * width + j] = !nextCellulars[i * width + j];
            }
        }
        cellulars = std::move(nextCellulars);
        flippedCellulars = std::move(nextFlippedCellulars);

        std::string result = findPattern();

        flippedCellulars.clear();
        
        if(!result.empty()) return std::to_string(t + 1) + "," + result;
    }
    return "0,0,0";
}

std::string CellularAutomataFinder::findPattern() const
{    
    std::string result;
    
    #pragma omp parallel
    for(std::size_t i = 0; i <= height - patternHeight; ++i)
    {
        if(!result.empty())
        {
            continue;
        }
        
        boost::dynamic_bitset<> pattern1sCopy = pattern1s << (i * width);
        boost::dynamic_bitset<> pattern0sCopy = pattern0s << (i * width);
        for(std::size_t j = 0; j <= width - patternWidth && result.empty(); ++j)
        {
            if((cellulars & pattern1sCopy) == pattern1sCopy &&
                (flippedCellulars & pattern0sCopy) == pattern0sCopy)
            {
                #pragma omp critical
                {
                    result = std::to_string(i) + "," + std::to_string(j);
                }
            }
            
            pattern1sCopy <<= 1;
            pattern0sCopy <<= 1;
        }
    }
    return result;
}

bool CellularAutomataFinder::nextCellularAt(int x, int y) const
{
    std::int64_t result{};
    auto addToResult = [&](int deltaX, int deltaY, int ruleIndex)
    {
        if(isValidIndex(x + deltaX, y + deltaY) && cellularValueAt(x + deltaX, y + deltaY))
        {
            result += rule[ruleIndex];
        }
    };
    
    addToResult(-1, 0, 0);
    addToResult(0, 1, 1);
    addToResult(1, 0, 2);
    addToResult(0, -1, 3);
    
    return result >= rule[4];
}

bool CellularAutomataFinder::cellularValueAt(int x, int y) const
{
    return cellulars[x * width + y];
}

bool CellularAutomataFinder::isValidIndex(int x, int y) const
{
    return 0 <= x && x < height && 0 <= y && y < width;
}


