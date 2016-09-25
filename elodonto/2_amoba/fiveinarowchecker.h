#ifndef FIVEINAROWCHECKER_H
#define FIVEINAROWCHECKER_H

#include <vector>
#include <set>
#include <map>
#include <string>
#include <sstream>

std::vector<std::string> readTokens(std::istream& input, char delimiter);

class FiveInARowChecker
{
    enum class FieldType : char { UNKNOWN = ' ', X = 'X', O = 'O' };

    std::vector<std::vector<FieldType>> fields;
    std::map<FieldType, std::size_t> countOfElements;

    std::set<std::pair<std::size_t, std::size_t>> possibleLastMoveIndices;
    FieldType winner;

    std::string forceEndReason;
    bool forceEnd;

    static std::vector<std::vector<FieldType>> readFieldsFromFile(std::istream&& file);
    static std::vector<FieldType> readFieldsFromLine(std::istream&& input);

    void checkLine(int fromX, int fromY, int deltaX, int deltaY);
    int countOfEquals(int fromX, int fromY, int deltaX, int deltaY) const;
    void addPosibleLastMoves(std::set<std::pair<std::size_t, std::size_t>>&& otherPossibleLastMoves);
    bool isValidIndex(int x, int y) const;

public:
    FiveInARowChecker(std::istream&& file);
    std::string getMessage();
};

#endif // FIVEINAROWCHECKER_H
