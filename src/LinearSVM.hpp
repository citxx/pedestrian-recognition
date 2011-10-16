#ifndef LINEAR_SVM_HPP
#define LINEAR_SVM_HPP

#include <vector>
#include <string>

class LinearSVM {
    struct model *modelSVM;

  public:
    LinearSVM(std::vector <std::vector <double> > descriptor,
              std::vector <int> answers,
              double violationCost
    );
    LinearSVM(std::string fileName);
    ~LinearSVM();

    void save(std::string fileName) const;
    int classify(std::vector <double> descriptor, double *estimate = NULL) const;
};

#endif  // LINEAR_SVM_HPP
