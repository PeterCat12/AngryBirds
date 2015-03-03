#include "WoodSounds.h"



bool WoodSounds::instanceFlag;

WoodSounds *WoodSounds::single;


WoodSounds::WoodSounds()
{
	srand(10);
	count = 0;
}

void WoodSounds::playContact()
{
	if(count == 0)
	{
		int randNum = (rand() % 6);
		if(randNum == 0)
			Audio::getISoundEngine()->play2D("wood collision a1.mp3",false,false,true);
		else if(randNum == 1)				 
			Audio::getISoundEngine()->play2D("wood collision a2.mp3",false,false,true);
		else if(randNum == 2)				
			Audio::getISoundEngine()->play2D("wood collision a3.mp3",false,false,true);
		else if(randNum == 3)				  
			Audio::getISoundEngine()->play2D("wood collision a4.mp3",false,false,true);
		else if(randNum == 4)				 
			Audio::getISoundEngine()->play2D("wood collision a5.mp3",false,false,true);
		else if(randNum == 5)				  
			Audio::getISoundEngine()->play2D("wood collision a6.mp3",false,false,true);
	}
	if(count >=3)
		count = 0;
	else
		count++;
}
void WoodSounds::playDamaged()
{
		int randNum = (rand() % 3);
	if(randNum == 0)
		Audio::getISoundEngine()->play2D("wood damage a1.mp3",false,false,true);
	else if(randNum == 1)				 
		Audio::getISoundEngine()->play2D("wood damage a2.mp3",false,false,true);
	else if(randNum == 2)				
		Audio::getISoundEngine()->play2D("wood damage a3.mp3",false,false,true);	
}

void WoodSounds::playDestroy()
{
	int randNum = (rand() % 3);
	if(randNum == 0)
		Audio::getISoundEngine()->play2D("wood destroyed a1.mp3",false,false,true);
	else if(randNum == 1)				 
		Audio::getISoundEngine()->play2D("wood destroyed a2.mp3",false,false,true);
	else if(randNum == 2)				
		Audio::getISoundEngine()->play2D("wood destroyed a3.mp3",false,false,true);	
}

WoodSounds* WoodSounds::getInstance()
{
	if(! instanceFlag)
	{
		single = new WoodSounds();
		instanceFlag = true;
		return single;
	}
	else
	{
		return single;
	}
}