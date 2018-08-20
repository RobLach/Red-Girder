#include "stdafx.h"
#include "GameletManager.h"

GameletManager::GameletManager(){
	currentGamelet = 0;
	em = 0;
}

GameletManager::~GameletManager(){
	currentGamelet = 0;
	em = 0;
}

void GameletManager::setEventManager(EventManager *manager){
	em = manager;
}


void GameletManager::registerGamelet(int name, Gamelet *g){
	gamelets.set(name, g);
}

void GameletManager::updateCurrentGamelet() {
	if(nextGamelet != currentGamelet){
		if(currentGamelet != 0){
			currentGamelet->onExit();
		}

		currentGamelet = nextGamelet;

		if(currentGamelet != 0){
			currentGamelet->onEnter();
		}
	}
}

void GameletManager::pushTransition(int name){
	if(gamelets.containsKey(name)){
		pushTransition(gamelets.get(name));
	}else{
		terminate();
	}
}

void GameletManager::pushTransition(Gamelet *g){
	gameletStack.push(currentGamelet);
	transition(g);
}

void GameletManager::popTransition(){
	Gamelet *g = gameletStack.pop();
	transition(g);
}

void GameletManager::transition(Gamelet *g) {
	nextGamelet = g;
}

void GameletManager::transition(int name) {
	if(gamelets.containsKey(name)){
		transition(gamelets.get(name));
	}else{
		terminate();
	}
}

void GameletManager::run(int name){
	gameletStack.clear();
	transition(name);
	updateCurrentGamelet();

	while(currentGamelet != 0){
		currentGamelet->doSingleFrame(em);
		updateCurrentGamelet();
	}
}

void GameletManager::terminate(){
	transition((Gamelet *)0);
}