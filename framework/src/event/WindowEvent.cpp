#include "stdafx.h"
#include "event/WindowEvent.h"
#include "GLG3D/UserInput.h"

//
// Keyboard
//

std::string KeyboardEvent::toString() const {
	char temp[16];

	std::string s =  "Keyboard Event: ";

	s += keyString();
	s += " ";

	s += "(";
	s += itoa(key(), temp, 10);
	s += ") ";

	if(leftAltDown()) s += "LALT ";
	if(rightAltDown()) s += "RALT ";

	if(leftCtrlDown()) s += "LCTRL ";
	if(rightCtrlDown()) s += "RCTRL ";

	if(leftShiftDown()) s += "LSHIFT ";
	if(rightShiftDown()) s += "RSHIFT ";

	if(leftMetaDown()) s += "LMETA ";
	if(rightMetaDown()) s += "RMETA ";

	if(pressed()) s += "pressed ";
	if(released()) s += "released ";

	return s;
}

std::string KeyboardEvent::keyString() const {
	return UserInput::keyCodeToString(key());
}

bool KeyboardEvent::isKeyboard() const {
	return true;
}


void KeyboardEvent::copyFrom(SDL_Event &event){	
	state = event.key.state;
	sym = event.key.keysym.sym;
	mod = event.key.keysym.mod;
	unicode = event.key.keysym.unicode;
}


unsigned int KeyboardEvent::key() const {
	return sym;
}

std::string KeyboardEvent::character() const {
	/** @todo Is this safe? */
	char temp[2];
	temp[0] = (char)unicode;
	temp[1] = 0;
	return temp;
}

bool KeyboardEvent::pressed() const {
	return state == SDL_PRESSED;
}

bool KeyboardEvent::released() const {
	return state == SDL_RELEASED;
}


bool KeyboardEvent::altDown() const {
	return (mod & KMOD_ALT) != 0;
}

bool KeyboardEvent::ctrlDown() const {
	return (mod & KMOD_CTRL) != 0;
}

bool KeyboardEvent::shiftDown() const {
	return (mod & KMOD_SHIFT) != 0;
}

bool KeyboardEvent::metaDown() const {
	return (mod & KMOD_META) != 0;
}

bool KeyboardEvent::leftAltDown() const {
	return (mod & KMOD_LALT) != 0;
}

bool KeyboardEvent::leftCtrlDown() const {
	return (mod & KMOD_LCTRL) != 0;
}

bool KeyboardEvent::leftShiftDown() const {
	return (mod & KMOD_LSHIFT) != 0;
}

bool KeyboardEvent::leftMetaDown() const {
	return (mod & KMOD_LMETA) != 0;
}

bool KeyboardEvent::rightAltDown() const {
	return (mod & KMOD_RALT) != 0;
}

bool KeyboardEvent::rightCtrlDown() const {
	return (mod & KMOD_RCTRL) != 0;
}

bool KeyboardEvent::rightShiftDown() const {
	return (mod & KMOD_RSHIFT) != 0;
}

bool KeyboardEvent::rightMetaDown() const {
	return (mod & KMOD_RMETA) != 0;
}

bool KeyboardEvent::capsLockDown() const {
	return (mod & KMOD_CAPS) != 0;
}

bool KeyboardEvent::numLockDown() const {
	return (mod & KMOD_NUM) != 0;
}


//
// Active
//

std::string ActiveEvent::toString() const {
	std::string s =  "Active Event: ";

	if(active()) s += "active ";
	if(inputFocus()) s += "input focus ";
	if(mouseFocus()) s += "mouse focus ";

	if(gained()) s += "gained ";
	if(lost()) s += "lost ";

	return s;
}

bool ActiveEvent::isActive() const {
	return true;
}


void ActiveEvent::copyFrom(SDL_Event &event){
	gain = event.active.gain != 0;
	state = event.active.state;
}

bool ActiveEvent::gained() const {
	return gain;
}

bool ActiveEvent::lost() const {
	return !gain;
}

bool ActiveEvent::active() const {
	return (state & SDL_APPACTIVE) != 0;
}

bool ActiveEvent::inputFocus() const {
	return (state & SDL_APPINPUTFOCUS) != 0;
}

bool ActiveEvent::mouseFocus() const {
	return (state & SDL_APPMOUSEFOCUS) != 0;
}

//
// Quit
//

std::string QuitEvent::toString() const {
	return "Quit Event";
}

bool QuitEvent::isQuit() const {
	return true;
}

void QuitEvent::copyFrom(SDL_Event &event){
}


//
// Mouse Button
//

std::string MouseButtonEvent::toString() const {
	char temp[16];

	std::string s =  "Mouse Button Event: ";

	if(left()) s += "LEFT ";
	if(middle()) s += "MIDDLE ";
	if(right()) s += "RIGHT ";

	if(pressed()) s += "pressed ";
	if(released()) s += "released ";

	s += "abs(";
	s += itoa(x(), temp, 10);
	s += ", ";
	s += itoa(y(), temp, 10);
	s += ") ";

	return s;
}

bool MouseButtonEvent::isMouseButton() const {
	return true;
}


void MouseButtonEvent::copyFrom(SDL_Event &event){
	button = event.button.button;
	state = event.button.state;
	xCoord = event.button.x;
	yCoord = event.button.y;
}


bool MouseButtonEvent::pressed() const {
	return state == SDL_PRESSED;
}

bool MouseButtonEvent::released() const {
	return state == SDL_RELEASED;
}

bool MouseButtonEvent::left() const {
	return button == SDL_BUTTON_LEFT;
}

bool MouseButtonEvent::middle() const {
	return button == SDL_BUTTON_MIDDLE;
}

bool MouseButtonEvent::right() const {
	return button == SDL_BUTTON_RIGHT;
}

int MouseButtonEvent::x() const {
	return xCoord;
}

int MouseButtonEvent::y() const {
	return yCoord;
}


//
// Mouse Motion
//

std::string MouseMotionEvent::toString() const {
	char temp[16];

	std::string s =  "Mouse Motion Event: ";

	if(left()) s += "LEFT ";
	if(middle()) s += "MIDDLE ";
	if(right()) s += "RIGHT ";

	s += "abs(";
	s += itoa(x(), temp, 10);
	s += ", ";
	s += itoa(y(), temp, 10);
	s += ") ";

	s += "rel(";
	s += itoa(xRel(), temp, 10);
	s += ", ";
	s += itoa(yRel(), temp, 10);
	s += ") ";

	return s;
}

bool MouseMotionEvent::isMouseMotion() const {
	return true;
}


void MouseMotionEvent::copyFrom(SDL_Event &event){
	state		= event.motion.state;
	xCoord		= event.motion.x;
	yCoord		= event.motion.y;
	xRelCoord	= event.motion.xrel;
	yRelCoord	= event.motion.yrel;
}


bool MouseMotionEvent::left() const {
	return (state & SDL_BUTTON(1)) != 0;
}

bool MouseMotionEvent::middle() const {
	return (state & SDL_BUTTON(2)) != 0;
}

bool MouseMotionEvent::right() const {
	return (state & SDL_BUTTON(3)) != 0;
}


int MouseMotionEvent::x() const {
	return xCoord;
}

int MouseMotionEvent::y() const {
	return yCoord;
}
	
int MouseMotionEvent::xRel() const {
	return xRelCoord;
}

int MouseMotionEvent::yRel() const {
	return yRelCoord;
}


Vector2 MouseMotionEvent::abs() const {
	return Vector2(x(), y());
}

Vector2 MouseMotionEvent::rel() const {
	return Vector2(xRel(), yRel());
}

