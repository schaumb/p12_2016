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
    while(std::getline(file, tmp) && (int)tmp.size() >= width)
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
    int i = 0;
    do
    {
        ++patternHeight;
        for(char c : line)
        {
            if(c == '\r') continue;
            if(c == '1')
                pattern1s[i] = true;
            if(c == '0')
                pattern0s[i] = true;
            ++i;
        }
        if(i % width != 0)
        {
            i += width - (i % width);        
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
        for(int i = 0; i < height; ++i)
        {
            for(int j = 0; j < width; ++j)
            {
                nextCellulars[i * width + j] = nextCellularAt(i, j);
            }
        }
        cellulars = std::move(nextCellulars);
        flippedCellulars = ~cellulars;
        
        std::string result = findPattern();
        
        if(!result.empty()) return std::to_string(t + 1) + "," + result;
        
        flippedCellulars.clear();
    }
    return "0,0,0";
}

std::string CellularAutomataFinder::findPattern() const
{
    boost::dynamic_bitset<> pattern1sCopy = pattern1s;
    boost::dynamic_bitset<> pattern0sCopy = pattern0s;
    
    for(int i = 0; i <= height - patternHeight; ++i)
    {
        for(int j = 0; j <= width - patternWidth; ++j)
        {
            if((cellulars & pattern1sCopy) == pattern1sCopy &&
                (flippedCellulars & pattern0sCopy) == pattern0sCopy)
            {
                return std::to_string(i) + "," + std::to_string(j);
            }
            
            pattern1sCopy <<= 1;
            pattern0sCopy <<= 1;
        }
        pattern1sCopy <<= patternWidth - 1;
        pattern0sCopy <<= patternWidth - 1;
    }
    return "";
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


