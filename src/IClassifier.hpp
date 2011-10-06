#ifndef I_CLASSIFIER_HPP
#define I_CLASSIFIER_HPP

#include <string>
#include <vector>

class IClassifier {
  public:
    void save(std::string fileName);
    void train(std::vector <std::vector <double> > samples, std::vector <int> answers);
    void classify(std::vector <double> sample);
};

#endif  // I_CLASSIFIER_HPP
