#include "stdafx.h"
#include "event/JoyEvent.h"

std::string JoyAxisEvent::toString() const {
	char temp[16];

	std::string s =  "Joystick Axis Event: ";

	s += "joystick ";
	s += itoa(joystick(), temp, 10);

	s += " axis ";
	s += itoa(axis(), temp, 10);

	s += " value ";
	sprintf(temp, "%f", valueAsFloat());
	s += temp;

	return s;
}

int JoyAxisEvent::joystick() const {
	return whichJoystick;
}

int JoyAxisEvent::axis() const {
	return whichAxis;
}

int JoyAxisEvent::value() const {
	return rawValue;
}

float JoyAxisEvent::valueAsFloat() const {
	return rawValue > 0 ? rawValue/32767.0f : rawValue/32768.0f;
}


bool JoyAxisEvent::isJoyAxis() const {
	return true;
}

void JoyAxisEvent::copyFrom(SDL_Event &event){
	whichJoystick = event.jaxis.which;
	whichAxis = event.jaxis.axis;
	rawValue = event.jaxis.value;
}



std::string JoyButtonEvent::toString() const {
	char temp[16];

	std::string s =  "Joystick Button Event: ";

	s += "joystick ";
	s += itoa(joystick(), temp, 10);

	s += " button ";
	s += itoa(button(), temp, 10);


	if(pressed()) s += " pressed";
	if(released()) s += " released";

	return s;
}

int JoyButtonEvent::joystick() const {
	return whichJoystick;
}

int JoyButtonEvent::button() const {
	return whichButton;
}

bool JoyButtonEvent::pressed() const {
	return state == SDL_PRESSED;
}

bool JoyButtonEvent::released() const {
	return state == SDL_RELEASED;
}

bool JoyButtonEvent::isJoyButton() const {
	return true;
}

void JoyButtonEvent::copyFrom(SDL_Event &event){
	whichJoystick = event.jbutton.which;
	whichButton = event.jbutton.button;
	state = event.jbutton.state;
}



std::string JoyHatEvent::toString() const {
	char temp[16];

	std::string s =  "Joystick Hat Event: ";

	s += "joystick ";
	s += itoa(joystick(), temp, 10);

	s += " hat ";
	s += itoa(hat(), temp, 10);


	if(centered()) s += " centered";
	if(up()) s += " up";
	if(down()) s += " down";
	if(left()) s += " left";
	if(right()) s += " right";

	return s;
}

int JoyHatEvent::joystick() const {
	return whichJoystick;
}

int JoyHatEvent::hat() const {
	return whichHat;
}

bool JoyHatEvent::centered() const {
	return value == SDL_HAT_CENTERED;   // CENTERED in zero (?) so it can't be used as a bitmask.
}

bool JoyHatEvent::up() const {
	return (value & SDL_HAT_UP) != 0;
}

bool JoyHatEvent::down() const {
	return (value & SDL_HAT_DOWN) != 0;
}

bool JoyHatEvent::left() const {
	return (value & SDL_HAT_LEFT) != 0;
}

bool JoyHatEvent::right() const {
	return (value & SDL_HAT_RIGHT) != 0;
}

bool JoyHatEvent::isJoyHat() const {
	return true;
}

void JoyHatEvent::copyFrom(SDL_Event &event){
	whichJoystick = event.jhat.which;
	whichHat = event.jhat.hat;
	value = event.jhat.value;
}


std::string JoyBallEvent::toString() const {
	char temp[16];

	std::string s =  "Joystick Ball Event: ";

	s += "joystick ";
	s += itoa(joystick(), temp, 10);

	s += " ball ";
	s += itoa(ball(), temp, 10);

	s += " rel(";
	s += itoa(xRel(), temp, 10);
	s += ", ";
	s += itoa(yRel(), temp, 10);
	s += ") ";

	return s;
}

int JoyBallEvent::joystick() const {
	return whichJoystick;
}

int JoyBallEvent::ball() const {
	return whichBall;
}

bool JoyBallEvent::isJoyBall() const {
	return true;
}

void JoyBallEvent::copyFrom(SDL_Event &event){
	whichJoystick = event.jball.which;
	whichBall = event.jball.ball;
	xRelAmt = event.jball.xrel;
	yRelAmt = event.jball.yrel;
}

int JoyBallEvent::xRel() const {
	return xRelAmt;
}

int JoyBallEvent::yRel() const {
	return yRelAmt;
}

Vector2 JoyBallEvent::rel() const {
	return Vector2(xRel(), yRel());
}
