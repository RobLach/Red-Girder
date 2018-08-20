#ifndef SHOOTERGAMELET_H
#define SHOOTERGAMELET_H

#include "Gamelet.h"
#include "Renderer.h"

class ShooterGamelet : public Gamelet {
protected:
	virtual void handleEvent(Event *e);

	virtual void tick(float deltaT);
	virtual void frame(float deltaT);

	void doPhysics(float deltaT);

	virtual void doRender();
	virtual void present(PaperWorld * const world, PaperWorld * const overlay);

	bool handleMouseControl(Event *e);
	bool handleKeyControl(Event *e);

	void createRandomEnemy();
	void addRemPlayer2();

	void updateCamera();

	void togglePause();

	float fadage;

	void Win();
	void Lose();



	bool paused;

public:

	virtual void onEnter();
	virtual void onExit();

};

#endif