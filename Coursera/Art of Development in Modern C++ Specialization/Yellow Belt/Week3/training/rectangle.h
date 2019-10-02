#ifndef C___YELLOW_BELT_RECTANGLE_H
#define C___YELLOW_BELT_RECTANGLE_H

class Rectangle {
public:
    Rectangle(int width, int height);

    int GetArea() const;

    int GetPerimeter() const;

    int GetWidth() const;

    int GetHeight() const;

private:
    int width_, height_;
};

#endif //C___YELLOW_BELT_RECTANGLE_H
