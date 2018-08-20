#include "stdafx.h"
#include "ShooterGamelet.h"

#include "Parser.h"
Parser entityConfig("config.ini");

#include "Enemy.h"
EnemyRef player1, player2;

#include "GameBoard.h"
GameBoard board;

#include "BlackHole.h"
BlackHole blackHole;

#include "ShooterState.h"

float rate;
float rateUpdated;
int numEnemies;
float enemyJustAdded;

float fps = 0;
Text fpsText;
Tile menu;
Tile gui;
Tile win, lose;
#include "JoystickControl.h"
JoystickControl joyCont;

#include "MouseControl.h"
MouseControl mouseCont;

#include "ShawnSound.h"
ShawnSound *shawnssystem;
float globalFreq = 44100.0 * 1;

//SHAWNSOUND NEEDS THIS
#include "fmod.hpp"
FMOD::System  *soundsystem;

bool ShooterGamelet::handleKeyControl(Event *e){
	if(e->isKeyboard()){
		KeyboardEvent *ke = static_cast<KeyboardEvent *>(e);

		if(ke->key() == config.key.togglePlayer2){
			if(ke->pressed())
				addRemPlayer2();
			return true;
		}else if(ke->key() == config.key.createEnemy){
			if(ke->pressed())
				createRandomEnemy();
			return true;
		}/*else if(ke->key()== config.key.restart){
			if(ke->pressed()){
				
				onExit();
				edb.clear();
				onEnter();
			}
		}*/

	}

	return false;
}

// Add-Remove Player 2 from the field
void ShooterGamelet::addRemPlayer2(){
	if(player2.isNull()) {
		player2.reset(new Player());
		
		//Initialize player2
		player2->configure("Player2");
		player2->setTrajectory(Vector3(3, 3, 0), Vector3(0, 0, 3));
		player2->getCollider()->isFriendly = true;
				
		//add player2 to the database of entities
		edb.add(player2);

		joyCont.controled.reset(player2);
	} else {
		//In the case of removal,  when "-" is pressed,
		//  remove player2 from the entity database, set
		//  the flag to nonexist and hope the database will
		//  delete the player2 object from memory
		edb.remove(player2);
		player2.reset(0);
		joyCont.controled.reset(0);
	}
}



void doScreenshot(){
	struct tm *newtime;
	time_t long_time;

	time( &long_time );
	newtime = localtime( &long_time );

	char temp[256];
	sprintf(temp, "shooter-%d-%2.2d-%2.2d-%d.png", newtime->tm_year+1900, newtime->tm_mon+1, newtime->tm_mday, long_time); 

	window.takeScreenshot(temp);
}

void ShooterGamelet::togglePause() {
	paused = !paused;
	shawnssystem->stopAll();
	if (paused)
	{
		//play title music
		std::string bgSoundFile = entityConfig.fetchAsString("Menu", "music");
		float bgVolume = entityConfig.fetchAsFloat("Menu", "volume");
	
		shawnssystem->playStreamfile(bgSoundFile, bgVolume);
	}
	else
	{
		//play background music
		std::string bgSoundFile = entityConfig.fetchAsString("Level 1", "music");
		float bgVolume = entityConfig.fetchAsFloat("Level 1", "volume");
	
		shawnssystem->playStreamfile(bgSoundFile, bgVolume);
	}
}


void ShooterGamelet::handleEvent(Event *e){
	// Print the event.
	//std::cout << e->toString() << std::endl;

	/// @todo Disable player control when paused?

	// Respond to mouse control.
	if(mouseCont.handleEvent(e)) return;

	// Respond to joystick control.
	if(joyCont.handleEvent(e)) return;

	if(handleKeyControl(e)) return;

	if(e->isKeyboard()){ //set up for keyboard control.
		KeyboardEvent *ke = static_cast<KeyboardEvent *>(e);
		if(ke->key() == config.key.pause){
			if(ke->pressed()) togglePause(); 
		}else if(ke->key() == config.key.quit){
			gameletManager.terminate();
		}else if(ke->key() == config.key.screenshot){
			if(ke->pressed()) doScreenshot();}
	

		
	}else if(e->isQuit()){
		gameletManager.terminate();
	}

}

