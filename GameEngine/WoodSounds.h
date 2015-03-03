#ifndef WOODSOUNDS_H
#define WOODSOUNDS_H

#include "Audio.h"
#include <cstdlib>

class WoodSounds 
{
	public:
	static WoodSounds *getInstance();
	void playContact();
	void playDamaged();
	void playDestroy();

private:
	WoodSounds();
	int count;
	static bool instanceFlag;
	static WoodSounds *single;


};

#endif