#ifndef BODY_H
#define BODY_H

/**
A rigid, 2D body.
*/
class Body {
public:
	Body();
	void setMass(float m);

	void impulseAtCenter(const Vector3 &i);
	void impulseAtPoint(const Vector3 &i, const Vector2 &p);
	void forceAtCenter(const Vector3 &f, float deltaT);
	void forceAtPoint(const Vector3 &f, const Vector2 &p, float deltaT);

	void updateVelocity(float deltaT);
	void updatePosition(float deltaT);
	void makePlayer();
	void makeShot();

	Vector3 pos, vel;
	float mass, massInv;
	bool isPlayer; //massive hacks
	bool isShot;   //massive hacks

	Vector2 velocityAtPoint(const Vector2 &p) const;

protected:
	Vector3 impulse;
};

#endif 