#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <string>
#include <vector>

#include "debug.hpp"
#include "ImageSet.hpp"
#include "LinearSVM.hpp"
#include "PatchPositions.hpp"
#include "Rectangle.hpp"
#include "Sample.hpp"

#define ANSWER_PEDESTRIAN +1
#define ANSWER_BACKGROUND -1

#define PATCH_STEP 4

static void printUsage(const char *programName) {
    std::cout << "Usage:" << std::endl;
    std::cout << "    " << programName << " sample_dir result_file [classifier_file]" << std::endl;
    std::cout << std::endl;
    std::cout << "Examples:" << std::endl;
    std::cout << "    1) $ " << programName << " train train\\train-processed.idl" << std::endl;
    std::cout << "       Read model from stdout and classify." << std::endl;
    std::cout << "    2) $ " << programName << " train train\\train-processed.idl model.txt" << std::endl;
    std::cout << "       Read model from 'model.txt' file and classify." << std::endl;
}

int main(int argc, char *argv[]) {
    if (/*argc != 3 &&*/ argc != 4) {  // TODO: non-implemented case
        printUsage(argv[0]);
        exit(EXIT_FAILURE);
    }
    else {
        const char *sampleDirectory = strdup(argv[1]);
        const char *resultFile = strdup(argv[2]);
        const char *modelFile = "";
        if (argc == 4) {
            modelFile = strdup(argv[3]);
        }

        try {
            ImageSet images(sampleDirectory);

            PatchPositions result;

            debugInline("Loading classifier... ");
            LinearSVM classifier(modelFile);
            debug("done.");

            std::vector <std::string> names = images.getNames();
            std::cerr << names.size() << " files are found." << std::endl;

            debug("Processing images...");
            int progress = 0;
            for (std::vector <std::string>::iterator name = names.begin(); name != names.end(); ++name) {
                progress += 1;
                std::cerr << "\b\b\b\b\b" << 100 * progress / names.size() << " %";

                Sample sample(images.getImage(*name));
                for (int x = 0; x < sample.maximalShift(); x += PATCH_STEP) {
                    int answer = classifier.classify(sample.getDescriptor(x));
                    if (answer == ANSWER_PEDESTRIAN) {
                        result.addPosition(*name, Rectangle(x, 0, PATCH_WIDTH, PATCH_HEIGHT));
                    }
                }
            }
            debug("\b\b\b\b\bDone.");

            result.save(resultFile);
        }
        catch (const char *e) {
            std::cerr << "Error: " << e << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}
