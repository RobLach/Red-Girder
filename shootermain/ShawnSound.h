#ifndef SHAWNSOUND_H
#define SHAWNSOUND_H

//RELIES ON EXTERNAL SOUNDSYSTEM


#include <string>
#include <vector>
#include <G3DAll.h>
#include "fmod.hpp"

using namespace std;
using namespace G3D;

class ShawnSound {
public:
	void initialize();
	//short sounds
	void playSoundfile(const std::string &name, float volume = 1.0);
	//long sounds
	void playStreamfile(const std::string &name, float volume = 1.0);

	void setFrequency(float frequency);
	float getFrequency();

	void stopAll();
};

#endif