#ifndef HISTOGRAM_HPP
#define HISTOGRAM_HPP

#include <vector>

template <unsigned int size>
class Histogram;

template <unsigned int size>
Histogram <size> operator +(const Histogram <size> &a, const Histogram <size> &b) {
    Histogram <size> answer;
    for (unsigned int i = 0; i < size; i++) {
        answer.data[i] = a.data[i] + b.data[i];
    }
    return answer;
}

template <unsigned int size>
Histogram <size> operator -(const Histogram <size> &a, const Histogram <size> &b) {
    Histogram <size> answer;
    for (unsigned int i = 0; i < size; i++) {
        answer.data[i] = a.data[i] - b.data[i];
    }
    return answer;
}

template <unsigned int size>
class Histogram {
    int data[size];

  public:
    Histogram() {
        for (unsigned int i = 0; i < size; i++) {
            this->data[i] = 0;
        }
    }

    Histogram(const Histogram <size> &hist) {
        for (unsigned int i = 0; i < size; i++) {
            this->data[i] = hist.data[i];
        }
    }

    std::vector <int> getVector() const {
        return std::vector <int>(this->data, this->data + size);
    }

    int & operator [](unsigned int index) {
        if (index < 0 || size <= index) {
            throw "Histogram: wrong index";
        }
        return data[index];
    }

    const int & operator [](unsigned int index) const {
        if (index < 0 || size <= index) {
            throw "Histogram: wrong index";
        }
        return data[index];
    }

    Histogram <size> & operator =(const Histogram <size> &hist) {
        for (unsigned int i = 0; i < size; i++) {
            this->data[i] = hist.data[i];
        }
        return *this;
    }

    friend Histogram <size> operator + <size>(const Histogram <size> &a, const Histogram <size> &b);
    friend Histogram <size> operator - <size>(const Histogram <size> &a, const Histogram <size> &b);
};

#endif  // HISTOGRAM_HPP
