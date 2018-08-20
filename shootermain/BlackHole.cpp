#include "stdafx.h"
#include "BlackHole.h"

#include "Depth.h"

#include "ShooterState.h"
#include "Parser.h"
extern Parser entityConfig;

void BlackHole::tick(float deltaT){
	// Move around.
	twitch += deltaT*0.1;
	pos = Vector2(5.9, 4.2)+Vector2(sin(twitch*11), cos(twitch*5))*0.1;
	collider.setTranslation(pos.x, pos.y, deltaT);
	gw.pos = pos;

	// Grow and shrink.
	pulse += deltaT*0.7;
	while(pulse > G3D::pi()*2) pulse -= G3D::pi()*2;
	float r = 0.3+sin(pulse)*0.04;


	setSize(r);
}

void BlackHole::frame(float deltaT){
}

void BlackHole::present(PaperWorld * const world, PaperWorld * const overlay){
	rep.setTranslation(pos.x, pos.y, 0);
	rep.present(world);
}

void BlackHole::setSize(float size) {
	rep.setSize(size*8, size*8);
	rep.center();

	collider.radius = size*0.5;
}

void BlackHole::configure(const std::string &name) {
	setTexture(entityConfig.fetchAsTexture(textureCache, name, "texture"));

	setSize(0.3);

	pos = Vector2(5.9, 4.2);
	pulse = 0;
	twitch = 0;

	gw.strength = entityConfig.fetchAsFloat(name, "strength");
}


void BlackHole::setTexture(const NixTextureRef &t){
	rep.setTexture(t);
	rep.setCastsShadow(true);
	rep.setColor(1, 1, 1, 1);
	rep.setDepth(0.1);
}

void BlackHole::collide(const Collision2D &c){
}

float BlackHole::getX()
{
	return pos.x;
}

float BlackHole::getY()
{
	return pos.y;
}
