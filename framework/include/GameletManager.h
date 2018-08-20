#ifndef GAME_H
#define GAME_H

#include "Gamelet.h"
#include "event/EventManager.h"

class GameletManager {
public:
	GameletManager();
	~GameletManager();
	
	void setEventManager(EventManager *manager);

	void registerGamelet(int name, Gamelet *g);

	void transition(Gamelet *g);
	void transition(int name);

	void pushTransition(Gamelet *g);
	void pushTransition(int name);

	void popTransition();

	void run(int name);
	void terminate();

protected:
	void updateCurrentGamelet();

	EventManager *em;

	Gamelet *nextGamelet;
	Gamelet *currentGamelet;

	Array<Gamelet *> gameletStack;
	Table<int, Gamelet *> gamelets;
};

#endif