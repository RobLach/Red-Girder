#include "stdafx.h"
#include "JoystickControl.h"

void JoystickControl::translateRawGunControl() {
	// Only update gun angle if the joystick is out of the dead zone.
	float lsq = rawGunControl.squaredLength();
	if(lsq >= sqr(0.3)){
		gunControl = rawGunControl;
		updateGunAngle();
	}
}

void JoystickControl::translateRawPositionControl() {

	float lsq = rawPosControl.squaredLength();
	if(lsq >= sqr(0.1)){ // Threshold.
		posControl = rawPosControl;

		float len = sqrt(lsq);

		// Clamp the control vector's length.
		if(len>1){
			posControl /= len;
			len = 1;
		}

		posControl *= len;  // Nonlinear warp.
	}else{
		posControl.zero();
	}
}


bool JoystickControl::handleEvent(Event *e) {
	if(controled.isNull()) return false;

	if(e->isJoyAxis()){
		JoyAxisEvent *jae = static_cast<JoyAxisEvent *>(e);
		if(jae->axis() == 0){
			rawPosControl.x = jae->valueAsFloat();
			translateRawPositionControl();
			return true;
		}

		if(jae->axis() == 1){
			rawPosControl.y = jae->valueAsFloat();
			translateRawPositionControl();
			return true;
		}

		if(jae->axis() == 2){
			rawGunControl.x = jae->valueAsFloat();
			translateRawGunControl();
			return true;
		}

		if(jae->axis() == 3){
			rawGunControl.y = jae->valueAsFloat();
			translateRawGunControl();
			return true;
		}
	}

	if(e->isJoyButton()){
		JoyButtonEvent *jbe = static_cast<JoyButtonEvent *>(e);
		if(jbe->button() == 6-1){
			controled->gunActive = jbe->pressed();
			controled->gunType = 0;
			return true;
		}else if(jbe->button() == 8-1){
			controled->gunActive = jbe->pressed();
			controled->gunType = 1;
			return true;
		}

	}

	return false;
}