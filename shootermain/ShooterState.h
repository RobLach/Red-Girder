#ifndef SHOOTERSTATE_H
#define SHOOTERSTATE_H

// Engine

#include "WindowManager.h"
#include "event/EventManager.h"
#include "NixVfs.h"

extern EventManager		event;
extern WindowManager	window;
extern NixVfs vfs;

#include "Renderer.h"
extern Renderer r;
extern OrthogonalCameraRef worldCamera;

extern NixFontRef font;


#include "ContentCache.h"
extern TextureCache textureCache;
extern FontCache fontCache;


// Gamelets

#include "GameletManager.h"
#include "ShooterGamelet.h"

extern GameletManager gameletManager;
extern ShooterGamelet mainGamelet;

#include "EntityDatabase.h"
extern EntityDatabase edb;

extern void spawnParticleEffect(const std::string &name, const Vector3 &pos,  const Vector3 &vel);
extern void shake(float mag);
extern void updateShake(float deltaT);

extern float shakeAmt, shakeDecay, shakeSmooth, shakeScale;
extern Vector2 shakeOffset;

// Sound
#include "ShawnSound.h"
extern ShawnSound *shawnssystem;
//no idea why these have to be global but putting them in ShawnSound breaks it
extern float globalFreq;

#include "fmod.hpp"
extern FMOD::System  *soundsystem;

// Config

class ShooterConfig {
public:
	struct {
		int width;
		int height;
		int samples;
		int fullscreen;
		int vsync;
	} video;

	struct {
		float global_volume;
	} sound;

	struct {
		int up, down, left, right;
		int createEnemy;
		int togglePlayer2;
		int pause;
		int slowmo;
		int quit;
		int screenshot;
		int restart;
	} key;
};

extern ShooterConfig config;

#endif SHOOTERSTATE_H