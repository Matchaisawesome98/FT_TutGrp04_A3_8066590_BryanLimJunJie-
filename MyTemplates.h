#ifndef MYTEMPLATES_H
#define MYTEMPLATES_H

#include <cmath>
#include <memory>
#include <vector>
#include <algorithm>

// Template function for scalar difference
template<typename T>
double scalar_difference(T obj1, T obj2) {
    return abs(obj1.getScalarValue() - obj2.getScalarValue());
}

// Template function for equals comparison
template<typename T>
bool equals(T obj1, T obj2) {
    return obj1 == obj2;
}

// Point2D and Point3D comparators
template <typename T>
bool compareXAsc(const std::unique_ptr<T>& a, const std::unique_ptr<T>& b) {
    return a->getX() < b->getX();
}

template <typename T>
bool compareXDsc(const std::unique_ptr<T>& a, const std::unique_ptr<T>& b) {
    return a->getX() > b->getX();
}

template <typename T>
bool compareYAsc(const std::unique_ptr<T>& a, const std::unique_ptr<T>& b) {
    return a->getY() < b->getY();
}

template <typename T>
bool compareYDsc(const std::unique_ptr<T>& a, const std::unique_ptr<T>& b) {
    return a->getY() > b->getY();
}

template <typename T>
bool compareZAsc(const std::unique_ptr<T>& a, const std::unique_ptr<T>& b) {
    return a->getZ() < b->getZ();
}

template <typename T>
bool compareZDsc(const std::unique_ptr<T>& a, const std::unique_ptr<T>& b) {
    return a->getZ() > b->getZ();
}

template <typename T>
bool compareDistAsc(const std::unique_ptr<T>& a, const std::unique_ptr<T>& b) {
    return a->getScalarValue() < b->getScalarValue();
}

template <typename T>
bool compareDistDsc(const std::unique_ptr<T>& a, const std::unique_ptr<T>& b) {
    return a->getScalarValue() > b->getScalarValue();
}

// Line2D and Line3D comparators for Point 1
template <typename T>
bool compareXAscPt1(const std::unique_ptr<T>& a, const std::unique_ptr<T>& b) {
    return a->getPt1().getX() < b->getPt1().getX();
}

template <typename T>
bool compareXDscPt1(const std::unique_ptr<T>& a, const std::unique_ptr<T>& b) {
    return a->getPt1().getX() > b->getPt1().getX();
}

template <typename T>
bool compareYAscPt1(const std::unique_ptr<T>& a, const std::unique_ptr<T>& b) {
    return a->getPt1().getY() < b->getPt1().getY();
}

template <typename T>
bool compareYDscPt1(const std::unique_ptr<T>& a, const std::unique_ptr<T>& b) {
    return a->getPt1().getY() > b->getPt1().getY();
}

template <typename T>
bool compareZAscPt1(const std::unique_ptr<T>& a, const std::unique_ptr<T>& b) {
    return a->getPt1().getZ() < b->getPt1().getZ();
}

template <typename T>
bool compareZDscPt1(const std::unique_ptr<T>& a, const std::unique_ptr<T>& b) {
    return a->getPt1().getZ() > b->getPt1().getZ();
}

// Line2D and Line3D comparators for Point 2
template <typename T>
bool compareXAscPt2(const std::unique_ptr<T>& a, const std::unique_ptr<T>& b) {
    return a->getPt2().getX() < b->getPt2().getX();
}

template <typename T>
bool compareXDscPt2(const std::unique_ptr<T>& a, const std::unique_ptr<T>& b) {
    return a->getPt2().getX() > b->getPt2().getX();
}

template <typename T>
bool compareYAscPt2(const std::unique_ptr<T>& a, const std::unique_ptr<T>& b) {
    return a->getPt2().getY() < b->getPt2().getY();
}

template <typename T>
bool compareYDscPt2(const std::unique_ptr<T>& a, const std::unique_ptr<T>& b) {
    return a->getPt2().getY() > b->getPt2().getY();
}

template <typename T>
bool compareZAscPt2(const std::unique_ptr<T>& a, const std::unique_ptr<T>& b) {
    return a->getPt2().getZ() < b->getPt2().getZ();
}

template <typename T>
bool compareZDscPt2(const std::unique_ptr<T>& a, const std::unique_ptr<T>& b) {
    return a->getPt2().getZ() > b->getPt2().getZ();
}

#endif //MYTEMPLATES_H