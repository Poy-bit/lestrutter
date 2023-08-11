#pragma once

#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

#include "mathtypes.h"

struct Collider;

struct Rigidbody {
    Collider* body_collider = {};

    vec2 pos;
    vec2 vel;
    vec2 acc = {};

    Rigidbody() : pos(vec2(0, 0)), vel(vec2(0, 0)) {}
    Rigidbody(vec2 pos, vec2 vel = {0, 0}) : pos(pos), vel(vel) {}
    
    void setCollider(Collider* pCollider) {
        body_collider = pCollider;
    }

    glm::mat4 getModelMatrix() {
        return glm::translate(glm::mat4(1.0f), glm::vec3(pos.x, pos.y, 0.0f));
    }

    Transform getTransform() {
        Transform transform = Transform();
        transform.position = pos;
        return transform;
    }
};