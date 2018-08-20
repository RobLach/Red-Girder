#include "stdafx.h"
#include "CircleCollider.h"

CircleCollider2D::CircleCollider2D() : Collider2D(){
	radius = 0.5;
}

bool CircleCollider2D::collideCircle(const CircleCollider2D * const other, Collision2D &c) const {
	return collideCircleCircle(this, other, c);
}

bool CircleCollider2D::collidePlane(const PlaneCollider2D * const other, Collision2D &c) const {
	return collideCirclePlane(this, other, c);
}
