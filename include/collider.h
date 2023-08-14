#pragma once

#include "mathtypes.h"
#include "aabb.h"

enum eColliderTypes {
	CIRCLE
};

struct Contact {
	vec2 a;
	vec2 b;
	vec2 n;

	Contact() : a({}), b({}) { n = { 0,0 }; }
	Contact(vec2 a, vec2 b) : a(a), b(b) { n = (b - a).normalize(); }
};

struct Rigidbody;
struct Collider;
struct CircleCollider;

struct Collider {
	aabb* bounding_box;
	vec2* position;
	Rigidbody* user;
	eColliderTypes type;

	Collider() {}
	virtual Contact* testCollision(CircleCollider* circle) const = 0;
	virtual void update() = 0;
};

struct CircleCollider: Collider {
	float radius;
	CircleCollider(vec2* pos, float radius=1) : radius(radius) {
		type = eColliderTypes::CIRCLE;
		position = pos;
		bounding_box = new aabb(*position - radius, *position + radius, this);
	}

	Contact* testCollision(CircleCollider* circle) const override {
		if ((*position - *circle->position).length() <= radius + circle->radius) {
			vec2 a = (*circle->position - *position).normalize() * radius + *position;
			vec2 b = (*position - *circle->position).normalize() * radius + *circle->position;
			return new Contact(a, b);
		}
		else {
			return nullptr;
		}
	}

	void update() override {
		bounding_box->min_point = *position - radius;
		bounding_box->max_point = *position + radius;
	}
};
