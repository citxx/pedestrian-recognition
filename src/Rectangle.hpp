#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

class Rectangle {
    int _left;
    int _top;
    int _width;
    int _height;

  public:
    Rectangle(int left, int top, int width, int height);
    int left();
    int top();
    int right();
    int bottom();
    int width();
    int height();
};

#endif  // RECTANGLE_HPP
