#pragma once

#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

#include "mathtypes.h"
class Collider;

class Rigidbody {
    Collider* body_collider;

    vec2 pos;
    vec2 vel;
    vec2 acc = {};

public:
    Rigidbody();
    Rigidbody(float x, float y, vec2 vel);
    
    void setCollider(Collider* pCollider);

    glm::mat4 getModelMatrix();
    void step(double dt);
};