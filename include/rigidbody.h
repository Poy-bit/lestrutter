#pragma once

#include <glm/gtc/matrix_transform.hpp>

class rigidbody {
public:
    rigidbody();
    
    glm::mat4 get_model_matrix();
};