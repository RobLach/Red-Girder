#ifndef SIMULATION_TIMER_H
#define SIMULATION_TIMER_H

/** @brief Simulation timer.

SimulationTimer keeps track of timing issues for the simulation. 
*/
class SimulationTimer { //tolua_export
public:
	//tolua_begin
	SimulationTimer();
	float speedMod;
	float speedModMod;

	/** Sets the number of ticks the simulation timer generates per second. */
	void setTickRate(double rate);

	/** Called once per loop iteration. */
	void startFrame();

	/** Gets the number of seconds since the last call to startFrame(). */
	double timeElapsed() const;

	/** Gets the number of simulation ticks that should be executed in this loop iteration. */
	int numTicks() const;
	
	/** Gets the duration of a single tick. */
	double tickLength() const;

	/** Pauses the timer.  Prevents ticks from accumulating.*/
	void pause();

	bool paused();

	/** Unpauses the timer.*/
	void resume();

	/** Completely resets the internal state of the timer.*/
	void reset();

	double frameRate() const;

	/** Gets the system time, not the simulation time. */
	double time() const;

	//tolua_end
private:
	double tickRateVal;
	double tickLengthVal;

	double oldTime, newTime, tickAccum;
	double pauseTime;
	int numTicksVal;
	

	bool halted;
}; //tolua_export

#endif