#pragma once

#include "rigidbody.h"
#include "mathtypes.h"

class Collision {
public:
	Collision() {}
};

class Collider {
	Transform transform;

public:
	Collider() {}
	Collision test_collision(Collider* other_collider) { return Collision(); }
};

class CircleCollider : public Collider {
	float radius;
	Transform transform;

public:
	CircleCollider(float radius = 1) : radius(radius) {}
	Collision test_collision(CircleCollider* other_collider);
};
