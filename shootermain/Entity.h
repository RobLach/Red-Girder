#ifndef ENTITY_H
#define ENTITY_H

#include "SmartPtr.h"

class PaperWorld;
class Body;
class Collider2D;
class Collision2D;

typedef SmartPointerRef<class Entity> EntityRef;

/** @brief The superclass for all game objects.

Entity defines the 
*/
class Entity : public SmartPointerBase {
public:
	Entity() {
		setID(currentID);
		currentID++;
	}

	virtual ~Entity() {}

	void setID(int id){
		eid = id;
	}

	/** Each Entity is assigned a unique ID, and all comunication between Entities is done
	via ID, rather than through a native pointer.  This indirection is used so dangling references can be detected.
	*/
	int id() const {
		return eid;
	}

	/** Tick is called at a fixed frequency.  
	(60 Hz is typical, although the exact rate is a matter of preference.)
	Unless the system changes the tick rate in an adaptive manner, deltaT should be 
	the same every time tick is called.
	Gameplay-critical simulation logic should be performed inside the tick function,
	so it will not be influenced by the frame rate.
	*/
	virtual void tick(float deltaT) {};

	/** Frame is called before each frame is rendered.
	As deltaT can vary upredictabally, only logic that does not affect the gameplay should
	be preformed inside the frame function.
	*/
	virtual void frame(float deltaT) {};

	/** Present rendereables to the renderer. */
	virtual void present(PaperWorld * const world, PaperWorld * const overlay) {};

	virtual void collide(const Collision2D &c) {};

	virtual void configure(const std::string &name) {};

	/** @todo UNHACK */
	virtual void damage(float amt) {};
	virtual int getTeam() {
		return -1;
	}

	/** @todo UNHACK */
	virtual Body * getBody() {
		return 0;
	}

	/** @todo UNHACK */
	virtual Collider2D * getCollider() {
		return 0;
	}

protected:
	int eid;

	static int currentID;
};
#endif