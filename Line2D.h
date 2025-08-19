//
// Created by Bryan on 17/8/2025.
//

#ifndef LINE2D_H
#define LINE2D_H
#include "Point2D.h"


class Line2D {
private:
    Point2D pt1;
    Point2D pt2;
    double length;
public:
    virtual ~Line2D() = default;

    void setLength(); //calculate the length
    void setLength(double length); //setter for the length
    void setPt1(Point2D pt1);
    void setPt2(Point2D pt2);

    Line2D();
    Line2D(Point2D pt1, Point2D pt2);

    Point2D getPt1() const;
    Point2D getPt2() const;

    double getScalarValue();

    bool operator==(const Line2D& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Line2D& line);
};



#endif //LINE2D_H
