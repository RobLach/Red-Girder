#ifndef PARTICLEEFFECT_H
#define PARTICLEEFFECT_H

#include "Entity.h"
#include "Body.h"
#include "Tile.h"

class ParticleEffect;

class Particle {
public:
	void frame(float deltaT);
	void present(PaperWorld * const world, PaperWorld * const overlay);

	void setSize(float size);
	void setTTL(float time);
	void setTexture(const NixTextureRef &t);
	void setTrajectory(const Vector3 &pos, const Vector3 &vel);



protected:
	friend ParticleEffect;

	Body body;
	Tile rep;
	float ttl;
	float ttlMax;
};

class ParticleEffect : public Entity {
public:
	ParticleEffect();

	/** ParticleEffect updates on frame rather than tick, 
	to save processing power if the frame rate drops below the tick rate.
	*/
	virtual void frame(float deltaT);
	virtual void present(PaperWorld * const world, PaperWorld * const overlay);

	virtual void configure(const std::string &name);
	void setTrajectory(const Vector3 &pos, const Vector3 &vel);

protected:	
	Array<Particle> particles;
	Vector3 position, velocity;
};

#endif