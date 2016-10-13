//
// Created by Komonyi on 2016.10.13..
//

#ifndef KEZIRAS_FELISMERES_SAMPLE_HPP
#define KEZIRAS_FELISMERES_SAMPLE_HPP

#include <vector>

class Sample {
private:
    std::vector<std::vector<int> > pixels = std::vector<std::vector<int> >(28, std::vector<int> (28));
    std::vector<std::vector<int> > averagePixels = std::vector<std::vector<int> >(28, std::vector<int> (28, 0));

    int trimLeft = -1, trimTop = -1, trimRight = -1, trimBottom = -1;
    int x = 0, y = 0;
    int label = -1;

public:
    //Sample();

    void setLabel(int l);
    int getLabel();

    void addPixel(int p);

    int getPixel(int x, int y);

    int getAveragePixel(int x, int y);
    void addAveragePixel(int x, int y, int p);

    static int compare(Sample &a, Sample &b);
};


#endif //KEZIRAS_FELISMERES_SAMPLE_HPP
