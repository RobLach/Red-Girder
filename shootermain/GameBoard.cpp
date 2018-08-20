#include "stdafx.h"
#include "GameBoard.h"
#include "PaperWorld.h"

#include "Depth.h"

#include "ShooterState.h"
#include "Parser.h"
extern Parser entityConfig;

GameBoard::GameBoard(){
	for(int j=0;j<1;j++){
		for(int i=0;i<1;i++){
			tiles[j][i].setSize(1024/60,768/60);
			tiles[j][i].setXY(-0.9,-0.5);
			tiles[j][i].setDepth(floorDepth);
			tiles[j][i].setCastsShadow(false);
			tiles[j][i].setTranslation(0, 0, 0);		
			//tiles[j][i].setColor(G3D::random(0.8, 1), G3D::random(0.8, 1), G3D::random(0.8, 1), 1);
		}
	}

	planes[0].setNormal(1, 0);
	planes[0].setPosition(-0.5, 0);

	planes[1].setNormal(0, 1);
	planes[1].setPosition(0, -0.5);

	planes[2].setNormal(-1, 0);
	planes[2].setPosition(9.7, 0);

	planes[3].setNormal(0, -1);
	planes[3].setPosition(0, 7.5);


	for(int p=0;p<4;p++) collider.addCollider(&planes[p]);
}

void GameBoard::configure(const std::string &name) {
	setTexture(	entityConfig.fetchAsTexture(textureCache, name, "floor1"), 
				entityConfig.fetchAsTexture(textureCache, name, "floor2"));
}

void GameBoard::present(PaperWorld * const world, PaperWorld * const overlay){
	for(int j=0;j<1;j++){
		for(int i=0;i<1;i++){
			tiles[j][i].present(world);
		}
	}
}

void GameBoard::setTexture(const NixTextureRef &floor1, const NixTextureRef &floor2){
	for(int j=0;j<1;j++){
		for(int i=0;i<1;i++){
			if(G3D::random(0, 1) < 0.75)
				tiles[j][i].setTexture(floor1);
			else
				tiles[j][i].setTexture(floor2);
		}
	}
}

