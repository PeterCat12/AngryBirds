#include "StoneSounds.h"



bool StoneSounds::instanceFlag;

StoneSounds *StoneSounds::single;


StoneSounds::StoneSounds()
{
	srand(10);
	count = 0;
}

void StoneSounds::playContact()
{
	if(count == 0)
	{
		int randNum = (rand() % 5);
		if(randNum == 0)
			Audio::getISoundEngine()->play2D("rock collision a1.mp3",false,false,true);
		else if(randNum == 1)				 
			Audio::getISoundEngine()->play2D("rock collision a2.mp3",false,false,true);
		else if(randNum == 2)				
			Audio::getISoundEngine()->play2D("rock collision a3.mp3",false,false,true);
		else if(randNum == 3)				  
			Audio::getISoundEngine()->play2D("rock collision a4.mp3",false,false,true);
		else if(randNum == 4)				 
			Audio::getISoundEngine()->play2D("rock collision a5.mp3",false,false,true);
	}
	if(count >=3)
		count = 0;
	else
		count++;
}
void StoneSounds::playDamaged()
{
		int randNum = (rand() % 3);
	if(randNum == 0)
		Audio::getISoundEngine()->play2D("rock damage a1.mp3",false,false,true);
	else if(randNum == 1)				 
		Audio::getISoundEngine()->play2D("rock damage a2.mp3",false,false,true);
	else if(randNum == 2)				
		Audio::getISoundEngine()->play2D("rock damage a3.mp3",false,false,true);	
}

void StoneSounds::playDestroy()
{
	int randNum = (rand() % 3);
	if(randNum == 0)
		Audio::getISoundEngine()->play2D("Rock destroyed a1.mp3",false,false,true);
	else if(randNum == 1)				 
		Audio::getISoundEngine()->play2D("Rock destroyed a2.mp3",false,false,true);
	else if(randNum == 2)				
		Audio::getISoundEngine()->play2D("Rock destroyed a3.mp3",false,false,true);	
}

StoneSounds* StoneSounds::getInstance()
{
	if(! instanceFlag)
	{
		single = new StoneSounds();
		instanceFlag = true;
		return single;
	}
	else
	{
		return single;
	}
}