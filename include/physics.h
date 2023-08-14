#pragma once

#include <vector>
#include "rigidbody.h"
#include "collider.h"
#include "aabb.h"

class Physics {
	std::vector<Rigidbody*> bodies;
	aabbtree broadphase;
public:
	Physics() {}

	void add_body(Rigidbody* body) {
		broadphase.add(body->body_collider->bounding_box);
		bodies.push_back(body);
	}
	void remove_body(int index) {
		bodies.erase(bodies.begin() + index);
	}

	void step(double dt) {
		for (int i = 0; i < bodies.size(); i++) {
			// Dynamics
			Rigidbody* body = bodies[i];
			body->acc = { 0, 0 };
			body->vel = body->vel + body->acc * dt;
			body->pos = body->pos + body->vel * dt;
			body->body_collider->update();
		}

		std::vector<std::pair<aabb, aabb>> collider_pairs = broadphase.computeColliderPairs();
		for (int i = 0; i < collider_pairs.size(); i++) {
			std::pair<aabb, aabb> collider_pair = collider_pairs[i];
			Collider* first_collider = collider_pair.first.collider;
			Collider* second_collider = collider_pair.second.collider;

			Contact* contact;
			switch (second_collider->type) {
			case(eColliderTypes::CIRCLE):
				contact = first_collider->testCollision((CircleCollider*)second_collider); break;
			}
			if (contact == nullptr) { continue; }
			Rigidbody* body_a = first_collider->user;
			Rigidbody* body_b = second_collider->user;

			vec2 rel_vel = body_b->vel - body_a->vel;

			float e = 1;
			float impulse_magnitude = contact->n.dot(rel_vel);
			vec2 impulse = contact->n * impulse_magnitude;
		
			body_a->vel = body_a->vel + impulse;
			body_b->vel = body_b->vel - impulse;
		}
	}
};