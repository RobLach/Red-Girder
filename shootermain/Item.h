#ifndef ITEM_H
#define ITEM_H
//THINGS TO DO
/*
make it so that when you create an icon for powerups, 
you make it a physical body so that when the player collides with 
it, you can have it disapear.  Don't include it in the entity database
so gravity wont act on it
*/
#include "Entity.h"
#include "Body.h"
#include "Tile.h"
#include "CircleCollider.h"

class Item : public Entity {
public:	
	
	virtual void configure(const std::string &name);

	virtual void tick(float deltaT);
	
	virtual void collide(const Collision2D &c);
	virtual void doEffect(EntityRef e) = 0;
	virtual void ttlExpire();

	virtual void present(PaperWorld * const world, PaperWorld * const overlay);
	void setTrajectory(const Vector3 &pos, const Vector3 &vel);


	virtual Body * getBody() {
		return &body;
	}
	virtual Collider2D * getCollider() {
		return &collider;
	}

protected:

	void setSize(float size);
	void setTexture(const NixTextureRef &t);

	Body body;
	Tile icon;
	CircleCollider2D collider;

	float ttl;
	int uses;

	//team it affects
	int affects;
};

class HealthItem : public Item {
	virtual void doEffect(EntityRef e);
	virtual void configure(const std::string &name);

	int amount;
};
#endif
