#ifndef MYTEMPLATES_H
#define MYTEMPLATES_H

template<typename T>
double scalar_difference(T obj1, T obj2) {
    return abs(obj1.getScalarValue() - obj2.getScalarValue());
}

template<typename T>
bool equals(T obj1, T obj2) {
    return obj1 == obj2;
}
#endif //MYTEMPLATES_H
