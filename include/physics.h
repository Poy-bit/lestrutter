#pragma once

#include <vector>
#include "rigidbody.h"

class physics {
	std::vector<rigidbody*> bodies;
public:
	physics();

	void add_body(rigidbody* body);
	void remove_body(int index);

	void step(double dt);
};