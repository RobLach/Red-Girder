#include "stdafx.h"
#include "ShooterState.h"

EventManager	event;
WindowManager	window;
NixVfs vfs;

Renderer r;
OrthogonalCameraRef worldCamera;

NixFontRef font;

TextureCache textureCache;
FontCache fontCache;


GameletManager gameletManager;
ShooterGamelet mainGamelet;

ShooterConfig config;

EntityDatabase edb;


#include "ParticleEffect.h"

void spawnParticleEffect(const std::string &name, const Vector3 &pos,  const Vector3 &vel) {
	ParticleEffect *pe = new ParticleEffect();
	pe->setTrajectory(pos, vel);
	pe->configure(name);						
	edb.add(pe);
}


float shakeAmt, shakeDecay, shakeSmooth, shakeScale;
Vector2 shakeOffset;

void shake(float mag) {
	shakeAmt = max(shakeAmt, mag*shakeScale);
}

void updateShake(float deltaT) {
	shakeAmt *= shakeDecay;

	//Prevent floating point denormals.
	if(shakeAmt < 0.01) shakeAmt = 0;

	shakeOffset = shakeOffset*shakeSmooth+Vector2::random()*(1-shakeSmooth);
}
