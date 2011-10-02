#ifndef PEDESTRIAN_RECOGNITION_HPP
#define PEDESTRIAN_RECOGNITION_HPP

class PedestrianRecognition {

    static void trainingMode(
        const char *classifierFileName,
        const char *sampleSetDirectoryName,
        const char *resultFileName
    );

    static void recognitionMode(
        const char *classifierFileName,
        const char *sampleSetDirectoryName,
        const char *resultFileName
    );

    static void graphicsMode();

  public:
    static int Main(int argc, char *argv[]);
};

#endif  // PEDESTRIAN_RECOGNITION_HPP
