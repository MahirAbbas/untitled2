//
// Created by mahir on 2/15/23.
//

#ifndef UNTITLED2_VECTOR_H
#define UNTITLED2_VECTOR_H
#include <cmath>
#include <iostream>
class Vector {
public:
    float x, y, z;
    float r, g, b;

    Vector() {}
    Vector(double x, double y, double z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }
    double magnitude() {
        return std::sqrt(x * x + y * y + z * z);
    }
    void setx(float x)
    {
        this->x = x;
    }
    void normalise() {
        double mag = magnitude();
        if (mag != 0) {
            x /= mag;
            y /= mag;
            z /= mag;
        }
    }

    double dot(Vector a)
    {
        return x * a.x + y * a.y + z * a.z;
    }
    Vector operator + (Vector v)
    {
       Vector new_vec(x + v.x, y+v.y, z+v.z);
        return new_vec;
    }
    Vector operator - (Vector v)
    {
        Vector new_vec(x - v.x, y - v.y, z - v.z);
        return new_vec;
    }
    Vector operator * (double d)
    {
        Vector new_vec(x * d, y * d, z * d);
        return new_vec;
    }
    Vector componentMultiply(Vector v)
    {
        return Vector(x*v.x, y*v.y, z*v.z);
    }
    void print() {
        std::cout << "x=" << x << ", y=" << y << ", z=" << z << "\n";
    }
};


#endif //UNTITLED2_VECTOR_H
