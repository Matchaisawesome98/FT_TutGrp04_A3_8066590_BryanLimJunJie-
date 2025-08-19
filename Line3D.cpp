#include "Line3D.h"
#include "Point3D.h"
#include <cmath>
#include <iostream>
#include <math.h>

Line3D::Line3D() {
    pt1 = Point3D();
    pt2 = Point3D();
    setLength();
};

Line3D::Line3D(Point3D pt1, Point3D pt2) {
    this->pt1 = pt1;
    this->pt2 = pt2;
    setLength();
}

void Line3D::setLength() {
    double deltaX = pt2.getX() - pt1.getX();
    double deltaY = pt2.getY() - pt1.getY();
    double deltaZ = pt2.getZ() - pt1.getZ();
    this->length = sqrt(pow(deltaX, 2) + pow(deltaY, 2) + pow(deltaZ, 2));
}

double Line3D::getScalarValue() {
    return this->length;
}

Point3D Line3D::getPt1() const{
    return this->pt1;
}

Point3D Line3D::getPt2() const {
    return this->pt2;
}

void Line3D::setPt1(Point3D pt1) {
    this->pt1 = pt1;
    setLength();
}

void Line3D::setPt2(Point3D pt2) {
    this->pt2 = pt2;
    setLength();
}

bool Line3D::operator==(const Line3D& other) const {
    return (this->pt1 == other.pt1) && (this->pt2 == other.pt2);
}

std::ostream& operator<<(std::ostream& os, const Line3D& line) {
    os << "Line3D[(" << line.getPt1().getX() << ", "
       << line.getPt1().getY() << ", "
       << line.getPt1().getZ() << "), ("
       << line.getPt2().getX() << ", "
       << line.getPt2().getY() << ", "
       << line.getPt2().getZ() << ")]";
    return os;
}



