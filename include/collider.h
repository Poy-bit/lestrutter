#pragma once

#include "mathtypes.h"

struct Collision {
	vec2 pos1;
	vec2 pos2;
	vec2 penetration1;
	vec2 penetration2;
};

struct Collider;
struct CircleCollider;

struct Collider {
	Collider() {}
	virtual Collision testCollision(CircleCollider* circle, Transform transform) const = 0;
};

struct CircleCollider : public Collider {
	float radius;
	CircleCollider(float radius=1) : radius(radius) {}
	Collision testCollision(CircleCollider* circle, Transform transform);
};
