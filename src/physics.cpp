#include "physics.h"

physics::physics() {}

void physics::add_body(rigidbody* body) {
	bodies.push_back(body);
}

void physics::remove_body(int index) {
	bodies.erase(bodies.begin() + index);
}

void physics::step(double dt) {
	for (int i = 0; i < bodies.size(); i++) {
		bodies[i]->step(dt);
	}
}