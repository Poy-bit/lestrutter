#pragma once

#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "collider.h"

struct vec2 {
    double x, y;
    vec2() : x(0), y(0) {}
    vec2(double x, double y): x(x), y(y) {}

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

class rigidbody {
    vec2 pos;
    vec2 vel;
    vec2 acc = {};

    collider* body_collider = nullptr;

public:
    rigidbody();
    rigidbody(float x, float y, vec2 vel);
    
    void add_collider(collider* pCollider);

    glm::mat4 get_model_matrix();
    void step(double dt);
};