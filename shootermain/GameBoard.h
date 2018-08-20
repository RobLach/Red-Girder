#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "Entity.h"
#include "Tile.h"

#include "PlaneCollider.h"
#include "CompositeCollider.h"

/**
Currently, gameboard draws a tiled background and does not influence gameplay.
*/
class GameBoard : public Entity {
public:
	GameBoard();

	virtual void configure(const std::string &name);
	virtual void present(PaperWorld * const world, PaperWorld * const overlay);

	/** HACK */
	virtual Collider2D * getCollider() {
		return &collider;
	}

protected:
	void setTexture(const NixTextureRef &floor1, const NixTextureRef &floor2);

	CompositeCollider2D collider;
	PlaneCollider2D planes[4];

	Tile tiles[1][1];
};

#endif