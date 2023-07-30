#include "rigidbody.h"

rigidbody::rigidbody() {
	position = glm::vec2(0, 50);
	old_position = position;
}

glm::mat4 rigidbody::get_model_matrix() {
	return glm::translate(glm::mat4(1.0f), glm::vec3(position, 0.0f));
}

void rigidbody::update(float dt) {
	glm::vec2 velocity = position - old_position;
	old_position = position;
	position = position + velocity + acceleration * dt * dt;
	acceleration = {};
}