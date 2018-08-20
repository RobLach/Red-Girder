#include "stdafx.h"
#include "PlayerControl.h"

PlayerControl::PlayerControl(){
	reset();

	maxSpeed = 6;
	feedbackGain = 3;
}

void PlayerControl::reset(){
	posControl.zero();
	gunControl.zero();
	rawPosControl.zero();
	rawGunControl.zero();
	gunAngle = 0;
}

void PlayerControl::updateGunAngle(){
	// Don't calculate the angle if the gun control vector is near zero.
	float lsq = gunControl.squaredLength();
	if(lsq > 0.01){
		gunAngle = atan2(-gunControl.x, gunControl.y);
	}
}

void PlayerControl::tick(float deltaT){
	if(controled.isNull()) return;

	updateControl(deltaT);

	Vector2 controlForce = (posControl*maxSpeed-controled->body.vel.xy())*feedbackGain;
	controled->body.forceAtCenter(Vector3(controlForce, 0), deltaT);

	controled->gunAngle = gunAngle;
}