/// @todo reduce O(n^2) algo. --bwahhahahahhah
void doCollision(float epsilon, float deltaT){
	Collision2D c;

	for(DBIterator it1 = edb.db.begin(); it1 != edb.db.end(); it1++){
		Collider2D *c1 = it1->value->getCollider();
		if(c1){
			for(DBIterator it2 = edb.db.begin(); it2 != edb.db.end(); it2++){
				if(it1->value->id() < it2->value->id()){
					Collider2D *c2 = it2->value->getCollider();
					if(c2 && (!c1->isShot || !c2->isShot)){
						c.reset();
						if(c1->collide(c2, c)){
							/// HACK
							c.eid1 = it1->value->id();
							c.eid2 = it2->value->id();
							c.bounce = resolvePhysicalCollision(c, it1->value->getBody(), it2->value->getBody(), epsilon, deltaT);

							it1->value->collide(c);
							c.flip();
							it2->value->collide(c);

						}
					}
				}
			}
		}
	}
	//edb.update();
}

void applyGravity(float deltaT){
	// Apply gravity to all the bodies.
	for(DBIterator it = edb.db.begin(); it != edb.db.end(); it++){
		Body *b = it->value->getBody();
		if(b){
			blackHole.gw.apply(*b, deltaT);
		}
	}
}


void updateVelocity(float deltaT){
	for(DBIterator it = edb.db.begin(); it != edb.db.end(); it++){
		Body *b = it->value->getBody();
		if(b){
			b->updateVelocity(deltaT);
		}
	}
}

void updatePosition(float deltaT){
	for(DBIterator it = edb.db.begin(); it != edb.db.end(); it++){
		Body *b = it->value->getBody();
		if(b){
			b->updatePosition(deltaT);
		}
	}
}


void ShooterGamelet::doPhysics(float deltaT) {
	applyGravity(deltaT);
	doCollision(0.7, deltaT);
	updateVelocity(deltaT);
	doCollision(0, deltaT);
	updatePosition(deltaT);
}

void ShooterGamelet::tick(float deltaT){
	if(!paused){
		updateShake(deltaT);

		mouseCont.tick(deltaT);
		joyCont.tick(deltaT);

		doPhysics(deltaT);

		edb.tick(deltaT);

		enemyJustAdded += deltaT;
		rateUpdated += deltaT;

		if (enemyJustAdded >= rate)
		{
			if (numEnemies < 100)
			{
				createRandomEnemy();
				numEnemies++;
				enemyJustAdded = 0.0;
			}
			else
			{
				
				Win();
			}
		}

		if (rateUpdated >= 20.0 && rate >= 1.0)
		{
				rate -= 0.50;
				rateUpdated = 0.0;
		}

		soundsystem->update();
	}
}

void ShooterGamelet::Win()
{
	win.setXY(0,0);
	win.setSize(800,600);
	NixTextureRef winText = entityConfig.fetchAsTexture(textureCache, "Win", "frame1");
	win.setTexture(winText);
	win.setTranslation(0,0,0);
}

void ShooterGamelet::Lose()
{
	lose.setXY(0,0);
	lose.setSize(800,600);
	NixTextureRef loseText = entityConfig.fetchAsTexture(textureCache, "Lose", "frame1");
	lose.setTexture(loseText);
	lose.setTranslation(0,0,0);
}


void ShooterGamelet::frame(float deltaT){
	if(!paused){
		edb.frame(deltaT);
		if(fadage>-0.01)
			fadage-=0.03;
		menu.setColor(1, 1, 1, fadage);
		gui.setColor(1,1,1, 1-fadage);
		fpsText.setColor(1,1,1, 1-fadage);
    }
	else
	{
		menu.setXY(0,0);
		menu.setSize(800,600);
		NixTextureRef menText = entityConfig.fetchAsTexture(textureCache, "Menu", "frame1");
		menu.setTexture(menText);
		menu.setTranslation(0,0,0);
		if(fadage<1.00001)
			fadage+=0.03;
		menu.setColor(1, 1, 1, fadage);
		gui.setColor(1,1,1, 1-fadage);
		fpsText.setColor(1,1,1, 1-fadage);
		
	}

	char temp[64];

	fps *= 0.92;
	fps += 0.08*RenderDevice::lastRenderDeviceCreated->getFrameRate();
	sprintf(temp, "Fps: %3.1f", fps);
	fpsText.setText(temp);

	dirty = true; // HACK
	forceDirty = true;

	}

void ShooterGamelet::doRender() {
	updateCamera();

	r.beginRender();
	present(r.getGameWorld(), r.getOverlayWorld());
	r.endRender();
}


void ShooterGamelet::present(PaperWorld * const world, PaperWorld * const overlay) {
	edb.present(world, overlay);
	fpsText.present(overlay);
	gui.present(overlay);	
	menu.present(overlay);
	win.present(overlay);
	lose.present(overlay);

}

