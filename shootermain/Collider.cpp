#include "stdafx.h"
#include "Collider.h"

#include "CircleCollider.h"
#include "PlaneCollider.h"

#include "Body.h"

Body nullBody;

inline float calculateImpulse(Body &a, Body &b, const float vrel, const float epsilon){
	return -(1+epsilon)*vrel/(a.massInv+b.massInv);
}

/** @todo Add friction. Torque with impulse.*/
bool resolveContact(const ContactPoint &c, Body &a, Body &b, const float epsilon){
	if((a.isPlayer&&b.isShot)||(b.isPlayer&&a.isShot))
		return false;
	Vector2 padot = a.velocityAtPoint(c.pos); 
	Vector2 pbdot = b.velocityAtPoint(c.pos);
	Vector2 n = -c.normal;
	//Vector2 ra = c.pos - a.pos;
	//Vector2 rb = c.pos - b.pos;

	float vrel = n.dot(padot-pbdot);

	// Bomb out if vrel is wrong?
	if(vrel <= 0) return false;

	Vector3 impulse = Vector3(n*calculateImpulse(a, b, vrel, epsilon), 0);
	a.impulseAtPoint(impulse, c.pos);
	b.impulseAtPoint(-impulse, c.pos);
	return true;
}

void correctOverlap(const ContactPoint &c, Body &a, Body &b, const float deltaT){
	Vector2 n = -c.normal;
	const float k = 0.5;
	a.forceAtPoint(Vector3(n*c.depth*k, 0), c.pos, deltaT);
	b.forceAtPoint(Vector3(-n*c.depth*k, 0), c.pos, deltaT);
}

bool resolvePhysicalCollision(const Collision2D &c, Body *a, Body *b, const float epsilon, const float deltaT){
	bool bounce = false;

	nullBody.pos = Vector3::zero();
	nullBody.vel = Vector3::zero();
	nullBody.massInv = 0; // Infinate mass!

	if(a==0) a = &nullBody;
	if(b==0) b = &nullBody;
	if(a == b) return false;

	for(int i=0;i<c.contactPoints.length();i++){
		correctOverlap(c.contactPoints[i], *a, *b, deltaT);
		bounce |= resolveContact(c.contactPoints[i], *a, *b, epsilon);

		//Vector2 normal = c.contactPoints[i].normal;
		//float mag = body->vel.xy().dot(normal);

		//if(mag < 0){ // Is the entity moving INTO the collision?  (Note, should be relative velocities.)
		//	body->vel.x -= 2*normal.x*mag;
		//	body->vel.y -= 2*normal.y*mag;
		//	bounce = true;
		//}
	}
	return bounce;
}


void Collider2D::syncBody(const Body &b){
	translation = b.pos;
	velocity	= b.vel;
}

bool collideCircleCircle(const CircleCollider2D * const a, const CircleCollider2D * const b, Collision2D &c) {
	float minDist = a->radius+b->radius;
	float minDistSQ = minDist*minDist;
	Vector2 disp = b->translation.xy()-a->translation.xy();
	float distSQ = disp.squaredLength();

	if(distSQ < minDistSQ){
		c.eid1 = a->eid;
		c.eid2 = b->eid;

		float dist = sqrt(distSQ);
		float depth = minDist-dist;
		Vector2 n = disp/dist;
		Vector2 p = a->translation.xy()+n*(a->radius-depth*0.5);

		c.addContact(p , n, depth);
		return true;
	}else{
		return false;
	}
}

bool collideCirclePlane(const CircleCollider2D * const a, const PlaneCollider2D * const b, Collision2D &c, float polarity) {
	float depth = b->distance(a->translation.x, a->translation.y)-a->radius;

	if(depth < 0){
		c.eid1 = a->eid;
		c.eid2 = b->eid;


		Vector2 n = -b->normal();
		Vector2 p = a->translation.xy()+n*(a->radius-depth*0.5);

		c.addContact(p, n, depth);

		if(polarity < 0){
			c.flip();
		}

		return true;
	}else{
		return false;
	}
}

bool collidePlaneCircle(const PlaneCollider2D * const a, const CircleCollider2D * const b, Collision2D &c, float polarity) {
	return collideCirclePlane(b, a, c, -polarity);
}
