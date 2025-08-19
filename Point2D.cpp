#include "Point2D.h"
#include <cmath>
#include <iostream>
#include <math.h>

using namespace std;

//Default constructor
Point2D::Point2D() : x(0),y(0), distFrOrigin(0) {}

//Constructor
Point2D::Point2D(int x, int y) : x(x), y(y) {
    distFrOrigin = sqrt(pow(this->x, 2) + pow(this->y, 2));
}

int Point2D::getX() const {
    return this->x;
}

int Point2D::getY() const {
    return this->y;
}

double Point2D::getScalarValue() const {
    return this->distFrOrigin;
}

void Point2D::setX(int x) {
    this->x = x;
    distFrOrigin = sqrt(pow(this->x, 2) + pow(this->y, 2));
}

void Point2D::setY(int y) {
    this->y = y;
    distFrOrigin = sqrt(pow(this->x, 2) + pow(this->y, 2));
}

bool Point2D::operator==(const Point2D& other) const {
    return (this->x == other.x) && (this->y == other.y);
}

ostream& operator<<(ostream& os, const Point2D& point) {
    os << "Point2D(" << point.x << ", " << point.y << ")";
    return os;
}






