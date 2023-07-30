#pragma once

#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

class rigidbody {
    glm::vec2 old_position;
    glm::vec2 position;
    glm::vec2 acceleration = {};

    float mass;

public:
    rigidbody();
    
    glm::mat4 get_model_matrix();
    void update(float dt);

    void apply_acceleration(glm::vec2 applied_acceleration) {
        acceleration += applied_acceleration;
    }

    void apply_constraint() {
        glm::vec2 anchor = { 0, 0 };
        float radius = 20.0;
        //glm::vec2 to_obj = position - constraint_position;
        float dist = glm::length(position - anchor);
        
        if (dist > radius) {
            position = (glm::normalize(position - anchor) * 20.0f) + anchor;
            std::cout << "bruh\n";
        }
    }
};