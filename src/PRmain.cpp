#include <iostream>
#include <cstring>
#include <cstdlib>

#include "PedestrianRecognition.hpp"

static void printUsage(const char *programName) {
    std::cout << "Usage:  " << programName << " train classifier_file sample_dir result_file"    << std::endl <<
                 "        " << programName << " recognize classifier_file sample_dir result_file" << std::endl <<
                 "        " << programName << " [graphics]" << std::endl;
}

int PedestrianRecognition::Main(int argc, char *argv[]) {
    if (argc == 5 && strcmp(argv[1], "train") == 0) {
        PedestrianRecognition::trainingMode(argv[2], argv[3], argv[4]);
    }
    else if (argc == 5 && strcmp(argv[1], "recognize") == 0) {
        PedestrianRecognition::recognitionMode(argv[2], argv[3], argv[4]);
    }
    else if (argc == 1 || (argc == 2 && strcmp(argv[1], "graphics") == 0)) {
        PedestrianRecognition::graphicsMode();
    }
    else if (argc == 2 && strcmp(argv[1], "help") == 0) {
        printUsage(argv[0]);
        return EXIT_SUCCESS;
    }
    else {
        printUsage(argv[0]);
        return EXIT_FAILURE;
    }
}
