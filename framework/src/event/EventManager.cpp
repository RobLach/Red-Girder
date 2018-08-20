#include "stdafx.h"
#include "event/EventManager.h"

EventManager::EventManager(){
	currentEvent = &null;
	ui = 0;
}

EventManager::~EventManager(){
	if(ui) {
		delete ui;
		ui = 0;
	}
}

void EventManager::beginEvents(){
	if(!ui){
		ui = new UserInput();
	}
	ui->beginEvents();
}


bool EventManager::nextEvent(){
	// Event handling
	SDL_Event event;

	/** @todo Have engine distribute render device. */
	while(RenderDevice::lastRenderDeviceCreated->window()->pollEvent(event)) {
		ui->processEvent(event);

		switch(event.type) {

		case SDL_KEYDOWN:
		case SDL_KEYUP:
			keyboard.copyFrom(event);
			currentEvent = &keyboard;
			return true;
			break;

		case SDL_MOUSEBUTTONUP:
		case SDL_MOUSEBUTTONDOWN:
			button.copyFrom(event);
			currentEvent = &button;
			return true;
			break;

		case SDL_MOUSEMOTION:
			motion.copyFrom(event);
			currentEvent = &motion;
			return true;
			break;

		case SDL_JOYAXISMOTION:
			jaxis.copyFrom(event);
			currentEvent = &jaxis;
			return true;
			break;

		case SDL_JOYBUTTONDOWN:
		case SDL_JOYBUTTONUP:
			jbutton.copyFrom(event);
			currentEvent = &jbutton;
			return true;
			break;

		case SDL_JOYHATMOTION:
			jhat.copyFrom(event);
			currentEvent = &jhat;
			return true;
			break;

		case SDL_JOYBALLMOTION:
			jball.copyFrom(event);
			currentEvent = &jball;
			return true;
			break;


		case SDL_ACTIVEEVENT:
			active.copyFrom(event);
			currentEvent = &active;
			return true;
			break;

		case SDL_QUIT:
			quit.copyFrom(event);
			currentEvent = &quit;
			return true;
			break;

		default:
			// Got an unknown event, so try again...
			currentEvent = &null;
		}
	}
	
	// No event to get.
	currentEvent = &null;
	return false;
}

void EventManager::endEvents(){
	ui->endEvents();
}

void EventManager::mousePosition(int *x, int *y){
	Vector2 pos = ui->mouseXY();
	*x = pos.x;
	*y = pos.y;
}

bool EventManager::keyDown(int code){
	return ui->keyDown(code);
}

bool EventManager::keyPressed(int code){
	return ui->keyPressed(code);
}

bool EventManager::keyReleased(int code){
	return ui->keyReleased(code);
}

const std::string EventManager::keyCodeToString(int code) const {
	return UserInput::keyCodeToString(code);
}

int EventManager::stringToKeyCode(const std::string &s) const {
	return UserInput::stringToKeyCode(s);
}


bool EventManager::isActive() const {
	return currentEvent->isActive();
}

bool EventManager::isKeyboard() const {
	return currentEvent->isKeyboard();
}

bool EventManager::isMouseButton() const {
	return currentEvent->isMouseButton();
}

bool EventManager::isMouseMotion() const {
	return currentEvent->isMouseMotion();
}

bool EventManager::isQuit() const {
	return currentEvent->isQuit();
}

bool EventManager::isJoyAxis() const {
	return currentEvent->isJoyAxis();
}

bool EventManager::isJoyButton() const {
	return currentEvent->isJoyButton();
}

bool EventManager::isJoyHat() const {
	return currentEvent->isJoyHat();
}

bool EventManager::isJoyBall() const {
	return currentEvent->isJoyBall();
}
