#include "Line2D.h"
#include "Point2D.h"
#include <cmath>
#include <iostream>
#include <math.h>
#include <set>

using namespace std;

Line2D::Line2D() {
    pt1 = Point2D();
    pt2 = Point2D();
    setLength();
}

Line2D::Line2D(Point2D pt1, Point2D pt2) {
    this->pt1 = pt1;
    this->pt2 = pt2;
    setLength();
}

void Line2D::setLength(double length) {
    this->length = length;
}

void Line2D::setPt1(Point2D pt1) {
    this->pt1 = pt1;
    setLength();
}

void Line2D::setPt2(Point2D pt2) {
    this->pt2 = pt2;
    setLength();
}

Point2D Line2D::getPt1() const{
    return this->pt1;
}

Point2D Line2D::getPt2() const{
    return this->pt2;
}

void Line2D::setLength() {
    // Using the distance formula: √[(x2-x1)² + (y2-y1)²]
    double deltaX = pt2.getX() - pt1.getX();
    double deltaY = pt2.getY() - pt1.getY();
    this->length = sqrt(pow(deltaX, 2) + pow(deltaY, 2));
}

double Line2D::getScalarValue() {
    return this->length;
}

bool Line2D::operator==(const Line2D& other) const {
    return (this->pt1 == other.pt1) && (this->pt2 == other.pt2);
}

ostream& operator<<(ostream& os, const Line2D& line) {
    os << "Line2D[(" << line.getPt1().getX() << ", "
       << line.getPt1().getY() << "), ("
       << line.getPt2().getX() << ", "
       << line.getPt2().getY() << ")]";
    return os;
}