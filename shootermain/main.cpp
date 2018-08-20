#include "stdafx.h"
#include <iostream>

#pragma comment(lib, "framework.lib")
#pragma comment(lib, "paper.lib")

#include "ShooterState.h"


#include "Parser.h"


void getSysConfig(){
	Parser sys("sysconfig.ini");

	config.video.width			= sys.fetchAsInt("video", "width");
	config.video.height			= sys.fetchAsInt("video", "height");
	config.video.samples		= sys.fetchAsInt("video", "samples");
	config.video.fullscreen		= sys.fetchAsInt("video", "fullscreen");
	config.video.vsync			= sys.fetchAsInt("video", "vsync");

	config.key.up				= event.stringToKeyCode(sys.fetchAsString("keys", "up"));
	config.key.down				= event.stringToKeyCode(sys.fetchAsString("keys", "down"));
	config.key.left				= event.stringToKeyCode(sys.fetchAsString("keys", "left"));
	config.key.right			= event.stringToKeyCode(sys.fetchAsString("keys", "right"));

//	config.key.createEnemy		= event.stringToKeyCode(sys.fetchAsString("keys", "createEnemy"));
	config.key.togglePlayer2	= event.stringToKeyCode(sys.fetchAsString("keys", "togglePlayer2"));

	config.key.pause			= event.stringToKeyCode(sys.fetchAsString("keys", "pause"));
	config.key.slowmo			= event.stringToKeyCode(sys.fetchAsString("keys", "slowmo"));

	config.key.restart           = event.stringToKeyCode(sys.fetchAsString("keys", "restart"));
	config.key.quit				= event.stringToKeyCode(sys.fetchAsString("keys", "quit"));
	config.key.screenshot		= event.stringToKeyCode(sys.fetchAsString("keys", "screenshot"));
	

	vfs.loadPackage(sys.fetchAsString("system", "data"));

	shakeDecay = sys.fetchAsFloat("system", "shake_decay");
	shakeSmooth = sys.fetchAsFloat("system", "shake_smooth");
	shakeScale = sys.fetchAsFloat("system", "shake_scale");
}


void initSys(){
	getSysConfig();

	config.sound.global_volume	= 0.6;

	window.init(config.video.width, config.video.height, 
							config.video.samples, 
							config.video.fullscreen, 
							config.video.vsync);

	window.setCaption("Red Girder");

	//engine.sound.init();
	//engine.sound.setGlobalGain(config.sound.global_volume);

	textureCache.setVFS(&vfs);
	fontCache.setVFS(&vfs);

	// Seed the random number generator.
	srand((int)(System::time()*11));
}

void cleanSys(){
	edb.clear();
	fontCache.clear();
	textureCache.clear();
}

int main() {
	initSys();
	
	gameletManager.setEventManager(&event);  //~lachislamelet
	gameletManager.registerGamelet(0, &mainGamelet);
	gameletManager.run(0);

	cleanSys();
}