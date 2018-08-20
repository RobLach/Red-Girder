#ifndef MOUSECONTROL_H
#define MOUSECONTROL_H

#include "PlayerControl.h"
#include "event/WindowEvent.h"

class MouseControl : public PlayerControl {
public:
	bool handleEvent(Event *e);

	void updateControl(float deltaT);

protected:
	void translateRawPositionControl();
	void translateRawGunControl();
};


#endif