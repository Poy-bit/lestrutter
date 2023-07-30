#include "rigidbody.h"

rigidbody::rigidbody() {}

glm::mat4 rigidbody::get_model_matrix() {
	return glm::mat4(1.0f);
}