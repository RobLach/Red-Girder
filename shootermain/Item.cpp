//The Item Class
//By: James Kim

#include "stdafx.h"
#include "Item.h"
#include "PaperWorld.h"
#include "ShooterState.h"

#include "Depth.h"

#include "Parser.h"
extern Parser entityConfig;

void Item::tick(float deltaT){
	collider.syncBody(body);

	// Expire when TTL elapses.
	ttl -= deltaT;
	if(ttl < 0){
		//ttlExpire();
	}
}

void Item::setTrajectory(const Vector3 &pos, const Vector3 &vel){
	body.pos = pos;
	body.vel = vel;
	collider.syncBody(body);
}

void Item::collide(const Collision2D &c) {
	//bool bounce = resolvePhysicalCollision(c, getBody());
	EntityRef e = edb.get(c.eid2);

	if(affects == e->getTeam())
	{
		std::cout << "collision" << std::endl;
		doEffect(e);

		if(uses <= 1) {}
			//ttlExpire();
		else
			uses--;
	}	
}

void Item::ttlExpire() {
	edb.remove(this);
}


void Item::present(PaperWorld *const world, PaperWorld * const overlay) {
	icon.setTranslation(body.pos.x, body.pos.y, body.pos.z);

	// Fade out.
	if(ttl<0.1){
		//icon.setColor(1, 1, 1, ttl*10);
	}

	icon.present(world);
}

void Item::configure(const std::string &name) {
	std::cout << "Item::configure(" << name << ")" << std::endl;
	
	setSize(entityConfig.fetchAsFloat(name, "size"));
	setTexture(entityConfig.fetchAsTexture(textureCache, name, "icon"));

	uses		= entityConfig.fetchAsInt(name,		"uses");
	ttl			= entityConfig.fetchAsFloat(name,	"ttl");
	affects		= entityConfig.fetchAsInt(name,		"affects");
}

void Item::setSize(float size) {
	std::cout << "Item::setSize(" << size << ")" << std::endl;
	
	icon.setSize(size, size);
	icon.center();

	collider.radius = size*0.5;
}

void Item::setTexture(const NixTextureRef &t){
	std::cout << "Item::setTexture(" << &t << ")" << std::endl;
	
	icon.setTexture(t);
	icon.setCastsShadow(false);
	icon.setColor(1, 1, 1, 1);
	icon.setDepth(powerupDepth+10);
}


void HealthItem::configure(const std::string &name) {
	std::cout << "HealthItem::configure(" << name << ")" << std::endl;

	amount		= entityConfig.fetchAsInt(name,		"amount");
	Item::configure(name);
}

void HealthItem::doEffect(EntityRef e) {
	std::cout << "HealthItem::doEffect(" << &e << ")" << std::endl;
	e->damage(-1 * amount);
	edb.remove(this);
}

