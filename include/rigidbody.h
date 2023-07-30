#pragma once

#include <glm/gtc/matrix_transform.hpp>

class rigidbody {
    glm::vec2 old_position;
    glm::vec2 position;
    glm::vec2 acceleration = {};

public:
    rigidbody();
    
    glm::mat4 get_model_matrix();
    void update(float dt);

    void apply_acceleration(glm::vec2 applied_acceleration) {
        acceleration += applied_acceleration;
    }
};