#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <string>
#include <vector>

#include "debug.hpp"
#include "LinearSVM.hpp"
#include "PatchPositions.hpp"
#include "Processing.hpp"
#include "Rectangle.hpp"
#include "Sample.hpp"

static void printUsage(const char *programName) {
    std::cout << "Usage:" << std::endl;
    std::cout << "    " << programName << " sample_file [classifier_file]" << std::endl;
    std::cout << std::endl;
    std::cout << "Examples:" << std::endl;
    std::cout << "    1) $ " << programName << " image.png" << std::endl;
    std::cout << "       Read the model from stdout and classify patches from image.png" << std::endl;
    std::cout << "    2) $ " << programName << " image.png model.txt" << std::endl;
    std::cout << "       Read the model from 'model.txt' and classify patches from image.png" << std::endl;
}

int main(int argc, char *argv[]) {
    if (/*argc != 2 &&*/ argc != 3) {  // TODO: non-implemented case
        printUsage(argv[0]);
        exit(EXIT_FAILURE);
    }
    else {
        const char *sampleFile = strdup(argv[1]);
        const char *modelFile = "";
        if (argc == 3) {
            modelFile = strdup(argv[2]);
        }

        try {
            debugInline("Loading image... ");
            cv::Mat image = cv::imread(sampleFile);
            if (!image.data) {
                throw "Cannot load image";
            }
            debug("done.");

            Sample sample(image);

            debugInline("Loading classifier... ");
            LinearSVM classifier(modelFile);
            debug("done.");

            std::vector <int> matches = Processing::processSample(sample, &classifier);
            for (std::vector <int>::iterator it = matches.begin(); it != matches.end(); ++it) {
                cv::rectangle(image, cv::Point(*it, 0), cv::Point(*it + PATCH_WIDTH, PATCH_HEIGHT), cv::Scalar(0, 255, 0));
            }

            cv::imshow("Result", image);
            cv::waitKey();
        }
        catch (const char *e) {
            std::cerr << "Error: " << e << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}
