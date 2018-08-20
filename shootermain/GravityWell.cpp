#include "stdafx.h"
#include "GravityWell.h"

GravityWell::GravityWell() {
	pos = Vector2(5.9, 4.2);
	strength = 5;
}


void GravityWell::apply(Body &b, float deltaT) const {
	Vector2 disp = pos-b.pos.xy();
	float distsq = disp.squaredLength();
	if(distsq > 0.00001){
		disp /= sqrt(distsq)*distsq;
		disp *= strength;
		b.forceAtCenter(Vector3(disp.xy(), 0)*b.mass, deltaT);
	}
}