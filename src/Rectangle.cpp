#include <cmath>

#include "Rectangle.hpp"

Rectangle::Rectangle(int left, int top, int width, int height):
    _left(left),
    _top(top),
    _width(width),
    _height(height) {
}

Rectangle::Rectangle(const Rectangle &rect):
    _left(rect._left),
    _top(rect._top),
    _width(rect._width),
    _height(rect._height) {
}

int Rectangle::left() const {
    return this->_left;
}

int Rectangle::top() const {
    return this->_top;
}

int Rectangle::right() const {
    return this->_left + this->_width;
}

int Rectangle::bottom() const {
    return this->_top + this->_height;
}

int Rectangle::width() const {
    return this->_width;
}

int Rectangle::height() const {
    return this->_height;
}

bool operator ==(const Rectangle &a, const Rectangle &b) {
    return std::abs(a._left - b._left) <= 40 &&
           a._top == b._top &&
           a._width == b._width &&
           a._height == b._height;
}
