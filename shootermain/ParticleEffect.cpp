#include "stdafx.h"
#include "ParticleEffect.h"

#include "ShooterState.h"

#include "Depth.h"

#include "Parser.h"
Parser particleConfig("particle.ini");

void Particle::setTexture(const NixTextureRef &t){
	rep.setTexture(t);
	rep.setCastsShadow(false);
	rep.setColor(1, 1, 1, 1);
	rep.setDepth(particleDepth);

	setSize(0.3);
	setTTL(1);
}

void Particle::setTTL(float time) {
	ttl = time;
	ttlMax = time;
}

void Particle::setSize(float size) {
	rep.setSize(size, size);
	rep.center();
}


void Particle::setTrajectory(const Vector3 &pos, const Vector3 &vel){
	body.pos = pos;
	body.vel = vel;
}

void Particle::frame(float deltaT) {
	body.updatePosition(deltaT);  // Note there is no force being applied to the particle...
	ttl -= deltaT;
	rep.setColor(1,1,1, min(ttl/ttlMax, 1));
}

void Particle::present(PaperWorld *const world, PaperWorld *const overlay){
	rep.setTranslation(body.pos.x, body.pos.y, body.pos.z);
	rep.present(world);
}



ParticleEffect::ParticleEffect(){
	setTrajectory(Vector3::zero(), Vector3::zero());
}

void ParticleEffect::setTrajectory(const Vector3 &pos, const Vector3 &vel){
	position = pos;
	velocity = vel;
}

void ParticleEffect::configure(const std::string &name) {
	particles.resize(particleConfig.fetchAsInt(name, "count"));
	NixTextureRef t = particleConfig.fetchAsTexture(textureCache, name, "texture");

	float size = particleConfig.fetchAsFloat(name, "size");
	float speed_min = particleConfig.fetchAsFloat(name, "speed_min");
	float speed_max = particleConfig.fetchAsFloat(name, "speed_max");
	float ttl_min = particleConfig.fetchAsFloat(name, "ttl_min");
	float ttl_max = particleConfig.fetchAsFloat(name, "ttl_max");


	float ranAngle;
	float ranSpeed;

	for(Array<Particle>::Iterator it = particles.begin(); it != particles.end(); it++){
		ranAngle = G3D::random(-3.14, 3.14);
		ranSpeed = G3D::random(speed_min, speed_max);

		it->setTexture(t);
		it->setSize(size);
		it->setTrajectory(position,  Vector3(velocity.xy(), 0)+Vector3(-sin(ranAngle), cos(ranAngle), 0)*ranSpeed );
		it->setTTL(G3D::random(ttl_min, ttl_max));
	}
}


void ParticleEffect::frame(float deltaT) {
	float maxTTL = -1;

	for(Array<Particle>::Iterator it = particles.begin(); it != particles.end(); it++){
		it->frame(deltaT);	
		maxTTL = max(maxTTL, it->ttl);
	}

	// Instead of removing each particle as it dies, we wait for all of them to die.
	// A little inefficient, but it's really easy to implement.
	if(maxTTL < 0){
		edb.remove(this);
	}
}


void ParticleEffect::present(PaperWorld *const world, PaperWorld *const overlay){
	if(particles.length() > 0){
		for(Array<Particle>::Iterator it = particles.begin(); it != particles.end(); it++){
			if(it->ttl >= 0){
				it->present(world, overlay);
			}
		}
	}
}