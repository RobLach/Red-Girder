#ifndef JOYSTICKCONTROL_H
#define JOYSTICKCONTROL_H

#include "PlayerControl.h"
#include "event/JoyEvent.h"

class JoystickControl : public PlayerControl {
public:
	bool handleEvent(Event *e);

protected:
	void translateRawPositionControl();
	void translateRawGunControl();
};


#endif