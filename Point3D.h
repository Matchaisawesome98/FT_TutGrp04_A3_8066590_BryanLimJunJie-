#ifndef POINT3D_H
#define POINT3D_H

#include <iostream>
#include "Point2D.h"


class Point3D : public Point2D{
private:
    int z;
public:
    Point3D();
    Point3D(int x, int y, int z);

    int getZ() const;

    void setZ(int z);

    double getScalarValue() const override;

    bool operator==(const Point3D& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Point3D& point);
};



#endif //POINT3D_H
