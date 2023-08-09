#include "rigidbody.h"

Rigidbody::Rigidbody(): pos(vec2(0, 0)), vel(vec2(0, 0))
{}

Rigidbody::Rigidbody(float x, float y, vec2 vel) : pos(vec2(x, y)), vel(vel)
{}

void Rigidbody::setCollider(Collider* pCollider) {
	body_collider = pCollider;
}

glm::mat4 Rigidbody::getModelMatrix() {
	return glm::translate(glm::mat4(1.0f), glm::vec3(pos.x, pos.y, 0.0f));
}

void Rigidbody::step(double dt) {
	acc = { 0, 0 };
	vel = vel + acc * dt;

	//if (pos.y < 0) vel.y = -pos.y / dt;

	pos = pos + vel * dt;
}