#ifndef SAMPLE_HPP
#define SAMPLE_HPP

#include <vector>
#include <opencv/cv.h>

#include "Histogram.hpp"

const int HISTOGRAM_SIZE = 8;
const int PATCH_WIDTH = 80;
const int PATCH_HEIGHT = 200;

class Sample {
    std::vector <std::vector <Histogram <HISTOGRAM_SIZE> > > histogram;

  public:
    Sample(cv::Mat image);

    int maximalShift() const;
    std::vector <double> getDescriptor(int x) const;
};

#endif  // PEDESTRIAN_SAMPLE_HPP
