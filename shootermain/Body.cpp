#include "stdafx.h"

#include "Body.h"

Body::Body(){
	pos = Vector3(0, 0, 0);
	vel = Vector3(0, 0, 0);
	impulse = Vector3(0, 0, 0);
	setMass(1);
	isPlayer = 0;
	isShot = 0;
}

void Body::setMass(float m) {
	mass = m;
	massInv = 1/m;
}

void Body::updateVelocity(float deltaT) {
	vel += impulse*massInv;
	vel.x *= 0.999f;
	vel.y *= 0.999f;
	impulse = Vector3(0, 0, 0);
}

void Body::updatePosition(float deltaT) {
	pos += vel*deltaT;
	while(pos.z > G3D::pi()) pos.z -= 2*G3D::pi();
	while(pos.z < G3D::pi()) pos.z += 2*G3D::pi();
}

void Body::impulseAtCenter(const Vector3 &i){
	impulse += i;
}

/// @todo Take torque into account.
void Body::impulseAtPoint(const Vector3 &i, const Vector2 &p){
	impulse += i;
}

void Body::forceAtCenter(const Vector3 &f, float deltaT){
	impulse += f*deltaT;
}

void Body::forceAtPoint(const Vector3 &f, const Vector2 &p, float deltaT){
	impulse += f*deltaT;
}

void Body::makePlayer()
{
	isPlayer=1;
}

void Body::makeShot()
{
	isShot=1;
}


/// @todo Take angular velocity into account.
Vector2 Body::velocityAtPoint(const Vector2 &p) const {
	return vel.xy();
}
