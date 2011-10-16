#include <cmath>
#include <fstream>

#include "Chi2Kernel.hpp"

Chi2Kernel::Chi2Kernel(int n, double step): n(n), step(step) {
}

Chi2Kernel::Chi2Kernel(std::string fileName) {
    std::fstream kernelFile(fileName.c_str(), std::ios_base::in);

    kernelFile >> this->n >> this->step;
}

void Chi2Kernel::save(std::string fileName) const {
    std::fstream kernelFile(fileName.c_str(), std::ios_base::out);

    kernelFile << this->n << std::endl << this->step << std::endl;
}

std::vector <double> Chi2Kernel::transform(std::vector <double> descriptor) const {
    std::vector <double> result;

    for (std::vector <double>::iterator x = descriptor.begin(); x != descriptor.end(); ++x) {
        for (int k = -this->n; k <= this->n; k++) {
            double lambda = k * step;
            double phi = lambda * log(*x + 1);
            double len = sqrt((*x + 1) / cosh(M_PI * lambda));
            result.push_back(cos(phi) * len);
            result.push_back(sin(phi) * len);
        }
    }

    return result;
}
