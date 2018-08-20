/**

  @file Event.h

  @author Nick Bray, nbray1@uiuc.edu

 */

#ifndef EVENT_H
#define EVENT_H

/** @brief Abstract event superclass.

A interface for other event classes.
*/
class Event { //tolua_export
public:
	//tolua_begin
	/** Returns a textual representation of the event.  Useful for debugging. */
	virtual std::string toString() const = 0;

	/** Returns true if the event is an active event. */
	virtual bool isActive() const;

	/** Returns true if the event is a keyboard event. */
	virtual bool isKeyboard() const;

	/** Returns true if the event is a mouse button event. */
	virtual bool isMouseButton() const;

	/** Returns true if the event is a mouse motion event. */
	virtual bool isMouseMotion() const;

	/** Returns true if the event is a quit event. */
	virtual bool isQuit() const;

	/** Returns true if the event is a joystick axis event. */
	virtual bool isJoyAxis() const;

	/** Returns true if the event is a joystick button event. */
	virtual bool isJoyButton() const;

	/** Returns true if the event is a joystick hat event. */
	virtual bool isJoyHat() const;

	/** Returns true if the event is a joystick trackball event. */
	virtual bool isJoyBall() const;



	//tolua_end

	/** Copys the event from a corrisponding SDL event. 
	* @todo Decouple, so the event class is not dependant on SDL.
	*/
	virtual void copyFrom(SDL_Event &event) = 0;

}; //tolua_export

/** @brief A null event, used by the EventManager. 

NullEvent is used to prevent the EventManager from having a null pointer to the "current event"
when there is, in fact, no current event.
*/
class NullEvent : public Event {
public:
	virtual std::string toString() const;
	virtual void copyFrom(SDL_Event &event);
};

#endif // EVENT_H