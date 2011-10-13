#include <iostream>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <string>
#include <algorithm>

#include "ImageSet.hpp"
#include "PatchPositions.hpp"
#include "Sample.hpp"
#include "LinearSVM.hpp"
#include "Rectangle.hpp"
#include "debug.hpp"

#define ANSWER_PEDESTRIAN 1
#define ANSWER_BACKGROUND -1

#define BACKGROUND_PER_SAMPLE 3

static void printUsage(const char *programName) {
    std::cout << "Usage:" << std::endl;
    std::cout << "    " << programName << " sample_dir result_file [classifier_file]" << std::endl;
    std::cout << std::endl;
    std::cout << "Examples:" << std::endl;
    std::cout << "    1) $ " << programName << " train\\train-processed.idl" << std::endl;
    std::cout << "       Writes model to stdout" << std::endl;
    std::cout << "    2) $ " << programName << " train\\train-processed.idl model.txt" << std::endl;
    std::cout << "       Writes model to 'model.txt' file" << std::endl;
}

int main(int argc, char *argv[]) {
    srand(argc * 17);
    if (/*argc != 3 &&*/ argc != 4) {  // TODO: unimplemented case
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
            PatchPositions result(resultFile);

            std::vector <std::string> names = images.getNames();
            std::vector <std::vector <double> > descriptorSet;
            std::vector <int> answerSet;
            std::cerr << names.size() << std::endl;
            for (std::vector <std::string>::iterator imageName = names.begin();
                 imageName != names.end();
                 ++imageName) {
                Sample sample(images.getImage(*imageName));

                std::vector <Rectangle> pRects = result.getPositions(*imageName);
                std::vector <int> pPos(pRects.size());
                for (int i = 0; i < (int)pRects.size(); i++) {
                    pPos[i] = pRects[i].left();
                }
                std::sort(pPos.begin(), pPos.end());

                // Pedestrian patches
                std::cerr << *imageName << " " << pPos.size() << std::endl;
                for (std::vector <int>::iterator pos = pPos.begin(); pos != pPos.end(); ++pos) {
                    descriptorSet.push_back(sample.getDescriptor(*pos));
                    answerSet.push_back(ANSWER_PEDESTRIAN);
                }

                // Background patches
                std::vector <bool> isAllowed(sample.maximalShift() + 1, true);
                for (std::vector <int>::iterator pos = pPos.begin(); pos != pPos.end(); ++pos) {
                    int start = std::max(0, *pos - PATCH_WIDTH / 2);
                    int end = std::min(*pos + PATCH_WIDTH / 2, sample.maximalShift() + 1);
                    for (int i = start; i < end; i++) {
                        isAllowed[i] = false;
                    }
                }
                int bgCount = 0;
                for (int i = 0; i < (int)isAllowed.size(); i++) {
                    if (isAllowed[i]) {
                        bgCount += 1;
                    }
                }

                for (int bgNum = 0; bgNum < BACKGROUND_PER_SAMPLE; bgNum++) {
                    int number = rand() % bgCount;
                    int x = -1;
                    while (number > 0 || !isAllowed[x]) {
                        x += 1;
                        if (isAllowed[x]) {
                            number -= 1;
                        }
                    }
                    descriptorSet.push_back(sample.getDescriptor(x));
                    answerSet.push_back(ANSWER_PEDESTRIAN);
                }
            }

            std::cerr << "There are " << descriptorSet.size() << " pathces." << std::endl;

            LinearSVM(descriptorSet, answerSet).save(modelFile);
        }
        catch (const char *e) {
            std::cerr << "Error: " << e << std::endl;
        }
    }

    return 0;
}
