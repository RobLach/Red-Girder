#ifndef GRAVITYWELL_H
#define GRAVITYWELL_H

#include "Body.h"

class GravityWell {
public:
	GravityWell();

	void apply(Body &b, float deltaT) const;

	Vector2 pos;
	float strength;
};

#endif