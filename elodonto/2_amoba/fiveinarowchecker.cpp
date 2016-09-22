#include "fiveinarowchecker.h"
#include <algorithm>

std::vector<std::vector<FiveInARowChecker::FieldType>> FiveInARowChecker::readFieldsFromFile(std::istream&& file)
{
    std::vector<std::vector<FieldType>> result;

    for (const std::string& line : readTokens(file, '\n'))
    {
        result.push_back(readFieldsFromLine(std::istringstream(line)));
    }

    return result;
}

std::vector<FiveInARowChecker::FieldType> FiveInARowChecker::readFieldsFromLine(std::istream&& input)
{
    std::vector<FieldType> result;

    for (const std::string& fieldString : readTokens(input, ';'))
    {
        char fieldCharRepr = fieldString.c_str()[0];
        switch(fieldCharRepr)
        {
        case 'X': case 'O': break;
        default: fieldCharRepr = ' ';
        }

        result.push_back(FieldType(fieldCharRepr));
    }

    return result;
}

std::string FiveInARowChecker::getMessage()
{
    for(int i = 0; i < fields.size() && !forceEnd; ++i)
    {
        for(int j = 0; j < fields[i].size() && !forceEnd; ++j)
        {
            if(fields[i][j] == FieldType::UNKNOWN)
                continue;

            ++countOfElements[fields[i][j]];

            checkLine(i, j, 1, 1); // main diagonal
            checkLine(i, j, 1, 0); // vertical
            checkLine(i, j, 0, 1); // horizontal
            checkLine(i, j, 1, -1); // antidiagonal
        }
    }

    using namespace std::string_literals;

    if(forceEnd)
    {
        return "Hibas jatek - "s + forceEndReason;
    }
    else if(possibleLastMoveIndices.empty() || winner == FieldType::UNKNOWN)
    {
        return "Hibas jatek - nincs/nem egyertelmu nyero allapot"s;
    }
    else if(countOfElements[FieldType::X] != countOfElements[FieldType::O] &&
        ((winner == FieldType::X && countOfElements[FieldType::X] != countOfElements[FieldType::O] + 1) ||
        (winner == FieldType::O && countOfElements[FieldType::O] != countOfElements[FieldType::X] + 1)))
    {
        return "Hibas jatek - nem megfelelo mennyisegu elem a jatekban"s;
    }
    return "A jatek megfelelo, a nyertes: "s + static_cast<char>(winner);
}

void FiveInARowChecker::checkLine(int fromX, int fromY, int deltaX, int deltaY)
{
    // if previous field was the same type of field, then it's already checked - nothing to do
    if(isValidIndex(fromX - deltaX, fromY - deltaY) && fields[fromX][fromY] == fields[fromX - deltaX][fromY - deltaY])
    {
        return;
    }

    int count = countOfEquals(fromX, fromY, deltaX, deltaY);

    if(count < 5)
    {
        return;
    }
    else if(count > 9)
    {
        forceEnd = true;
        forceEndReason = "9-nel hosszabb egybefuggo van, ami lehetetlen egy jatek folyaman";
        return;
    }

    std::set<std::pair<std::size_t, std::size_t>> thisPossibleLastMoveIndices;
    for(std::size_t c = 0; c < count; ++c)
    {
        thisPossibleLastMoveIndices.insert(std::make_pair(fromX + c * deltaX, fromY + c * deltaY));
    }

    addPosibleLastMoves(std::move(thisPossibleLastMoveIndices));
}

int FiveInARowChecker::countOfEquals(int fromX, int fromY, int deltaX, int deltaY) const
{
    std::size_t count = 1;

    while(isValidIndex(fromX + count * deltaX, fromY + count * deltaY) &&
        fields[fromX][fromY] == fields[fromX + count * deltaX][fromY + count * deltaY])
    {
        ++count;
    }

    return count;
}

void FiveInARowChecker::addPosibleLastMoves(std::set<std::pair<std::size_t, std::size_t>>&& otherPossibleLastMoves)
{
    if(possibleLastMoveIndices.empty())
    {
        possibleLastMoveIndices = std::move(otherPossibleLastMoves);
        winner = fields[possibleLastMoveIndices.begin()->first][possibleLastMoveIndices.begin()->second];
        return;
    }

    for(auto it = possibleLastMoveIndices.begin(); it != possibleLastMoveIndices.end();)
    {
        if(!otherPossibleLastMoves.count(*it))
        {
            possibleLastMoveIndices.erase(it++);
        }
        else
        {
            ++it;
        }
    }

    if(possibleLastMoveIndices.empty())
    {
        forceEnd = true;
        forceEndReason = "tobb, egy ponton nem erintkezo gyozelmi vonal letezik";
        return;
    }
}

bool FiveInARowChecker::isValidIndex(int x, int y) const
{
    return 0 <= x && x < fields.size() && 0 <= y && y < fields[x].size();
}
