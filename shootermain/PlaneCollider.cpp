#include "stdafx.h"
#include "PlaneCollider.h"

PlaneCollider2D::PlaneCollider2D() : Collider2D(){
	setNormal(1, 0);
	setPosition(0, 0);
}

void PlaneCollider2D::setNormal(float nx, float ny) {
	a = nx;
	b = ny;
}

void PlaneCollider2D::setPosition(float x, float y) {
	c = -(a*x+b*y);
}

float PlaneCollider2D::distance(float x, float y) const {
	return a*x+b*y+c;
}

Vector2 PlaneCollider2D::normal() const {
	return Vector2(a, b);
}


bool PlaneCollider2D::collideCircle(const CircleCollider2D * const other, Collision2D &c) const {
	return collidePlaneCircle(this, other, c);
}

bool PlaneCollider2D::collidePlane(const PlaneCollider2D * const other, Collision2D &c) const {
	//return collidePlanePlane(this, other, c);
	return false; // This collision is meaningless...
}
