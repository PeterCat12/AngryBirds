#ifndef AUDIO_H
#define AUDIO_H

#include "irrKlang.h"

using namespace irrklang;

class Audio
{
protected:
	ISound* pSndTheme;
	ISound *victorySound;
	bool m_bTheme;


public:
	static ISoundEngine *getISoundEngine();
	static void unload();
	static void clear();
	static void Update(float time);
	static void Start();
	static bool Victory();
private:
	static Audio *getInstance();
	Audio();
	void privStart();
	void privUpdate(float time);
	bool privVictory();

	static bool instanceFlag;
	static Audio *single;
	ISoundEngine * soundEngine;
};
#endif