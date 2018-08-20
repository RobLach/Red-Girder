#ifndef JOYEVENT_H
#define JOYEVENT_H

#include "event/Event.h"

/** @brief Joystick Axis Event.

The event corresponds to the movement of an analog control on a joystick.  
For example, a PS2-style game pad can send axis events for four different axis: 
one for the x-axis and one for the y-axis of each analog control.
On the Logitech Rumblepad 2, the left analog identifies the x-axis and y-axis as '0' and '1', respectively.
Similarly, the right analog identifies the x-axis and y-axis as '2' and '3'.
*/
class JoyAxisEvent : public Event {
public:
	virtual std::string toString() const;

	/** Which joystick caused the event? */
	int joystick() const;

	/** Which analog axis on the joystick does this event correspond to? */
	int axis() const;

	/** What was the integer value of the axis? [-32768, 32767] */
	int value() const;

	/** What was the floating-point value of the axis? [-1.0, 1.0] */
	float valueAsFloat() const;

	virtual bool isJoyAxis() const;

	virtual void copyFrom(SDL_Event &event);

private:
	int whichJoystick;
	int whichAxis;
	int rawValue;
};

/** @brief Joystick Button Event.

This event is sent whenever a button on a joystick is pressed or released.
*/
class JoyButtonEvent : public Event {
public:
	virtual std::string toString() const;

	/** Which joystick caused the event? */
	int joystick() const;

	/** Which button on the joystick does this event correspond to? */
	int button() const;

	/** Was the button that caused this event pressed? */
	bool pressed() const;

	/** Was the button that caused this event released? */
	bool released() const;

	virtual bool isJoyButton() const;

	virtual void copyFrom(SDL_Event &event);
private:
	int whichJoystick;
	int whichButton;
	int state;
};

/** @brief Joystick Hat Event.

This event is sent whenever a hat on a joystick changes state.  
On a gamepad, the d-pad is ususally considered a hat.
*/
class JoyHatEvent : public Event {
public:
	virtual std::string toString() const;

	/** Which joystick caused the event? */
	int joystick() const;

	/** Which hat on the joystick does this event correspond to? */
	int hat() const;

	/** Is the hat in a neutral position?  Mutually exclusive with up, down, left, and right.*/
	bool centered() const;

	/** Is the hat pushed up?  Mutually exclusive with down and centered.*/
	bool up() const;

	/** Is the hat pushed down?  Mutually exclusive with up and centered.*/
	bool down() const;

	/** Is the hat pushed left?  Mutually exclusive with right and centered.*/
	bool left() const;

	/** Is the hat pushed right?  Mutually exclusive with left and centered.*/
	bool right() const;

	virtual bool isJoyHat() const;

	virtual void copyFrom(SDL_Event &event);

private:
	int whichJoystick;
	int whichHat;
	int value;
};

/** @brief Joystick Hat Event.

This class is entirely untested.  In theory, it correspond to a trackball on a joystick.
@todo Test JoyBallEvent
*/
class JoyBallEvent : public Event {
public:
	virtual std::string toString() const;

	int joystick() const;
	int ball() const;

	int xRel() const;
	int yRel() const;

	virtual bool isJoyBall() const;

	Vector2 rel() const;

	virtual void copyFrom(SDL_Event &event);

private:
	int whichJoystick;
	int whichBall;
	int xRelAmt, yRelAmt;
};

#endif