#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <functional>

struct Field
{
    enum class FieldType : char { X = 'X', O = 'O', UNKNOWN = ' ' };

    FieldType type = FieldType::UNKNOWN;
    std::size_t mainDiagonal = 0;
    std::size_t vertical = 0;
    std::size_t antidiagonal = 0;
    std::size_t horizontal = 0;
};

template<class IstreamType>
std::vector<std::string> readLines(IstreamType&& input, char delimiter = '\n')
{
    std::vector<std::string> result;
    std::string tmp;
    while(std::getline(input, tmp, delimiter))
    {
        result.push_back(std::move(tmp));
    }
    return result;
}

std::string removeExtension(const std::string& originalFileName)
{
    std::size_t pos = originalFileName.find_last_of('.');
    return pos == std::string::npos ? originalFileName : originalFileName.substr(0, pos);
}

int main()
{
    for(const std::string& fileName : readLines(std::cin))
    {
        std::unordered_map<char, std::size_t> countOfElements { {'X', 0}, {'O', 0} };

        Field::FieldType winner = Field::FieldType::UNKNOWN;
        std::unordered_set<std::size_t> possibleLastMoveIndices;

        std::vector<Field> fields;
        std::size_t sizeY = 0;

        for (const std::string& line : readLines(std::ifstream(fileName)))
        {
            for(const std::string& value : readLines(std::istringstream(line + ";"), ';'))
            {
                Field field;
                switch(value.c_str()[0]) {
                case 'X': case 'O':
                    ++countOfElements[value.c_str()[0]];
                    field.type = Field::FieldType(value.c_str()[0]);

                    if(sizeY != 0) { // has previous line


                    }
                }
                fields.push_back(field);
            }

            if(sizeY == 0)
            {
                sizeY = fields.size();
            }
        }
        std::ofstream output_file (removeExtension(fileName) + ".txt");

        if(possibleLastMoveIndices.empty() || winner == Field::FieldType::UNKNOWN)
        {
            output_file << "hibas jatek - nincs/nem egyertelmu nyero allapot" << std::endl;
        }
        else if(countOfOs != countOfXs &&
            ((winner == Field::FieldType::X && countOfElements['X'] != countOfElements['O'] + 1) ||
            (winner == Field::FieldType::O && countOfElements['O'] != countOfElements['X'] + 1)))
        {
            output_file << "hibas jatek - nem megfelelo mennyisegu elem a jatekban" << std::endl;
        }
        else
        {
            output_file << "A jatek megfelelo, a nyertes: " << static_cast<char>(winner) << std::endl;
        }
    }
}


