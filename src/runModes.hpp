#ifndef RUN_MODES_HPP
#define RUN_MODES_HPP

void runTrainingMode(
    const char *classifierFileName,
    const char *sampleSetDirectoryName);

void runClassifyingMode(
    const char *classifierFileName,
    const char *sampleSetDirectoryName,
    const char *resultFileName);

void runGraphicsMode();

#endif  // RUN_MODES_HPP

