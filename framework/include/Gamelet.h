#ifndef GAMELET_H
#define GAMELET_H

#include "event/EventManager.h"
#include "SimulationTimer.h"

class Gamelet {
protected:
	virtual void handleEvent(Event *e) = 0;
	virtual void doInput(EventManager * const em);
	virtual void doRender() = 0;

	virtual void doSimulation();

	virtual void tick(float deltaT) = 0;
	virtual void frame(float deltaT) = 0;

public:
	Gamelet();

	virtual void onEnter() = 0;
	virtual void onExit() = 0;

	virtual void doSingleFrame(EventManager * const em);
	SimulationTimer timer;

protected:
	

	bool dirty;
	bool forceDirty;
};

#endif