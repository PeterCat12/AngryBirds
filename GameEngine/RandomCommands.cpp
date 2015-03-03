#include "RandomCommands.h"


bool RandomCommands::instanceFlag;

RandomCommands *RandomCommands::single;

extern AzulStopWatch totalWatch;

RandomCommands::RandomCommands()
{
	srand(0);
	victory = false;
	coutBirdChirp = 0;
	countPigPoink = 0;
	clockBird = totalWatch.timeInSeconds();
	clockPig = totalWatch.timeInSeconds();
}

void RandomCommands::SetTimeBird()
{
	coutBirdChirp = (rand() % 9) + 8;
}

void RandomCommands::SetTimePig()
{
	countPigPoink = (rand() % 9) + 8;
}
ISound *RandomCommands::playVictory()
{

	int randNum = (rand() % 3);
	victory = true;
	if(randNum == 0)
		return Audio::getISoundEngine()->play2D("bird next military a1.mp3",false,false,true);
	else if(randNum == 1)
		return Audio::getISoundEngine()->play2D("bird next military a2.mp3",false,false,true);
	else 			 
		return Audio::getISoundEngine()->play2D("bird next military a2.mp3",false,false,true);
}

void RandomCommands::playChirp()
{
	clockBird = totalWatch.timeInSeconds();
	int randNum = (rand() % 3);
	if(randNum == 0)
		Audio::getISoundEngine()->play2D("Globe_Bird_idle_01.mp3",false,false,true);
	else if(randNum == 1)
		Audio::getISoundEngine()->play2D("Globe_Bird_idle_02.mp3",false,false,true);
	else if(randNum == 2)				  //bird misc a1.mp3
		Audio::getISoundEngine()->play2D("Globe_Bird_idle_03.mp3",false,false,true);
	//else if(randNum == 3)				  //bird misc a1.mp3
	//	Audio::getISoundEngine()->play2D("bird misc a4.mp3",false,false,true);
	//	if(randNum == 4)				  //bird misca1.mp3
	//	Audio::getISoundEngine()->play2D("bird misc a5.mp3",false,false,true);
	//else if(randNum == 5)				  //bird misc a1.mp3
	//	Audio::getISoundEngine()->play2D("bird misc a6.mp3",false,false,true);
	//else if(randNum == 6)				  //bird misc a1.mp3
	//	Audio::getISoundEngine()->play2D("bird misc a7.mp3",false,false,true);
	//else if(randNum == 7)				  //bird misc a1.mp3
	//	Audio::getISoundEngine()->play2D("bird misc a8.mp3",false,false,true);
	//	if(randNum == 8)				  //bird misc a1.mp3
	//	Audio::getISoundEngine()->play2D("bird misc a9.mp3",false,false,true);
	//else if(randNum == 9)				  //bird misc a1.mp3
	//	Audio::getISoundEngine()->play2D("bird misc a10.mp3",false,false,true);
	//else if(randNum == 10)				  //bird misc a1.mp3
	//	Audio::getISoundEngine()->play2D("bird misc a11.mp3",false,false,true);
	//else if(randNum == 11)				  //bird misc a1.mp3
	//	Audio::getISoundEngine()->play2D("bird misc a12.mp3",false,false,true);
}


void RandomCommands::playOink()
{
	clockPig = totalWatch.timeInSeconds();
	int randNum = (rand() % 12);
	if(randNum == 0)
		Audio::getISoundEngine()->play2D("piglette oink a1.mp3",false,false,true);
	else if(randNum == 1)				
		Audio::getISoundEngine()->play2D("piglette oink a2.mp3",false,false,true);
	else if(randNum == 2)				 
		Audio::getISoundEngine()->play2D("piglette oink a3.mp3",false,false,true);
	else if(randNum == 3)				
		Audio::getISoundEngine()->play2D("piglette oink a4.mp3",false,false,true);
		if(randNum == 4)				 
		Audio::getISoundEngine()->play2D("piglette oink a5.mp3",false,false,true);
	else if(randNum == 5)			
		Audio::getISoundEngine()->play2D("piglette oink a6.mp3",false,false,true);
	else if(randNum == 6)				  
		Audio::getISoundEngine()->play2D("piglette oink a7.mp3",false,false,true);
	else if(randNum == 7)				 
		Audio::getISoundEngine()->play2D("piglette oink a8.mp3",false,false,true);
		if(randNum == 8)				 
		Audio::getISoundEngine()->play2D("piglette oink a9.mp3",false,false,true);
	else if(randNum == 9)				
		Audio::getISoundEngine()->play2D("piglette oink a10.mp3",false,false,true);
	else if(randNum == 10)				  
		Audio::getISoundEngine()->play2D("piglette oink a11.mp3",false,false,true);
	else if(randNum == 11)				
		Audio::getISoundEngine()->play2D("piglette oink a112.mp3",false,false,true);

}


void RandomCommands::BirdChirp(float time)
{
	 float lastAccessed = time - clockBird;
	 if(lastAccessed > coutBirdChirp)
		 playChirp();
	
}

void RandomCommands::PigOink(float time)
{
	float lastAccessed = time - clockPig;
	 if(lastAccessed > countPigPoink)
		 playOink();
}


RandomCommands* RandomCommands::getInstance()
{
	if(! instanceFlag)
	{
		single = new RandomCommands();
		instanceFlag = true;
		return single;
	}
	else
	{
		return single;
	}
}