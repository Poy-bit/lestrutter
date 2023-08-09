#pragma once

// Used lowercase for easier typing
class vec2 {
public:
    double x, y;
    vec2() : x(0), y(0) {}
    vec2(double x, double y) : x(x), y(y) {}

    vec2 operator *(double op2) {
        return vec2(x * op2, y * op2);
    }

    vec2 operator +(vec2 op2) {
        return vec2(x + op2.x, y + op2.y);
    }

    float distance(vec2 p) {
        return sqrt(pow(x - p.x, 2) + pow(y - p.y, 2));
    }
};

class Transform {
public:
    vec2 position;
    // no rotation yet
    Transform() {}
};