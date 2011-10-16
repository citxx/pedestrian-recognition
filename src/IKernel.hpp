#ifndef KERNEL_HPP
#define KERNEL_HPP

#include <string>
#include <vector>

class IKernel {
  public:
    virtual ~Kernel() {};

    virtual void load(std::string fileName) = 0;
    virtual void save(std::string fikeName) const = 0;

    virtual std::string getExtension() const = 0;
    virtual std::vector <double> transform(std::vector <double> descriptor) const = 0;
};

#endif  // KERNEL_HPP
