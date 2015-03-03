#include "GlassSounds.h"


bool GlassSounds::instanceFlag;

GlassSounds *GlassSounds::single;


GlassSounds::GlassSounds()
{
	srand(10);
	count = 0;
}

void GlassSounds::playContact()
{
	if(count == 0)
	{
		int randNum = (rand() % 3);
		if(randNum == 0)
			Audio::getISoundEngine()->play2D("light damage a1.mp3",false,false,true);
		else if(randNum == 1)				 
			Audio::getISoundEngine()->play2D("light damage a2.mp3",false,false,true);
		else if(randNum == 2)				
			Audio::getISoundEngine()->play2D("light damage a3.mp3",false,false,true);
	}
	if(count >=4)
		count = 0;
	else
		count++;
}
void GlassSounds::playDamaged()
{
		int randNum = (rand() % 3);
	if(randNum == 0)
		Audio::getISoundEngine()->play2D("light damage a1.mp3",false,false,true);
	else if(randNum == 1)				 
		Audio::getISoundEngine()->play2D("light damage a2.mp3",false,false,true);
	else if(randNum == 2)				
		Audio::getISoundEngine()->play2D("light damage a3.mp3",false,false,true);	
}

void GlassSounds::playDestroy()
{
	int randNum = (rand() % 3);
	if(randNum == 0)
		Audio::getISoundEngine()->play2D("light destroyed a1.mp3",false,false,true);
	else if(randNum == 1)				 
		Audio::getISoundEngine()->play2D("light destroyed a2.mp3",false,false,true);
	else if(randNum == 2)				
		Audio::getISoundEngine()->play2D("light destroyed a3.mp3",false,false,true);	
}

GlassSounds* GlassSounds::getInstance()
{
	if(! instanceFlag)
	{
		single = new GlassSounds();
		instanceFlag = true;
		return single;
	}
	else
	{
		return single;
	}
}