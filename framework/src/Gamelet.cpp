#include "stdafx.h"
#include "Gamelet.h"

Gamelet::Gamelet(){
	dirty = false;
	forceDirty = false;
}

void Gamelet::doInput(EventManager * const em){
	em->beginEvents();
	while(em->nextEvent()){
		handleEvent(em->currentEvent);
	}
	em->endEvents();
}

void Gamelet::doSimulation(){
	// Fixed rate ticks.
	int ticks = timer.numTicks();

	for(int i=0;i<ticks;i++){
		tick(timer.tickLength());
	}

	frame(timer.timeElapsed());
}

void Gamelet::doSingleFrame(EventManager * const em){
	timer.startFrame();

	if(em != 0){
		doInput(em);
	}

	doSimulation();

	if(dirty || forceDirty){
		doRender();
		dirty = false;
	}
}