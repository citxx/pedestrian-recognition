#ifndef DEBUG_HPP
#define DEBUG_HPP

#define DEBUG_MODE

#ifdef DEBUG_MODE

#include <iostream>
#include <opencv/highgui.h>
#include <unistd.h>

#define debug(str) (std::cerr << (str) << std::endl)
#define debugInline(str) (std::cerr << (str))
#define debugImage(name, image) { cv::Mat tmp; image.copyTo(tmp); cv::imshow((name), tmp); cv::waitKey(); }

#else

#define debug(str)
#define debugInline(str)
#define debugImage(name, image)

#endif

#endif  // DEBUG_HPP
