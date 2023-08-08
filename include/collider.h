#pragma once

#include "rigidbody.h"

class Collision {
public:
	Collision() 
};

class Collider {
public:
	Collider();
	virtual Collision test_collision(CircleCollider* other_collider) {}
};

class CircleCollider: Collider {
	float radius;
	vec2 position;

public:
	CircleCollider(float radius = 1) : radius(radius) {}
	Collision test_collision(CircleCollider* other_collider) {
		if (position.distance(other_collider->position) < radius + other_collider->radius) {
			return
		}
	}
};