#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

class Rectangle {
    int _left;
    int _top;
    int _width;
    int _height;

  public:
    Rectangle(int left, int top, int width, int height);
    Rectangle(const Rectangle &rect);
    int left() const;
    int top() const;
    int right() const;
    int bottom() const;
    int width() const;
    int height() const;
};

#endif  // RECTANGLE_HPP
