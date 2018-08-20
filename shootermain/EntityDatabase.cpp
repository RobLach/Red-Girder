#include "stdafx.h"
#include "EntityDatabase.h"

int Entity::currentID = 100;

EntityDatabase::EntityDatabase(){
}

EntityDatabase::~EntityDatabase(){
	addList.clear();
	removeList.clear();
	db.clear();
}

void EntityDatabase::add(const EntityRef e){
	addList.append(e);
}

EntityRef EntityDatabase::get(const int id) const {
	if(db.containsKey(id)){
		return db.get(id);
	}else{
		return 0;
	}
}

void EntityDatabase::remove(const EntityRef e){
	removeList.append(e->id());
}

void EntityDatabase::update(){
	if(removeList.length() > 0){
		for(Array<int>::Iterator it = removeList.begin(); it != removeList.end(); it++){
			if(db.containsKey(*it)){
				db.remove(*it);
			}
		}		
		removeList.clear();
	}

	if(addList.length() > 0){
		for(Array<EntityRef>::Iterator it = addList.begin(); it != addList.end(); it++){
			db.set((*it)->id(), (*it));
		}
		addList.clear();
	}
}

void EntityDatabase::tick(float deltaT){
	for(DBIterator it = db.begin(); it != db.end(); it++){
		it->value->tick(deltaT);
	}

	update();
}

void EntityDatabase::frame(float deltaT) {
	for(DBIterator it = db.begin(); it != db.end(); it++){
		it->value->frame(deltaT);
	}

	update();
}

void EntityDatabase::present(PaperWorld * const world, PaperWorld * const overlay) {
	for(DBIterator it = db.begin(); it != db.end(); it++){
		it->value->present(world, overlay);
	}

	update();
}

void EntityDatabase::clear(){
	removeList.clear();
	addList.clear();
	db.clear();
}
