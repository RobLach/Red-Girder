#include "stdafx.h"
#include "Shot.h"

#include "ShooterState.h"

#include "Depth.h"

#include "Parser.h"
extern Parser entityConfig;

#include "fmod.hpp"

void Shot::setTexture(const NixTextureRef &t){
	rep.setTexture(t);
	rep.setCastsShadow(false);
	rep.setColor(1, 1, 1, 1);
	rep.setDepth(shotDepth);

}

void Shot::configure(const std::string &name) {
	/// @todo Create a "ShotConfig" structure for each type of shot.
	setSize(entityConfig.fetchAsFloat(name, "size"));
	setTexture(entityConfig.fetchAsTexture(textureCache, name, "texture"));

	damage		= entityConfig.fetchAsFloat(name,	"damage");
	impulse		= entityConfig.fetchAsFloat(name,	"impulse");
	numBounce	= entityConfig.fetchAsInt(name,		"bounces");
	ttl			= entityConfig.fetchAsFloat(name,	"ttl");
	hurts		= entityConfig.fetchAsInt(name,		"hurts");
	rotates		= entityConfig.fetchAsInt(name,		"rotates");
	rocket		= entityConfig.fetchAsInt(name,		"rocket");
	explodes	= entityConfig.fetchAsInt(name,		"explodes");
	velocity	= entityConfig.fetchAsFloat(name, "velocity");
	bounceMod	= 1;

	soundFile	= entityConfig.fetchAsString(name,	"sound");
	soundFile2	= entityConfig.fetchAsString(name,	"sound2");
	volume  = entityConfig.fetchAsFloat(name,	"volume");
	body.setMass(entityConfig.fetchAsFloat(name,	"mass"));

	shawnssystem->playSoundfile(soundFile, volume);
	
	if(rocket==1)
		this->body.makeShot(); //massive hack to stop colliding with own shots

	rocketMovement=0;
	collider.isShot = true;
}

void Shot::setSize(float size) {
	rep.setSize(size, size);
	rep.center();
	shake(0.03);

	collider.radius = size*0.5;
}


void Shot::setTrajectory(const Vector3 &pos, const Vector3 &vel){
	
	body.pos = pos;
	body.vel = vel;

	properX=-vel.x;
	properY=-vel.y;
	
	collider.syncBody(body);

	

	//fireAngle = atan2(-body.pos.x, body.pos.y);	
	fireAngle = atan2(body.vel.x, -body.vel.y);
	initFireAngle = fireAngle;

}
void Shot::setDirect(bool isRight)
{
	directRight=isRight;
}

void Shot::collide(const Collision2D &c) {
	//bool bounce = resolvePhysicalCollision(c, getBody());
	/* Shawns Code
	if(c.bounce){
		EntityRef e = edb.get(c.eid2);

		Body *b = e->getBody();

		if(b){
			b->impulseAtCenter(Vector3(c.contactPoints[0].normal*impulse, 0));
		}

		Collider2D *c = e->getCollider();
		if(hurts == e->getTeam())
			e->damage(damage);
		
		//if(!c->isShot && !c->isFriendly){
		//	e->damage(damage);
		//}

		if(numBounce <= 0)
			ttlExpire();
		else
			numBounce--;
		fireAngle = atan2(body.vel.x, -body.vel.y);
		*/

		//Lach's Code
		if(c.bounce){
		EntityRef e = edb.get(c.eid2);

		Body *b = e->getBody();

		if(b){
			b->impulseAtCenter(Vector3(-c.contactPoints[0].normal*impulse, 0));
		}

		Collider2D *c = e->getCollider();
		if(!c->isShot && (hurts == e->getTeam())){
			e->damage(damage);
			shake(0.15);
		}

		if(numBounce <= 0)
			ttlExpire();
		else
		{
			numBounce--;
			bounceMod=bounceMod/2; //placekeeper for testing of modificaion of velocity after bounce
		}
	}
	
}

void Shot::tick(float deltaT) {


	//body.tick(deltaT);

	collider.syncBody(body);
	fireAngle = atan2(body.vel.x, -body.vel.y);
	if(rocket==1) //serious business -Lach
	{
		float xMod, yMod;
		if(directRight==true)
		{
		yMod = sin(initFireAngle+20)*velocity/50;
		xMod = cos(initFireAngle+20)*velocity/50;
		this->body.vel.x+=xMod;
		this->body.vel.y+=yMod;
		}
		else
		{
		yMod = sin(initFireAngle-20)*velocity/50;
		xMod = cos(initFireAngle-20)*velocity/50;
		this->body.vel.x-=xMod;
		this->body.vel.y-=yMod;
		}


		velocity+=0.5;
		//this->setTrajectory(Vector3(body.vel.x +xMod, body.vel.y + yMod, fireAngle), Vector3(body.pos.x, body.pos.y, fireAngle));

	
	
	}

	// Expire when TTL elapses.
	ttl -= deltaT;
	if(ttl < 0){
		ttlExpire();
	}
}

void Shot::ttlExpire() {


	if(explodes==1){
	spawnParticleEffect("Ship Explode", body.pos, body.vel);
	spawnParticleEffect("Shockwave", body.pos, body.vel);
	
	}
	
		
	// Commit suicide.
	edb.remove(this);
}


void Shot::present(PaperWorld *const world, PaperWorld * const overlay){
	if(rotates==1)													//added rotation selection
		rep.setTranslation(body.pos.x, body.pos.y, body.pos.x*body.pos.y*5);
	else
	{
		rep.setTranslation(body.pos.x, body.pos.y, fireAngle);
		
	}
		// Fade out.
	if(ttl<0.1){
		rep.setColor(1, 1, 1, ttl*10);
	}

	rep.present(world);
}