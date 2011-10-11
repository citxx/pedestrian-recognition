#include "Rectangle.hpp"

Rectangle::Rectangle(int left, int top, int width, int height):
    left(left),
    top(top),
    width(width),
    height(height) {
}

int Rectangle::left() {
    return this->_left;
}

int Rectangle::top() {
    return this->_top;
}

int Rectangle::right() {
    return this->_left + this->_width;
}

int Rectangle::bottom() {
    return this->_top + this->_height;
}

int Rectangle::width() {
    return this->_width;
}

int Rectangle::height() {
    return this->_height;
}



