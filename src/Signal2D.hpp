#ifndef SIGNAL_2D_HPP
#define SIGNAL_2D_HPP

#include <QImage>
#include <QRect>

class Signal2D {
    struct SignalData {
        int linksCount;
        double *value;
        int width, height;

        SignalData(int width, int height);
    } *data;

    void makeCopy();

  public:
    Signal2D(int width, int height, double value = 0.0);
    Signal2D(const QImage &img);
    Signal2D(const Signal2D &sig);
    ~Signal2D();

    static Signal2D single(int width, int height);

    const double & at(int x, int y) const;
    double & at(int x, int y);

    int width() const;
    int height() const;

    Signal2D normalized() const;
    Signal2D transposed() const;

    Signal2D withFilterApplied(const Signal2D &filter, QRect area = QRect());

    Signal2D & operator =(const Signal2D &sig);
};

Signal2D operator -(const Signal2D &sig);
Signal2D operator +(const Signal2D &f, const Signal2D &g);
Signal2D operator -(const Signal2D &f, const Signal2D &g);
Signal2D operator *(double a, const Signal2D &f);
Signal2D operator *(const Signal2D &f, double a);

#endif  // SIGNAL_2D_HPP
