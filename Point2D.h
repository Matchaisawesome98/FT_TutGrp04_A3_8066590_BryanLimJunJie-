#ifndef POINT2D_H
#define POINT2D_H

#include <iostream>


class Point2D {
private:
    int x,y;
    double distFrOrigin;
public:
    virtual ~Point2D() = default;

    Point2D();
    Point2D(int x, int y);

    int getX() const;
    int getY() const;
    virtual double getScalarValue() const;

    void setX(int x);
    void setY(int y);

    bool operator==(const Point2D& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Point2D& point);
};

#endif //POINT2D_H
