#ifndef STONESOUNDS_H
#define STONESOUNDS_H

#include "Audio.h"
#include <cstdlib>

class StoneSounds 
{
	public:
	static StoneSounds *getInstance();
	void playContact();
	void playDamaged();
	void playDestroy();

private:
	StoneSounds();
	int count;
	static bool instanceFlag;
	static StoneSounds *single;


};

#endif