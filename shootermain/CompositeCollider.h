#ifndef COMPOSITECOLLIDER_H
#define COMPOSITECOLLIDER_H

#include "Collider.h"

class CompositeCollider2D : public Collider2D {
public:
	CompositeCollider2D();

	bool collide(const Collider2D * const other, Collision2D &c) const;

	bool collideCircle(const CircleCollider2D * const other, Collision2D &c) const;
	bool collidePlane(const PlaneCollider2D * const other, Collision2D &c) const;


	void addCollider(Collider2D * const coll){
		colliders.append(coll);
	}

	Array<Collider2D *> colliders;
};

#endif