#include <linear.h>
#include <cmath>

#include "LinearSVM.hpp"

LinearSVM::LinearSVM(std::vector <std::vector <double> > descriptors, std::vector <int> answers) {
    if (descriptors.size() != answers.size()) {
        throw "LinearSVM: 'descriptors' and 'answers' vectors should have the same size";
    }
    if (descriptors.size() == 0) {
        throw "LinearSVM: The model should be trained on non-empty sample set";
    }

    struct problem task;
    task.l = (int)descriptors.size();  // Size of sample set
    task.bias = 1;
    task.n = (int)descriptors[0].size() + 1;  // Number of features + final node

    task.y = new int[task.l];  // Memory for the answers
    task.x = new struct feature_node *[task.l];  // Memory for the features

    for (int i = 0; i < (int)descriptors.size(); i++) {
        task.x[i] = new feature_node[task.n];
        task.x[i][task.n - 1].index = -1;

        for (int j = 0; j < (int)descriptors[i].size(); j++) {
            task.x[i][j].index = j + 1;
            task.x[i][j].value = descriptors[i][j];
        }

        task.y[i] = answers[i];
    }

    struct parameter properties;
    properties.solver_type = L2R_L2LOSS_SVC_DUAL;
    properties.C = 1;
    properties.eps = 1e-4;
    properties.nr_weight = 0;
    properties.weight_label = NULL;
    properties.weight = NULL;

    this->modelSVM = train(&task, &properties);

    delete []task.y;
    for (int i = 0; i < task.l; i++) {
        delete task.x[i];
    }
    delete []task.x;
}

LinearSVM::LinearSVM(std::string fileName) {
    this->modelSVM = load_model(fileName.c_str());
    if (this->modelSVM == NULL) {
        throw "LinearSVM: Can't load a model from the file";
    }
}

LinearSVM::~LinearSVM() {
    free_and_destroy_model(&this->modelSVM);
}


void LinearSVM::save(std::string fileName) {
    int status = save_model(fileName.c_str(), this->modelSVM);
    if (status) {
        throw "LinearSVM: Can't save the model to the file";
    }
}

int LinearSVM::classify(std::vector <double> descriptor, double *estimate) {
    struct feature_node *x = new struct feature_node[descriptor.size() + 1];
    x[descriptor.size()].index = -1;
    for (int i = 0; i < (int)descriptor.size(); i++) {
        x[i].index = i + 1;
        x[i].value = descriptor[i];
    }
    double realEstimate;
    int label = predict_values(this->modelSVM, x, &realEstimate);
    if (estimate != NULL) *estimate = std::abs(realEstimate);
    return label;
}
