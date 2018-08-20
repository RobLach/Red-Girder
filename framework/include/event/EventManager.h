/**

  @file EventManager.h

  @author Nick Bray, nbray1@uiuc.edu

 */


#ifndef  EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include "event/Event.h"
#include "event/WindowEvent.h"
#include "event/JoyEvent.h"

class EventManager { //tolua_export
public:
	// tolua_begin
	EventManager();
	~EventManager();

	ActiveEvent active;
	KeyboardEvent keyboard;
	QuitEvent quit;
	MouseMotionEvent motion;
	MouseButtonEvent button;

	JoyAxisEvent jaxis;
	JoyButtonEvent jbutton;
	JoyHatEvent jhat;
	JoyBallEvent jball;


	/** Called at the start of event processing. */
	void beginEvents();
	
	/** Called to get the next event.
	@return True if an event was aquired. */
	bool nextEvent();

	/** Called at the end of event processing. */
	void endEvents();

	/** Returns true if the event is an active event. */
	bool isActive() const;

	/** Returns true if the event is a keyboard event. */
	bool isKeyboard() const;

	/** Returns true if the event is a mouse button event. */
	bool isMouseButton() const;

	/** Returns true if the event is a mouse motion event. */
	bool isMouseMotion() const;

	/** Returns true if the event is a quit event. */
	bool isQuit() const;

	/** Returns true if the event is a joystick axis event. */
	bool isJoyAxis() const;

	/** Returns true if the event is a joystick button event. */
	bool isJoyButton() const;

	/** Returns true if the event is a joystick hat event. */
	bool isJoyHat() const;

	/** Returns true if the event is a joystick trackball event. */
	bool isJoyBall() const;

	bool keyDown(int code);
	bool keyPressed(int code);
	bool keyReleased(int code);

	/** Gets the position of the mouse.  Funky syntax is for easy binding to lua. */
	void mousePosition(int *x, int *y);

	const std::string keyCodeToString(int code) const;
	int stringToKeyCode(const std::string &s) const ;
	//tolua_end


	Event *currentEvent;
protected:
	NullEvent null;

	UserInput *ui;
}; //tolua_export

#endif