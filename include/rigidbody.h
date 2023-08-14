#pragma once

#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

#include "mathtypes.h"
#include "collider.h"

struct Rigidbody {
    Collider* body_collider = {};

    vec2 pos;
    vec2 vel;
    vec2 acc = {};
    float mass;

    Rigidbody() : pos(vec2(0, 0)), vel(vec2(0, 0)), mass(1) {}
    Rigidbody(vec2 pos, vec2 vel = {0, 0}) : pos(pos), vel(vel), mass(1) {}
    
    void setCollider(Collider* pCollider) {
        pCollider->user = this;
        body_collider = pCollider;
    }

    glm::mat4 getModelMatrix() {
        return glm::translate(glm::mat4(1.0f), glm::vec3(pos.x, pos.y, 0.0f));
    }
};