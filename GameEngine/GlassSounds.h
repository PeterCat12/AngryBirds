#ifndef GLASSSOUNDS_H
#define GLASSSOUNDS_H

#include "Audio.h"
#include <cstdlib>

class GlassSounds 
{
	public:
	static GlassSounds *getInstance();
	void playContact();
	void playDamaged();
	void playDestroy();

private:
	GlassSounds();
	int count;
	static bool instanceFlag;
	static GlassSounds *single;
};

#endif