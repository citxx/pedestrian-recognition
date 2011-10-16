#include <cmath>
#include <iostream>

#include "Chi2Kernel.hpp"
#include "debug.hpp"
#include "Sample.hpp"

const int SQUARE_SIZE = 8;

Sample::Sample(cv::Mat image) {
    if (image.cols < PATCH_WIDTH || image.rows < PATCH_HEIGHT) {
        std::cerr << "Invalid sample image" << std::endl;
        throw "Invalid sample image";
    }
    this->histogram.assign(image.cols + 1, std::vector <Histogram <HISTOGRAM_SIZE> >(image.rows / SQUARE_SIZE));

    cv::Mat rawGray, gray, xGrad, yGrad;
    cv::cvtColor(image, rawGray, CV_RGB2GRAY);
    rawGray.convertTo(gray, CV_64F);

    double mXSobel[3][3] = {
        {-1,  0,  1},
        {-2,  0,  2},
        {-1,  0,  1}
    };
    cv::Mat xSobel(3, 3, CV_64F, mXSobel);
    cv::Mat ySobel = xSobel.t();

    cv::filter2D(gray, xGrad, -1, xSobel);
    cv::filter2D(gray, yGrad, -1, ySobel);
    int trueRows = (image.rows / SQUARE_SIZE) * SQUARE_SIZE;
    for (int row = 0; row < trueRows; row++) {
        double *xRowPtr = xGrad.ptr <double>(row);
        double *yRowPtr = yGrad.ptr <double>(row);
        for (int col = 0; col < xGrad.cols; col++) {
            double angle = atan2(*yRowPtr, *xRowPtr);
            int num = (int)((angle + M_PI) / (2 * M_PI / HISTOGRAM_SIZE)) % HISTOGRAM_SIZE;
            this->histogram[col][row / SQUARE_SIZE][num] += 1;
            xRowPtr++;
            yRowPtr++;
        }
    }

    for (int x = 1; x < (int)this->histogram.size(); x++) {
        for (int y = 0; y < (int)this->histogram[x].size(); y++) {
            this->histogram[x][y] = this->histogram[x][y] + this->histogram[x - 1][y];
        }
    }
}

int Sample::maximalShift() const {
    return (int)this->histogram.size() - PATCH_WIDTH;
}

std::vector <double> Sample::getDescriptor(int x) const {
    std::vector <double> answer;

    for (int sx = 0; sx < PATCH_WIDTH / SQUARE_SIZE; sx++) {
        for (int sy = 0; sy < PATCH_HEIGHT / SQUARE_SIZE; sy++) {
            std::vector <int> hist =
                (this->histogram[x + (sx + 1) * SQUARE_SIZE][sy] -
                this->histogram[x + sx * SQUARE_SIZE][sy]).getVector();
            answer.insert(answer.end(), hist.begin(), hist.end());
        }
    }

    return Chi2Kernel(1, 0.4).transform(answer);
}
