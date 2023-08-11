#pragma once

#include "mathtypes.h"
#include "aabb.h"

struct Collision {
	vec2 pos1;
	vec2 pos2;
	vec2 penetration1;
	vec2 penetration2;
};

struct Collider;
struct CircleCollider;

struct Collider {
	aabb* bounding_box;
	Collider() {}
	virtual Collision testCollision(CircleCollider* circle, Transform transform) const = 0;
};

struct CircleCollider : public Collider {
	float radius;
	CircleCollider(Transform transform, float radius=1) : radius(radius) {
		vec2 pos = transform.position;
		bounding_box = new aabb(pos - radius, pos + radius, this);
	}
	Collision testCollision(CircleCollider* circle, Transform transform);
};
