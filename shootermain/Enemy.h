#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"
#include "Body.h"
#include "Tile.h"

#include "CircleCollider.h"

typedef SmartPointerRef<class Enemy> EnemyRef;

class PlayerControl;
class MouseControl;
class JoystickControl;

#include "fmod.hpp"

class Enemy : public Entity {
public:
	virtual void configure(const std::string &name);

	virtual void tick(float deltaT);
	virtual void frame(float deltaT);

	virtual void aim(float deltaT) {};
	virtual void fire(float deltaT) {};


	virtual void collide(const Collision2D &c);

	virtual void present(PaperWorld * const world, PaperWorld * const overlay);

	void setTrajectory(const Vector3 &pos, const Vector3 &vel);

	virtual int getTeam();
	virtual void damage(float amt);
	virtual void die();

	virtual Body * getBody() {
		return &body;
	}
	virtual Collider2D * getCollider() {
		return &collider;
	}

//protected:
	void setTextures(const NixTextureRef &top, const NixTextureRef &middle);
	void setSize(float size);

	friend PlayerControl;
	friend MouseControl;
	friend JoystickControl;

	Body body;
	Tile topLayer;
	Tile middleLayer;
	CircleCollider2D collider;
	int team;
	int LOLastShot;

	float shoot(const std::string &shotType);

	float	gunCooldown;
	float	gunCooldownMax;
	float	hitpoints;
	float	maxhitpoints;

	float	gunAngle;
	int		gunType;
	bool	gunActive;

	FMOD::Sound		*deathSound;
	std::string		 soundFile;
};

class Player : public Enemy {

	virtual void tick(float deltaT);
	virtual void die();

	virtual void present(PaperWorld * const world, PaperWorld * const overlay);
	virtual void configure(const std::string &name);

	Text hpText;
	Tile shield;
};

class ea_AimsAt : virtual public Enemy {
protected:
	virtual void aim(float deltaT);
};

class ef_RandomFire : virtual public Enemy {
protected:
	virtual void fire(float deltaT);
};

class ed_DropHealth : virtual public Enemy {
protected:
	virtual void die();
};

class SmartEnemy : public ea_AimsAt, public ef_RandomFire, public ed_DropHealth {
};

#endif