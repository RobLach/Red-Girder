#include "stdafx.h"
#include "event/Event.h"

//
// Event
//

bool Event::isActive() const {
	return false;
}

bool Event::isKeyboard() const {
	return false;
}

bool Event::isMouseButton() const {
	return false;
}

bool Event::isMouseMotion() const {
	return false;
}

bool Event::isQuit() const {
	return false;
}

bool Event::isJoyAxis() const {
	return false;
}

bool Event::isJoyButton() const {
	return false;
}

bool Event::isJoyHat() const {
	return false;
}

bool Event::isJoyBall() const {
	return false;
}


//
// Null
//

std::string NullEvent::toString() const {
	return "Null Event";
}

void NullEvent::copyFrom(SDL_Event &event){
}