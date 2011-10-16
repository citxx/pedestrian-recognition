#include <algorithm>
#include <cmath>
#include <utility>

#include "debug.hpp"
#include "Processing.hpp"

const int ANSWER_PEDESTRIAN = 1;
const int ANSWER_BACKGROUND = 0;

const int PATCH_STEP = 4;
const int SUPPRESS_RANGE = PATCH_WIDTH / PATCH_STEP / 2;
const double THRESHOLD = 0.0;

std::vector <int> Processing::processSample(const Sample &sample,
                                            const LinearSVM *classifier) {
    std::vector <double> estimates;

    debugInline("Classifying sample: ");
    int toErase = 0;
    for (int x = 0; x < sample.maximalShift(); x += PATCH_STEP) {
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

        double estimate;
        int answer = classifier->classify(sample.getDescriptor(x), &estimate);

        if (answer == ANSWER_PEDESTRIAN) {
            debugInline(" ");
            toErase = 0;

            estimates.push_back(estimate);
        }
        else {
            estimates.push_back(-estimate);
        }
    }
    while (toErase > 0){
        debugInline("\b");
        toErase -= 1;
    }
    debug("done.");

    std::vector <int> result;

    while(true) {
        double mx = estimates[0];
        int mxInd = 0;
        for (int i = 0; i < (int)estimates.size(); i++) {
            if (estimates[i] > mx) {
                mx = estimates[i];
                mxInd = i;
            }
        }

        if (mx <= THRESHOLD) {
            break;
        }
        else {
            result.push_back(mxInd * PATCH_STEP);
            int suppressStart = std::max(0, mxInd - SUPPRESS_RANGE);
            int suppressEnd = std::min((int)estimates.size(), mxInd + SUPPRESS_RANGE);
            for (int i = suppressStart; i < suppressEnd; i++) {
                estimates[i] = THRESHOLD;
            }
        }
    }

    std::sort(result.begin(), result.end());
    return result;
}
