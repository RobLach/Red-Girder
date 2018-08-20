#include "stdafx.h"
#include "CompositeCollider.h"


CompositeCollider2D::CompositeCollider2D() : Collider2D(){
	colliders.clear();
}

bool CompositeCollider2D::collide(const Collider2D * const other, Collision2D &c) const {
	bool status = false;

	for(int i=0;i<colliders.length();i++){
		status |= colliders[i]->collide(other, c);
	}

	return status;
}

bool CompositeCollider2D::collideCircle(const CircleCollider2D * const other, Collision2D &c) const {
	bool status = false;

	for(int i=0;i<colliders.length();i++){
		status |= colliders[i]->collideCircle(other, c);
	}

	return status;
}

bool CompositeCollider2D::collidePlane(const PlaneCollider2D * const other, Collision2D &c) const {
	bool status = false;

	for(int i=0;i<colliders.length();i++){
		status |= colliders[i]->collidePlane(other, c);
	}

	return status;
}

