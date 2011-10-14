#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

#include "debug.hpp"
#include "PatchPositions.hpp"
#include "Sample.hpp"

static void printUsage(const char *programName) {
    std::cout << "Usage:" << std::endl;
    std::cout << "    " << programName << " check_results_file true_results_file" << std::endl;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printUsage(argv[0]);
        exit(EXIT_FAILURE);
    }
    else {
        const char *checkFile = strdup(argv[1]);
        const char *trueFile = strdup(argv[2]);

        try {
            debugInline("Loading files... ");
            PatchPositions checkPos(checkFile);
            PatchPositions truePos(trueFile);
            debug("done.");

            std::vector <std::string> checkNames = checkPos.getNames();
            std::vector <std::string> trueNames = truePos.getNames();

            int truePatchesCount = 0;
            int truePatchesFound = 0;

            for (std::vector <std::string>::iterator name = trueNames.begin(); name != trueNames.end(); ++name) {
                std::vector <Rectangle> trueRects = truePos.getPositions(*name);
                std::vector <Rectangle> checkRects = checkPos.getPositions(*name);

                truePatchesCount += trueRects.size();
                for (std::vector <Rectangle>::iterator rect = trueRects.begin(); rect != trueRects.end(); ++rect) {
                    if (std::find(checkRects.begin(), checkRects.end(), *rect) != checkRects.end()) {
                        truePatchesFound += 1;
                    }
                }
            }

            int trueDetectionsCount = 0;
            int allDetectionsCount = 0;

            for (std::vector <std::string>::iterator name = checkNames.begin(); name != checkNames.end(); ++name) {
                std::vector <Rectangle> trueRects = truePos.getPositions(*name);
                std::vector <Rectangle> checkRects = checkPos.getPositions(*name);

                allDetectionsCount += checkRects.size();
                for (std::vector <Rectangle>::iterator rect = checkRects.begin(); rect != checkRects.end(); ++rect) {
                    if (std::find(trueRects.begin(), trueRects.end(), *rect) != trueRects.end()) {
                        trueDetectionsCount += 1;
                    }
                }
            }

            debugInline("#TP' = "); debug(truePatchesFound);
            debugInline("#GP  = "); debug(truePatchesCount);
            debugInline("#TP  = "); debug(trueDetectionsCount);
            debugInline("#DET = "); debug(allDetectionsCount);

            std::cout << "Recall: " << (double)truePatchesFound / truePatchesCount << std::endl;
            std::cout << "Precision: " << (double)trueDetectionsCount / allDetectionsCount << std::endl;
        }
        catch (const char *e) {
            std::cerr << "Error: " << e << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}
