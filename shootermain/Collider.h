#ifndef COLLIDER_H
#define COLLIDER_H

/**
A contact point represents a point at which a collision occurs.
Simple collision geometries will typically produce a single contact when colliding,
but more complex geometries such as the composite geometry can produce multiple contact points.
*/
struct ContactPoint {
	ContactPoint(){
	}

	ContactPoint(const Vector2 &p, const Vector2 &n, const float d){
		pos = p;
		normal = n;
		depth = d;
	}

	void flip(){
		normal = -normal;
	}

	Vector2 pos, normal;
	float depth;
};

/**
Collision2D represents the geometry of two touching collision geometries.
*/
class Collision2D {
public:
	/** Changes the direction of the collision by swapping the entity IDs and reversing the contact normals.
	This is used so the same Collision2D structure can be used to inform both entities of the collision
	without needed to special case which "side" of the collision the entity is on.
	*/
	void flip(){
		for(int i=0;i<contactPoints.length();i++){
			contactPoints[i].flip();
		}

		int temp = eid1;
		eid1 = eid2;
		eid2 = temp;
	}

	void reset(){
		contactPoints.clear();
	}

	void addContact(const Vector2 &pos, const Vector2 &normal, const float depth){
		contactPoints.append(ContactPoint(pos, normal, depth));
	}

	int eid1, eid2;
	Array<ContactPoint> contactPoints;
	bool bounce;
};

class Body;
class CircleCollider2D;
class PlaneCollider2D;

/** Base class for all collision geometries. Uses double disbatch to determine 
the type of each geometry in a collision.*/
class Collider2D {
public:
	Collider2D(){
		setEID(0);
		isShot = false;
	}

	void setEID(int id){
		eid = id;
	}

	void setTranslation(float x, float y, float angle) {
		setTranslation(Vector3(x, y, angle));
	}

	/** @todo Remove. */
	void setTranslation(const Vector3 &trans) {
		translation = trans;
	}

	void syncBody(const Body &b);

	virtual bool collide(const Collider2D * const other, Collision2D &c) const = 0;

	// Double disbatch functions.
	virtual bool collideCircle(const CircleCollider2D * const other, Collision2D &c) const = 0;
	virtual bool collidePlane(const PlaneCollider2D * const other, Collision2D &c) const = 0;

	int eid;
	Vector3 translation;
	Vector3 velocity;

	bool isShot;
	bool isFriendly;
};

extern bool resolvePhysicalCollision(const Collision2D &c, Body *a, Body *b, const float epsilon, const float deltaT);

extern bool collideCircleCircle(const CircleCollider2D * const a, const CircleCollider2D * const b, Collision2D &c);
extern bool collideCirclePlane(const CircleCollider2D * const a, const PlaneCollider2D * const b, Collision2D &c, float polarity=1);
extern bool collidePlaneCircle(const PlaneCollider2D * const a, const CircleCollider2D * const b, Collision2D &c, float polarity=1);

#endif