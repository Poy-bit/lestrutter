#include "collider.h"

Collision CircleCollider::test_collision (CircleCollider* other_collider) {
	if (transform.position.distance(other_collider->transform.position) < radius + other_collider->radius) {
		return Collision();
	}
}
