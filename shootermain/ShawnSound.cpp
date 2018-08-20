#include "stdafx.h"

#include "ShawnSound.h"

//RELIES ON EXTERNAL SOUNDSYSTEM
#include "ShooterState.h"

void ShawnSound::initialize() {
	FMOD::System_Create(&soundsystem);
	soundsystem->init(100, FMOD_INIT_NORMAL, 0);
}

void ShawnSound::playStreamfile(const std::string &name, float volume) {
	FMOD::Sound *sound;
	FMOD::Channel *channel2;

	soundsystem->createStream(name.c_str(), FMOD_LOOP_NORMAL, 0, &sound);
	soundsystem->playSound(FMOD_CHANNEL_FREE, sound, true, &channel2);
	channel2->setLoopCount(-1);
	channel2->setVolume(volume);		// Set the volume while it is paused.
	channel2->setFrequency(globalFreq);
	channel2->setPaused(false);		// This is where the sound really starts.
}

void ShawnSound::playSoundfile(const std::string &name, float volume) {
	FMOD::Sound *sound;
	FMOD::Channel *channel;

	soundsystem->createSound(name.c_str(), FMOD_DEFAULT, 0, &sound);
	soundsystem->playSound(FMOD_CHANNEL_FREE, sound, true, &channel);
	channel->setVolume(volume);		// Set the volume while it is paused.
	channel->setFrequency(globalFreq);
	channel->setPaused(false);		// This is where the sound really starts.
}
float ShawnSound::getFrequency(){
	return globalFreq;
	}


void ShawnSound::setFrequency(float frequency) {
	FMOD::ChannelGroup *masterGroup;
	soundsystem->getMasterChannelGroup(&masterGroup);

	masterGroup->overrideFrequency(frequency);

	globalFreq = frequency;
}



void ShawnSound::stopAll() {
	FMOD::ChannelGroup *masterGroup;
	soundsystem->getMasterChannelGroup(&masterGroup);
	masterGroup->stop();
	masterGroup->release();
	//masterGroup->overridePaused(value);
}