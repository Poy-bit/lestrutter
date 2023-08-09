#pragma once

#include <vector>
#include "rigidbody.h"

class physics {
	std::vector<Rigidbody*> bodies;
public:
	physics();

	void add_body(Rigidbody* body);
	void remove_body(int index);

	void step(double dt);
};