#ifndef CHI2_KERNEL_HPP
#define CHI2_KERNEL_HPP

#include <string>
#include <vector>

//#include "IKernel.hpp"
#include "LinearSVM.hpp"

class Chi2Kernel {
    int n;
    double step;

  public:
    Chi2Kernel(int n, double step);
    Chi2Kernel(std::string fileName);

    void save(std::string fileName) const;
    std::vector <double> transform(std::vector <double> descriptor) const;
};

#endif  // CHI2_KERNEL_HPP
