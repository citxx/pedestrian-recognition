#include <iostream>
#include <cstring>
#include <cstdlib>

#include "runModes.hpp"

void printUsage(const char *programName) {
    std::cout << "Usage:  " << programName << " train sample_dir classifier_file"    << std::endl <<
                 "        " << programName << " classify sample_dir classifier_file result_file" << std::endl <<
                 "        " << programName << " [graphics]" << std::endl;
}

int main(int argc, char *argv[]) {
    if (argc == 4 && strcmp(argv[1], "train") == 0) {
        runTrainingMode(argv[3], argv[2]);
    }
    else if (argc == 5 && strcmp(argv[1], "classify") == 0) {
        runClassifyingMode(argv[3], argv[2], argv[4]);
    }
    else if (argc == 1 || (argc == 2 && strcmp(argv[1], "graphics") == 0)) {
        runGraphicsMode();
    }
    else if (argc == 2 && strcmp(argv[1], "help") == 0) {
        printUsage(argv[0]);
        exit(EXIT_SUCCESS);
    }
    else {
        printUsage(argv[0]);
        exit(EXIT_FAILURE);
    }
}
