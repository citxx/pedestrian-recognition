#include <cstring>

#include "Signal2D.hpp"

double brightness(QRgb color) {
    return 0.2125 * qRed(color) + 0.7154 * qGreen(color) + 0.0721 * qBlue(color);
}

Signal2D::SignalData::SignalData(int width, int height) {
    this->linksCount = 1;
    this->value = new double[width * height];
}

Signal2D::Signal2D(int width, int height, double value) {
    this->data = new Signal2D::SignalData(width, height);

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            this->at(x, y) = value;
        }
    }
}

Signal2D::Signal2D(const QImage &img) {
    this->data = new Signal2D::SignalData(img.width(), img.height());

    for (int x = 0; x < this->width(); x++) {
        for (int y = 0; y < this->height(); y++) {
            this->at(x, y) = brightness(img.pixel(x, y)) / 255.0;
        }
    }
}

Signal2D::Signal2D(const Signal2D &sig) {
    this->data = sig.data;
    this->data->linksCount += 1;
}

Signal2D::~Signal2D() {
    this->data->linksCount -= 1;

    if (this->data->linksCount == 0) {
        delete []this->data->value;
        delete this->data;
    }
}

Signal2D & Signal2D::operator =(const Signal2D &sig) {
    this->data->linksCount -= 1;

    if (this->data->linksCount == 0) {
        delete []this->data->value;
        delete this->data;
    }

    this->data = sig.data;
    this->data->linksCount += 1;

    return *this;
}

void Signal2D::makeCopy() {
    if (this->data->linksCount > 1) {
        this->data->linksCount -= 1;
        double *v = this->data->value;
        int w = this->data->width;
        int h = this->data->height;
        this->data = new Signal2D::SignalData(w, h);

        memcpy(this->data->value, v, w * h * sizeof(double));
    }
}

Signal2D Signal2D::single(int width, int height) {
    Signal2D result(width, height);
    result.at(width / 2, height / 2) = 1.0;
    return result;
}


int Signal2D::width() const {
    return this->data->width;
}

int Signal2D::height() const {
    return this->data->height;
}

const double & Signal2D::at(int x, int y) const {
    return this->data->value[x * this->height() + y];
}

double & Signal2D::at(int x, int y) {
    this->makeCopy();
    return this->data->value[x * this->height() + y];
}

Signal2D Signal2D::normalized() const {
    double sum = 0.0;
    for (int x = 0; x < this->width(); x++) {
        for (int y = 0; y < this->height(); y++) {
            sum += this->at(x, y);                   // TODO: can be optimized
        }
    }
    sum = qAbs(sum);

    if (sum < 1e-5) {
        return *this;
    }
    else {
        Signal2D normalizedSignal2D(this->width(), this->height());
        for (int x = 0; x < this->width(); x++) {
            for (int y = 0; y < this->height(); y++) {
                normalizedSignal2D.at(x, y) = this->at(x, y) / sum;
            }
        }

        return normalizedSignal2D;
    }
}

Signal2D Signal2D::transposed() const {
    Signal2D transposedSignal2D(this->height(), this->width());
    for (int x = 0; x < this->width(); x++) {
        for (int y = 0; y < this->height(); y++) {
            transposedSignal2D.at(y, x) = this->at(x, y);
        }
    }

    return transposedSignal2D;

}

double applyToPoint(int x, int y, const Signal2D &sig, const Signal2D &filter) {
    double result = 0.0;
    for (int fx = 0; fx < filter.width(); fx++) {
        for (int fy = 0; fy < filter.height(); fy++) {
            int sigX = qBound(0, x + (fx - filter.width() / 2), sig.width() - 1);
            int sigY = qBound(0, y + (fy - filter.height() / 2), sig.height() - 1);
            result += filter.at(fx, fy) * sig.at(sigX, sigY);
        }
    }

    return result;
}

Signal2D Signal2D::withFilterApplied(const Signal2D &filter, QRect area) {
    if (area.isNull()) {
        area = QRect(0, 0, this->width() - 1, this->height() - 1);
    }

    Signal2D answer(*this);

    for (int x = area.left(); x <= area.right(); x++) {
        for (int y = area.top(); y <= area.bottom(); y++) {
            answer.at(x, y) = applyToPoint(x, y, *this, filter);
        }
    }

    return answer;
}

Signal2D operator -(const Signal2D &f) {
    Signal2D result(f.width(), f.height());

    for(int x = 0; x < result.width(); x++) {
        for (int y = 0; y < result.height(); y++) {
            result.at(x, y) = -f.at(x, y);
        }
    }

    return result;
}

Signal2D operator +(const Signal2D &f, const Signal2D &g) {
    if (f.width() != g.width() || f.height() != g.height()) {
        throw "Operator +: Signal2D sizes should be the same";
    }
    else {
        Signal2D result(f.width(), f.height());
        for (int x = 0; x < result.width(); x++) {
            for (int y = 0; y < result.height(); y++) {
                result.at(x, y) = f.at(x, y) + g.at(x, y);
            }
        }

        return result;
    }
}

Signal2D operator -(const Signal2D &f, const Signal2D &g) {
    if (f.width() != g.width() || f.height() != g.height()) {
        throw "Operator -: Signal2D sizes should be the same";
    }
    else {
        Signal2D result(f.width(), f.height());
        for (int x = 0; x < result.width(); x++) {
            for (int y = 0; y < result.height(); y++) {
                result.at(x, y) = f.at(x, y) + g.at(x, y);
            }
        }

        return result;
    }
}

Signal2D operator *(double a, const Signal2D &f) {
    Signal2D result(f.width(), f.height());

    for(int x = 0; x < result.width(); x++) {
        for (int y = 0; y < result.height(); y++) {
            result.at(x, y) = a * f.at(x, y);
        }
    }

    return result;
}

Signal2D operator *(const Signal2D &f, double a) {
    return a * f;
}

QImage merge(const Signal2D &r, const Signal2D &g, const Signal2D &b) {
    if (r.width() != g.width() || r.width() != b.width() ||
        r.height() != g.height() || r.height() != b.height()) {
        throw "merge: components r, g and b must have equal sizes";
    }
    else {
        QImage result(r.width(), r.height(), QImage::Format_RGB32);

        for (int x = 0; x < r.width(); x++) {
            for (int y = 0; y < r.height(); y++) {
                int vR = (int)(255 * qBound(0.0, r.at(x, y), 1.0));
                int vG = (int)(255 * qBound(0.0, g.at(x, y), 1.0));
                int vB = (int)(255 * qBound(0.0, b.at(x, y), 1.0));
                result.setPixel(x, y, qRgb(vR, vG, vB));
            }
        }

        return result;
    }
}
