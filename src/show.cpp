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
#include "Rectangle.hpp"
#include "Sample.hpp"

#define ANSWER_PEDESTRIAN 1
#define ANSWER_BACKGROUND -1

#define PATCH_STEP 4

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

            debug("Classifying patches...");
            for (int x = 0; x < sample.maximalShift(); x += PATCH_STEP) {
                int answer = classifier.classify(sample.getDescriptor(x));
                debugInline("\b\b\b\b"); debugInline(x);
                if (answer == ANSWER_PEDESTRIAN) {
                    debugInline("\b\b\b\b"); debugInline("Pedestrian is found at the position "); debug(x);
                    cv::rectangle(image, cv::Point(x, 0), cv::Point(x + PATCH_WIDTH, PATCH_HEIGHT), cv::Scalar(0, 255, 0));
                }
            }
            debug("\b\b\b\b\bDone.");

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
