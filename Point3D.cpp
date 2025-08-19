//
// Created by Bryan on 18/8/2025.
//

#include "Point3D.h"
#include <cmath>
#include "Point2D.h"


using namespace std;

Point3D::Point3D() : Point2D(), z(0) {}
Point3D::Point3D(int x, int y, int z) :Point2D(x, y), z(z) {}

int Point3D::getZ() const {
    return this->z;
}

void Point3D::setZ(int z) {
    this->z = z;
}

double Point3D::getScalarValue() const {
    return sqrt(pow(getX(), 2) + pow(getY(), 2) + pow(this->z, 2));
}

bool Point3D::operator==(const Point3D& other) const {
    return Point2D::operator==(other) && (this->z == other.z);
}

ostream& operator<<(ostream& os, const Point3D& point) {
    os << "Point3D(" << point.getX() << ", "
       << point.getY() << ", " << point.getZ() << ")";
    return os;
}
