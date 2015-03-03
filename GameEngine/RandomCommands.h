#ifndef RANDOM_COM_H
#define RANDOM_COM_H

#include "AzulCore.h"
#include "Audio.h"

class RandomCommands
{
public:
	static RandomCommands *getInstance();
	void BirdChirp(float time);
	void PigOink(float time);
	void SetTimeBird();
	void SetTimePig();
	ISound *playVictory();
		bool victory;
private:

	RandomCommands();
	void playChirp();
	
	void playOink();
	int coutBirdChirp;
	int countPigPoink;
	float clockBird;
	float clockPig;
	static bool instanceFlag;
	static RandomCommands *single;
};
#endif