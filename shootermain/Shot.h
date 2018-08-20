#ifndef SHOT_H
#define SHOT_H

#include "Entity.h"
#include "Body.h"
#include "Tile.h"

#include "CircleCollider.h"

#include "fmod.hpp"

class Shot : public Entity {
public:
	virtual void configure(const std::string &name);
	virtual void setDirect(bool isRight);

	virtual void tick(float deltaT);
	virtual void collide(const Collision2D &c);

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

	void ttlExpire();
	float rocketMovement;
	Body body;
	Tile rep;
	CircleCollider2D collider;
	
	//added for some mega awesome shot physics.
	float properX;
	float properY;

	int rocket;
	float damage;
	float impulse;
	float fireAngle;
	int numBounce;
	float ttl;
	int rotates;
	float mass;
	int hurts; //indicates which team this shot hurts
	float bounceMod;
	int explodes;
	float velocity;
	float initFireAngle;
	bool directRight;

	std::string soundFile;
	std::string soundFile2;
	//sound parameters
	FMOD::Sound *sound;
	FMOD::Sound *sound2;
	float volume;



};

#endif