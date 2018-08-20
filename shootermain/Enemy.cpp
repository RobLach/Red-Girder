#include "stdafx.h"
#include "Enemy.h"
#include "PaperWorld.h"

#include "ShooterState.h"
#include "Shot.h"

#include "ParticleEffect.h"

#include "MouseControl.h"
extern MouseControl mouseCont;

#include "Depth.h"

#include "Parser.h"
extern Parser entityConfig;

#include "Item.h"

#include "fmod.hpp"

// @TODO : Make this file infinitely cleaner

int Enemy::getTeam() {
	return team;
}

void Enemy::tick(float deltaT) {
	//body.tick(deltaT);
	collider.syncBody(body);

	aim(deltaT);
	fire(deltaT);
}

void Player::tick(float deltaT) {
	//body.tick(deltaT);
	collider.syncBody(body);

    float ratio = hitpoints / maxhitpoints;
	float scale = 49 * (1 - ratio);
	if(scale < 12)
		scale = 12;

	hpText.setColor(1, ratio, ratio, 1);
	hpText.setFont(font, 18);
	hpText.setTranslation(60, 30, 0);
	
	char temp[64];
	sprintf(temp, "%3.0f", hitpoints*10);
	hpText.setText(temp);

	if(gunCooldown > 0){
		gunCooldown -= deltaT;
	}

	if(gunActive && gunCooldown <= 0){
		if(gunType == 0){
			gunCooldown += shoot("Normal Shot");
		}else{
			gunCooldown += shoot("Big Shot");
		}
	}else if(!gunActive && gunCooldown < 0){
		gunCooldown = 0;
	}
}

void Player::die() {
	edb.remove(this);
	Enemy::die();
}

void Player::configure(const std::string &name) {

	NixTextureRef shieldTex	= entityConfig.fetchAsTexture(textureCache, name, "shieldTex");
	
	shield.setSize(1.3,1.3);
	shield.center();
	shield.setTexture(shieldTex);
	shield.setCastsShadow(true);
	shield.setColor(1, 1, 1, .7);
	shield.setDepth(shipDepth-0.07);
	this->body.makePlayer();
	Enemy::configure(name);
	LOLastShot=0;
}

void Player::present(PaperWorld * const world, PaperWorld * const overlay) {
	hpText.present(overlay);
	
	float ratio = hitpoints / maxhitpoints;
	if(ratio > .6)
		ratio = .6;
	if(hitpoints <= 4)
	{
		ratio = 0;
		shield.setCastsShadow(false);
	}
	shield.setColor(1,1,1, ratio);

	shield.setTranslation(body.pos.x, body.pos.y, body.pos.z);
	shield.present(world);


	Enemy::present(world, overlay);
}

void Enemy::die() {
	shawnssystem->playSoundfile(soundFile);

}

void ea_AimsAt::aim(float deltaT) {
	Vector2 gunControl = mouseCont.controled->body.pos.xy() - body.pos.xy();
	gunAngle = atan2(-gunControl.x, gunControl.y);
}

void ef_RandomFire::fire(float deltaT) {
	if(G3D::random(0.0, 10.0) < 1.0)
	{
		if(G3D::random(0.0, 1.0) < .5)
			gunType = 0;
		else
			gunType = 1;
		gunActive = true;
	}
	else
		gunActive = false;

	if(gunCooldown > 0){
		gunCooldown -= deltaT;
	}

	if(gunActive && gunCooldown <= 0){
		if(gunType == 0){
			gunCooldown += shoot("Enemy Normal Shot");
		}else{
			gunCooldown += shoot("Enemy Big Shot");
		}
	}else if(!gunActive && gunCooldown < 0){
		gunCooldown = 0;
	}

}

void ed_DropHealth::die() {
	edb.remove(this);
	std::cout << "Trying to drop health item" << std::endl;
	Item *drop = new HealthItem();
	
	drop->configure("Health");
	drop->setTrajectory(body.pos, Vector3(0,0,0));
	drop->getBody()->setMass(0);
	
	edb.add(drop);

	Enemy::die();
}

void Enemy::collide(const Collision2D &c) {
	//resolvePhysicalCollision(c, getBody());
}

