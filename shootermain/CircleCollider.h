#ifndef SPHERECOLLIDER_H
#define SPHERECOLLIDER_H

#include "Collider.h"

class CircleCollider2D : public Collider2D {
public:
	CircleCollider2D();

	bool collide(const Collider2D * const other, Collision2D &c) const {
		return other->collideCircle(this, c);
	}

	bool collideCircle(const CircleCollider2D * const other, Collision2D &c) const;
	bool collidePlane(const PlaneCollider2D * const other, Collision2D &c) const;

	float radius;
};

#endif