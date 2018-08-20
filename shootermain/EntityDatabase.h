#ifndef ENTITYDATABASE_H
#define ENTITYDATABASE_H

#include "Entity.h"

class EntityDatabase {
public:
	EntityDatabase();
	~EntityDatabase();

	/** @note add is defered until update() is called. */
	void add(EntityRef const e);

	/** @note remove is defered until update() is called. */
	void remove(EntityRef const e);

	EntityRef get(const int id) const;

	/** Processes pending adds and removes. */
	void update();

	void tick(float deltaT);
	void frame(float deltaT);
	void present(PaperWorld * const world, PaperWorld * const overlay);

	void clear();

	/** How can access to db be controled while still allowing iteration? */
	Table<int, EntityRef> db;

protected:
	Array<int> removeList;
	Array<EntityRef> addList;
};

typedef Table<int, EntityRef>::Iterator DBIterator;

#endif