#pragma once

#include <vector>
#include "rigidbody.h"

class Physics {
	std::vector<Rigidbody*> bodies;
public:
	Physics() {}

	void add_body(Rigidbody* body) {
		bodies.push_back(body);
	}
	void remove_body(int index) {
		bodies.erase(bodies.begin() + index);
	}

	void step(double dt) {
		for (int i = 0; i < bodies.size(); i++) {
			Rigidbody* body = bodies[i];
			body->acc = { 0, 0 };
			body->vel = body->vel + body->acc * dt;

			//if (pos.y < 0) vel.y = -pos.y / dt;

			body->pos = body->pos + body->vel * dt;
		}
	}
};