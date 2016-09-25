#include <iostream>
#include <string>
#include "lodepng.h"
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <algorithm>
#include <math.h>
#include <tuple>
#include <list>

int getPixel(std::vector<unsigned char> &img, int x, int y, int width)
{
    return int(img[(y * width + x) * 4]) * int(img[(y * width + x) * 4 + 1]) * int(img[(y * width + x) * 4 + 2]);
}

int main() {

    std::string filename;

    std::cin >> filename;

    std::vector<unsigned char> image;
    unsigned width, height;

    unsigned error = lodepng::decode(image, width, height, filename);

    if(error)
    {
        std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
    }
    else
    {
        unsigned int size = atoi(filename.substr(0, filename.find_last_of('.')).c_str());
        unsigned int squareWidth = ceil(double(width) / double(size));
        unsigned int squareHeight = ceil(double(height) / double(size));

        std::vector<std::vector<unsigned int> > squares(size, std::vector<unsigned int>(size, 0));

        std::cout << "Width: " << width << std::endl;
        std::cout << "Height: " << height << std::endl;
        std::cout << "Size: " << size << std::endl;

        for(unsigned int i = 0; i < squareWidth; i++)
        {
            for(unsigned int j = 0; j < squareHeight; j++)
            {

                if((i + 1) * size - 1 >= width || (j + 1) * size - 1 >= height ||
                        getPixel(image, (i + 1) * size - 1, (j + 1) * size - 1, width) != 0)
                {
                    //std::cout << i << ":" << j << std::endl;
                    std::vector<std::list<std::tuple<int, int> > > columns;
                    columns.reserve(size * 2 - 1);

                    for(unsigned int a = 0; a < size * 2 - 1; a++)
                    {
                        std::list<std::tuple<int, int> > column;
                        std::tuple<int, int> last(1, 0);
                        for(unsigned int b = 0; b < size * 2 - 1; b++)
                        {
                            if(i * size + a < width && j * size + b < height)
                            {
                                if(getPixel(image, i * size + a, j * size + b, width) == 0)
                                {
                                    if(std::get<0>(last) == 0)
                                    {
                                        std::get<1>(last)++;
                                    }
                                    else
                                    {
                                        if(std::get<1>(last) > 0)
                                            column.push_back(last);

                                        std::get<0>(last) = 0;
                                        std::get<1>(last) = 1;
                                    }
                                }
                                else
                                {
                                    if(std::get<0>(last) == 1)
                                    {
                                        std::get<1>(last)++;
                                    }
                                    else
                                    {
                                        column.push_back(last);

                                        std::get<0>(last) = 1;
                                        std::get<1>(last) = 1;
                                    }
                                }
                            }
                        }
                        column.push_back(last);

                        columns.push_back(column);
                    }

                    for(unsigned int e = 0; e < size; e++)
                    {
                        for(unsigned int f = 0; f < size; f++)
                        {
                            //std::cout << "isBlack: " << e << ":" << f << std::endl;
                            bool isBlack = false;
                            for(unsigned int g = 0; g < size && !isBlack; g++)
                            {
                                unsigned int position = 0;
                                //std::cout << "oszlop: " << e + g << std::endl;
                                auto it = columns[e + g].begin();
                                while (it != columns[e + g].end() && !isBlack)
                                {
                                    //std::cout << "position: " << position << "; f: " << f << "; color: " << std::get<0>(*it) << "; count: " << std::get<1>(*it) << std::endl;
                                    if(position > f)
                                        break;

                                    //std::cout << "black: " << e << ":" << f << std::endl;
                                    if(f >= position && f < position + std::get<1>(*it) && std::get<0>(*it) == 0)
                                    {
                                        isBlack = true;
                                    }

                                    position += std::get<1>(*it);

                                    it++;
                                }
                            }

                            if(isBlack)
                            {
                                squares[e][f]++;
                                //std::cout << "black: " << e << ":" << f << std::endl;
                            }
                        }
                    }

                }

            }
        }

        unsigned int x = 0;
        unsigned int y = 0;
        int min = -1;
        for(unsigned int e = 0; e < size; e++)
        {
            for (unsigned int f = 0; f < size; f++)
            {
                if(min == -1 || squares[e][f] < min)
                {
                    x = e;
                    y = f;
                    min = squares[e][f];
                }
            }
        }

        std::vector<unsigned char> solution;
        solution.reserve(width * height * 4 + squareWidth * squareHeight * 2 * size * 4);


        unsigned int w = ceil(double(width - x) / double(size)), h = ceil(double(height - x) / double(size));
        for(unsigned int b = 0; b < height; b++)
        {
            if(b % size == y)
            {
                for (unsigned int d = 0; d < width; d++)
                {
                    if(d % size == x)
                    {
                        solution.push_back(255);
                        solution.push_back(0);
                        solution.push_back(0);
                        solution.push_back(255);
                    }

                    solution.push_back(255);
                    solution.push_back(0);
                    solution.push_back(0);
                    solution.push_back(255);
                }
            }

            for(unsigned int a = 0; a < width; a++)
            {
                if(a % size == x)
                {
                    solution.push_back(255);
                    solution.push_back(0);
                    solution.push_back(0);
                    solution.push_back(255);
                }

                for(unsigned int c = 0; c < 4; c++)
                {
                    solution.push_back(image[(b * width + a) * 4 + c]);
                }
            }
        }

        std::cout << solution.size() << std::endl;
        std::cout << "w: " << width + w << "; h: " << height + h << std::endl;

        error = lodepng::encode(filename.substr(0, filename.find_last_of('.')) + "_solution.png", solution, width + w, height + h);

        //if there's an error, display it
        if(error) std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;

        std::cout << "Megoldas: " << x << ":" << y << std::endl;
    }


    return 0;
}