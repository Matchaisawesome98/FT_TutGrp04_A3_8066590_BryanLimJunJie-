#ifndef LINE3D_H
#define LINE3D_H
#include "Point3D.h"


class Line3D {
private:
    Point3D pt1;
    Point3D pt2;
    double length;

public:
    ~Line3D() = default;

    Line3D();
    Line3D(Point3D pt1, Point3D pt2);

    void setLength();

    Point3D getPt1() const;
    Point3D getPt2() const;
    double getScalarValue();

    void setPt1(Point3D pt1);
    void setPt2(Point3D pt2);

    bool operator==(const Line3D& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Line3D& line);
};



#endif //LINE3D_H
