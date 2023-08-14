#pragma once

#include <algorithm>
#include <cmath>

// Used lowercase for easier typing
class vec2 {
public:
    double x, y;
    vec2() : x(0), y(0) {}
    vec2(double x, double y) : x(x), y(y) {}

    vec2 operator *(double op2) {
        return vec2(x * op2, y * op2);
    }

    vec2 operator /(double op2) {
        return vec2(x / op2, y / op2);
    }

    vec2 operator +(vec2 op2) {
        return vec2(x + op2.x, y + op2.y);
    }

    vec2 operator +(float op2) {
        return vec2(x + op2, y + op2);
    }

    vec2 operator -(vec2 op2) {
        return vec2(x - op2.x, y - op2.y);
    }

    vec2 operator -(float op2) {
        return vec2(x - op2, y - op2);
    }

    vec2 operator -() {
        return vec2(-x, -y);
    }

    float distance(vec2 v) {
        return sqrt(pow(x - v.x, 2) + pow(y - v.y, 2));
    }

    float dot(vec2 v) {
        return x * v.x + y * v.y;
    }

    float length() {
        return sqrt(pow(x, 2) + pow(y, 2));
    }

    vec2 normalize() {
        float len = length();
        return vec2(x / len, y / len);
    }
};

class Transform {
public:
    vec2 position;
    // no rotation yet
    Transform() {}
};