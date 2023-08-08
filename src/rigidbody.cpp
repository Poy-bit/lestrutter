#include "rigidbody.h"

rigidbody::rigidbody(): pos(vec2(0, 0)), vel(vec2(0, 0))
{}

rigidbody::rigidbody(float x, float y, vec2 vel) : pos(vec2(x, y)), vel(vel)
{}

void rigidbody::add_collider(collider* pCollider) {
	body_collider = pCollider;
}

glm::mat4 rigidbody::get_model_matrix() {
	return glm::translate(glm::mat4(1.0f), glm::vec3(pos.x, pos.y, 0.0f));
}

void rigidbody::step(double dt) {
	acc = { 0, 0 };
	vel = vel + acc * dt;

	//if (pos.y < 0) vel.y = -pos.y / dt;

	pos = pos + vel * dt;
}