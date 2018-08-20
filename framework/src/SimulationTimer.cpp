#include "stdafx.h"
#include "SimulationTimer.h"

SimulationTimer::SimulationTimer(){
	setTickRate(60);
	reset();
	speedMod = 1.0;
	speedModMod =1.0;
}

void SimulationTimer::setTickRate(double rate){
	tickRateVal = rate;
	tickLengthVal = (1/rate);
}

void SimulationTimer::reset(){
	oldTime = newTime = time();
	tickAccum = 0;
	numTicksVal = 0;
	halted = false;
}


void SimulationTimer::startFrame(){
	assert(!halted);
	oldTime = newTime;
	newTime = time();
	tickAccum += newTime-oldTime;
	numTicksVal = floor(tickAccum*tickRateVal);
	tickAccum -= numTicksVal*tickLengthVal;
	if(speedMod<0.2)		//slow motion interping
		speedMod=0.2;
	if(speedMod>1.0)
		speedMod=1.0;

	if(numTicksVal%2==0)
		if((speedMod<=1.0)&&(speedMod>=0.2))
			speedMod=speedMod*speedModMod;

}

double SimulationTimer::timeElapsed() const{
	return newTime-oldTime;
}
 
int SimulationTimer::numTicks() const{

	return numTicksVal;
}

double SimulationTimer::tickLength() const {

	return tickLengthVal*speedMod; // slow motion location
}

void SimulationTimer::pause(){
	assert(!halted);
	pauseTime = time();
	halted = true;
}

void SimulationTimer::resume(){
	assert(halted);
	newTime += time()-pauseTime;
	halted = false;
}

bool SimulationTimer::paused(){
	return halted;
}

double SimulationTimer::frameRate() const{

	return RenderDevice::lastRenderDeviceCreated->getFrameRate(); // HACK
}

double SimulationTimer::time() const {
	return System::getTick();
}
