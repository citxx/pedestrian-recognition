#include "debug.hpp"
#include "Processing.hpp"

const int ANSWER_PEDESTRIAN = 1;
const int ANSWER_BACKGROUND = 0;

const int PATCH_STEP = 4;

std::vector <int> Processing::processSample(const Sample &sample,
                                            const LinearSVM *classifier) {
    std::vector <int> result;

    debugInline("Classifying sample: ");
    int toErase = 0;
    for (int x = 0; x < sample.maximalShift(); x += PATCH_STEP) {
        int answer = classifier->classify(sample.getDescriptor(x));

        while (toErase > 0){
            debugInline("\b");
            toErase -= 1;
        }

        debugInline(x);

        if (x == 0) {
            toErase = 1;
        }
        else {
            int y = x;
            while (y > 0) {
                y /= 10;
                toErase += 1;
            }
        }

        if (answer == ANSWER_PEDESTRIAN) {
            debugInline(" ");
            toErase = 0;
            result.push_back(x);
        }
    }
    while (toErase > 0){
        debugInline("\b");
        toErase -= 1;
    }
    debug("done.");

    return result;
}
