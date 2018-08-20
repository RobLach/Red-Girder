#ifndef PLANECOLLIDER_H
#define PLANECOLLIDER_H

#include "Collider.h"

class PlaneCollider2D : public Collider2D {
public:
	PlaneCollider2D();

	bool collide(const Collider2D * const other, Collision2D &c) const {
		return other->collidePlane(this, c);
	}

	void setNormal(float nx, float ny);
	void setPosition(float x, float y);

	float distance(float x, float y) const;
	Vector2 normal() const;

	bool collideCircle(const CircleCollider2D * const other, Collision2D &c) const;
	bool collidePlane(const PlaneCollider2D * const other, Collision2D &c) const;

protected:
	float a, b, c;  // ax+by+c == distance from plane.  positive means outside, negative means inside;
};

#endif