void ShooterGamelet::updateCamera(){
	// Setup the camera.
	Rect2D wv = r.worldViewport();
	worldCamera.reset(new OrthogonalCamera());
	float xoff = (8*wv.width()/wv.height()-10)/2.0+shakeOffset.x*shakeAmt;
	float yoff = shakeOffset.y*shakeAmt;

	worldCamera->setRange(0-0.5-xoff, 8*wv.width()/wv.height()-0.5-xoff, 0-0.5-yoff, 8-0.5-yoff, -1, 1);
	r.getGameWorld()->setCamera(worldCamera);
}


/*
class Tile : public PaperRenderable { //tolua_export
public:
	//tolua_begin
	Tile();

	void setXY(float ix, float iy);
	void center();

	void setSize(float iw, float ih);

	void setTexture(const NixTextureRef &tex);
	void setColor(float r, float g, float b, float a);

	void setCastsShadow(bool casts);

	bool isTransparent() const;
	bool castsShadow() const;

	void draw(RenderDevice * const r);
	void drawShadow(RenderDevice * const r);
	void drawDebug(RenderDevice * const r);

	void setDepth(float id);
	float getDepth() const;
	void setTranslation(float tx, float ty, float ta);

	bool contains(float x, float y) const;

	//tolua_end

	void setColor(const Color4 &color);
	*/

void ShooterGamelet::onEnter() {
	fadage=1.0;
	paused = true;
  //  menu.setXY(0,0);
//	menu.setSize(800,600);
//	NixTextureRef menText = entityConfig.fetchAsTexture(textureCache, "Menu", "frame1");
//	menu.setTexture(menText);
//	menu.setTranslation(0,0,0);
	
	gui.setXY(0,0);
	gui.setSize(800,600);
	NixTextureRef guiText = entityConfig.fetchAsTexture(textureCache, "GUI", "overlayage");
	gui.setTexture(guiText);
	gui.setTranslation(0,0,0);


	shawnssystem->initialize();
		//FMOD::System_Create(&soundsystem);
		//soundsystem->init(100, FMOD_INIT_NORMAL, 0);

	//play background music
	std::string bgSoundFile = entityConfig.fetchAsString("Menu", "music");
	float bgVolume = entityConfig.fetchAsFloat("Menu", "volume");

	shawnssystem->playStreamfile(bgSoundFile, bgVolume);


	font = fontCache.get("eurostyle.fnt");

	fpsText.setFont(font, 12);
	fpsText.setTranslation(40, 600-25, 2);

	shakeAmt = 0;
	shakeOffset = Vector2::zero();
	updateCamera();

	player1.reset(new Player());
	mouseCont.controled = player1;

	player2.reset(0);

	numEnemies = 0;
	rate = 4.0;

	// Configure the entities.
	board.configure("Level 1");
	blackHole.configure("BlackHole");

	player1->configure("Player1");
	player1->setTrajectory(Vector3(3, 3, 0), Vector3(0, 0, 3));
	player1->getCollider()->isFriendly = true;

	edb.add(player1);
	edb.add(&board);
	edb.add(&blackHole);

	//int numEnemies = entityConfig.fetchAsInt("Level 1", "numEnemies");
	
	/// @bug Ships do not always appear on the screen.
	//for(int i=0;i<numEnemies;i++){
	//	createRandomEnemy();
	//}

	edb.update();
	
}

void ShooterGamelet::createRandomEnemy() {
	EnemyRef e(new SmartEnemy());
	
	float randomando = G3D::random(0,4);
    if(randomando>=0 && randomando<=1.0)
		e->configure("Enemy");
	if(randomando>1 && randomando<=2.0)
		e->configure("Enemy2");
	if(randomando>2 && randomando<=3.0)
		e->configure("Enemy3");
	if(randomando>3 && randomando<=4.0)
		e->configure("Enemy4");
	Vector3 pos = Vector3(blackHole.getX() + G3D::random(-1.0, 1.0), blackHole.getY() + G3D::random(-1.0, 1.0), G3D::random(0, 1));
	Vector3 vel = Vector3(G3D::random(-1.0, 1.0), G3D::random(-1.0, 1.0), G3D::random(-3, 3));
	e->setTrajectory(pos, vel);
	
	edb.add(e);
}

void ShooterGamelet::onExit() {


	player1.reset(0);
	player2.reset(0);
}
