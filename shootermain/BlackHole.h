#ifndef BLACKHOLE_H
#define BLACKHOLE_H

#include "Entity.h"
#include "Body.h"
#include "Tile.h"

#include "GravityWell.h"

#include "CircleCollider.h"

class BlackHole : public Entity {
public:

	virtual void configure(const std::string &name);
	virtual void tick(float deltaT);
	virtual void frame(float deltaT);

	float getX();
	float getY();

	void setSize(float size);

	virtual void collide(const Collision2D &c);

	virtual void present(PaperWorld * const world, PaperWorld * const overlay);

		
	//virtual Body * getBody() {
	//	return &body;
	//}

	virtual Collider2D * getCollider() {
		return &collider;
	}

	GravityWell gw;

protected:
	void setTexture(const NixTextureRef &t);

	Tile rep;

	//Body body;
	CircleCollider2D collider;

	Vector2 pos;


	float twitch;
	float pulse;
};

#endif