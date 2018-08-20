#include "stdafx.h"
#include "MouseControl.h"

#include "ShooterState.h"

void MouseControl::translateRawGunControl() {
	gunControl = rawGunControl - controled->body.pos.xy();
	updateGunAngle();
}

void MouseControl::translateRawPositionControl() {
	float lsq = rawPosControl.squaredLength();
	posControl = rawPosControl;

	// Clamp the control vector's length.
	if(lsq>1){
		float len = sqrt(lsq);
		posControl /= len;
	}
}

void MouseControl::updateControl(float deltaT) {
	// Keep the gun aimed at the mouse cursor.
	translateRawGunControl();
}

bool MouseControl::handleEvent(Event *e) {
	if(controled.isNull()) return false;

	if (e->isMouseMotion()){
		MouseMotionEvent *mme = static_cast<MouseMotionEvent *>(e);
		rawGunControl = r.screenToWorld(mme->x(), mme->y());
		translateRawGunControl();
		return true;
	}else if(e->isKeyboard()){
		KeyboardEvent *ke = static_cast<KeyboardEvent *>(e);
		
		if(ke->key() == config.key.up){
			if(ke->pressed())
				rawPosControl.y -= 3;
			else
				rawPosControl.y += 3;
			translateRawPositionControl();
			return true;
		}else if(ke->key() == config.key.down){
			if(ke->pressed())
                rawPosControl.y += 3;
			else
				rawPosControl.y -= 3;
			translateRawPositionControl();
			return true;
		}else if(ke->key() == config.key.left){
			if(ke->pressed())
                rawPosControl.x -= 3;
			else
				rawPosControl.x += 3;
			translateRawPositionControl();
			return true;
		}else if(ke->key() == config.key.right){
			if(ke->pressed())
                rawPosControl.x += 3;
			else
				rawPosControl.x -= 3;
			translateRawPositionControl();
			return true;
		}else if(ke->key() == config.key.slowmo){
			if(ke->pressed()){
					mainGamelet.timer.speedModMod = 0.9;
					shawnssystem->setFrequency(globalFreq / 1.5);
					}
			else{
					mainGamelet.timer.speedModMod = 1.2;
					shawnssystem->setFrequency(globalFreq * 1.5);
					}
			return true;
		}
	}else if(e->isMouseButton()){
		MouseButtonEvent *mbe = static_cast<MouseButtonEvent *>(e);
		if(mbe->left()){
			controled->gunActive = mbe->pressed();
			controled->gunType = 0;
			return true;
		}else if(mbe->right()){
			controled->gunActive = mbe->pressed();
			controled->gunType = 1;
			return true;
		}
		
	}


	return false;
}