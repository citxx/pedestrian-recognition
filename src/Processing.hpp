#ifndef PROCESSING_HPP
#define PROCESSING_HPP

#include <vector>

#include "LinearSVM.hpp"
#include "Sample.hpp"

namespace Processing {
    std::vector <int> processSample(const Sample &sample, const LinearSVM *classifier);
}

#endif  // PROCESSING_HPP
