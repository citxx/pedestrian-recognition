#ifndef IMAGE_SET_HPP
#define IMAGE_SET_HPP

#include <string>
#include <vector>
#include <opencv/cv.h>

class ImageSet {
    std::string directoryName;

  public:
    ImageSet(std::string directoryName);
    std::vector <std::string> getNames() const;
    cv::Mat getImage(std::string name) const;
};

#endif  // IMAGE_SET_HPP
