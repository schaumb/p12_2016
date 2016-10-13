//
// Created by Komonyi on 2016.10.13..
//

#include "Sample.hpp"

#include <iostream>

void Sample::setLabel(int l)
{
    this->label = l;
}

int Sample::getLabel()
{
    return this->label;
}

void Sample::addPixel(int p)
{
    if(p > 0)
    {
        if(this->trimLeft == -1 || this->x < this->trimLeft) this->trimLeft = this->x;
        if(this->trimRight == -1 || this->x > this->trimRight) this->trimRight = this->x;
        if(this->trimTop == -1 || this->y < this->trimTop) this->trimTop = this->y;
        if(this->trimBottom == -1 || this->y < this->trimBottom) this->trimBottom = this->y;
    }

    this->pixels[this->x][this->y] = p;

    this->addAveragePixel(this->x - 1, this->y - 1, p);
    this->addAveragePixel(this->x - 1, this->y, p);
    this->addAveragePixel(this->x - 1, this->y + 1, p);
    this->addAveragePixel(this->x, this->y - 1, p);
    this->addAveragePixel(this->x, this->y, p);
    this->addAveragePixel(this->x, this->y + 1, p);
    this->addAveragePixel(this->x + 1, this->y - 1, p);
    this->addAveragePixel(this->x + 1, this->y, p);
    this->addAveragePixel(this->x + 1, this->y + 1, p);

    this->x++;
    if(this->x == 28)
    {
        this->x = 0;
        this->y++;
    }
}

int Sample::getPixel(int x, int y)
{
    return this->pixels[x][y];
}

void Sample::addAveragePixel(int x, int y, int p)
{
    if(x >= 0 && x < 28 && y >= 0 && y < 28)
        this->averagePixels[x][y] += p;
}

int Sample::getAveragePixel(int x, int y)
{
    return this->averagePixels[x][y];
}

int Sample::compare(Sample &a, Sample &b)
{
    int maxDifference = -1;

    for(unsigned int i = 0; i < 28; i++)
    {
        for(unsigned int j = 0; j < 28; j++)
        {
            int current = std::abs(a.getAveragePixel(i, j) - b.getAveragePixel(i, j));

            if(maxDifference == -1 || maxDifference < current)
            {
                maxDifference = current;
            }
        }
    }

    return maxDifference;
}