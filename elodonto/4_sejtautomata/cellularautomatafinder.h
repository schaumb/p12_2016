#ifndef CELLULARAUTOMATAFINDER_H
#define CELLULARAUTOMATAFINDER_H

#include <string>
#include <sstream>
#include <boost/dynamic_bitset.hpp>
#include <array>

class CellularAutomataFinder
{
    std::array<std::int32_t, 5> rule;
    boost::dynamic_bitset<> cellulars;
    boost::dynamic_bitset<> flippedCellulars;
    std::size_t width, height;
    boost::dynamic_bitset<> pattern1s;
    boost::dynamic_bitset<> pattern0s;
    std::size_t patternWidth, patternHeight;
    std::uint32_t maxIter;
    
    
    void readRule(std::istream& file);
    void readCellulars(std::istream& file);
    void readPattern(std::istream& file);
    
    std::string findPattern() const;
    bool nextCellularAt(int x, int y) const;
    bool cellularValueAt(int x, int y) const;
    bool isValidIndex(int x, int y) const;
public:
    CellularAutomataFinder(std::istream&& file);
    std::string find();
};

#endif // CELLULARAUTOMATAFINDER_H
