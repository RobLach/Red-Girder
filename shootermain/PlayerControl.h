#ifndef PLAYERCONTROL_H
#define PLAYERCONTROL_H

#include "Enemy.h"

class Event;

inline float sqr(float x){
	return x*x;
}
class PlayerControl {
public:
	PlayerControl();

	void reset();

	void tick(float deltaT);

	virtual bool handleEvent(Event *e) = 0;

	EnemyRef controled;

protected:
	void updateGunAngle();
	virtual void updateControl(float deltaT) {};

	Vector2 gunControl, posControl;
	Vector2 rawPosControl, rawGunControl;
	float gunAngle;

	float maxSpeed;
	float feedbackGain;
};


#endif