void Enemy::damage(float amt){
	hitpoints -= amt;

	if (hitpoints <= 0){
		spawnParticleEffect("Ship Explode", body.pos, body.vel);
		spawnParticleEffect("Shockwave", body.pos, body.vel);
		shake(0.3);
		die(); // Suicide.
	}

	if (hitpoints > maxhitpoints - 1)
		hitpoints = maxhitpoints - 1;
}

void Enemy::frame(float deltaT) {
}

void Enemy::present(PaperWorld * const world, PaperWorld * const overlay) {
	topLayer.setTranslation(body.pos.x, body.pos.y, gunAngle);
	topLayer.present(world);

	middleLayer.setTranslation(body.pos.x, body.pos.y, body.pos.z);
	middleLayer.present(world);
}


void Enemy::setTrajectory(const Vector3 &pos, const Vector3 &vel){
	body.pos = pos;
	body.vel = vel;
	collider.syncBody(body);
}

void Enemy::configure(const std::string &name) {
	NixTextureRef swtop		= entityConfig.fetchAsTexture(textureCache, name, "swtop");
	NixTextureRef swmiddle	= entityConfig.fetchAsTexture(textureCache, name, "swmiddle");

	team = entityConfig.fetchAsInt(name, "team");
	hitpoints = entityConfig.fetchAsFloat(name, "hitpoints");
	maxhitpoints = hitpoints + 1;

	setSize(1);
	setTextures(swtop, swmiddle);

	collider.isFriendly = false;

	gunAngle = 0;
	gunCooldown = 0;
	gunCooldownMax = 1.0/10;
	gunActive = false;
	gunType = 0;
	
	soundFile	= entityConfig.fetchAsString(name,	"deathSound");

}

void Enemy::setSize(float size){
	topLayer.setSize(size, size);
	topLayer.center();

	middleLayer.setSize(size, size);
	middleLayer.center();

	collider.radius = size*0.5;
}

void Enemy::setTextures(const NixTextureRef &top, const NixTextureRef &middle) {
	topLayer.setTexture(top);
	topLayer.setCastsShadow(true);
	topLayer.setColor(1, 1, 1, 1);
	topLayer.setDepth(shipDepth+0.05);

	middleLayer.setTexture(middle);
	middleLayer.setCastsShadow(true);
	middleLayer.setColor(1, 1, 1, 1);
	middleLayer.setDepth(shipDepth);
}

float Enemy::shoot(const std::string &shotType){
	Shot *s = new Shot();
	
	float velocity	= entityConfig.fetchAsFloat(shotType, "velocity");
	float size	= entityConfig.fetchAsFloat(shotType, "size");
	float cooldown	= 1/entityConfig.fetchAsFloat(shotType, "rate");
	int rocket = entityConfig.fetchAsInt(shotType, "rocket");
	float gx = -sin(gunAngle);
	float gy = cos(gunAngle);
	float gxLeft = -sin(gunAngle-10);
	float gyLeft = cos(gunAngle-10);
	float gxRight = -sin(gunAngle+10);
	float gyRight = cos(gunAngle+10);
 

	//s->configure(shotType);
	//s->setTrajectory(body.pos + Vector3(gx, gy, 0)*(1.01+size)*0.5, Vector3(gx, gy, 0)*velocity);
		
	
	s->configure(shotType);
	if(rocket==1)
	{
		if(LOLastShot%2==0)
		{
			s->setTrajectory(body.pos + Vector3(gxLeft, gyLeft, 0)*(1.01+size)*0.45, Vector3(gxLeft, gyLeft, 0)*velocity*3);
			s->setDirect(0);
		}
		else
		{
			s->setTrajectory(body.pos + Vector3(gxRight, gyRight, 0)*(1.01+size)*0.45, Vector3(gxRight, gyRight, 0)*velocity*3);
			s->setDirect(1);
		}
	}
	else
	{
		s->setTrajectory(body.pos + Vector3(gx, gy, 0)*(1.01+size)*0.5, Vector3(gx, gy, 0)*velocity);
	}
	edb.add(s);
	LOLastShot++;

	return cooldown;
}