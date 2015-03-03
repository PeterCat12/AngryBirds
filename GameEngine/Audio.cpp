#include "Audio.h"
#include "RandomCommands.h"
#include "PigManager.h"
#include "BirdObjectManager.h"

bool Audio::instanceFlag;

Audio *Audio::single;


Audio::Audio()
{
	soundEngine = createIrrKlangDevice();
	victorySound = 0;
	pSndTheme = 0;
	m_bTheme = false;
}

Audio* Audio::getInstance()
{
	if(! instanceFlag)
	{
		single = new Audio();
		instanceFlag = true;
		return single;
	}
	else
	{
		return single;
	}
}

 ISoundEngine *Audio::getISoundEngine()
 {
	 return getInstance()->soundEngine;
 }


 void Audio::clear()
 {
	 getInstance()->soundEngine->removeAllSoundSources();
 }

 void Audio::unload()
 {
	 getInstance()->soundEngine->drop();
 }

 void Audio::privStart()
 {
	 pSndTheme = Audio::getISoundEngine()->play2D("title_theme.mp3",false,false, true);
	 Audio::getISoundEngine()->play2D("level_0.wav",false,false, true);
	 Audio::getISoundEngine()->play2D("bird misc a5.mp3",false,false,true);
	 Audio::getISoundEngine()->setSoundVolume(0.5f);
	 RandomCommands::getInstance()->SetTimeBird();
	 RandomCommands::getInstance()->SetTimePig();
 }

 void Audio::Start()
 {
	 Audio::getInstance()->privStart();
 }

 void Audio::Update(float time)
{
	 Audio::getInstance()->privUpdate(time);
 }

 void Audio::privUpdate(float time)
{
	 if(m_bTheme == false && pSndTheme->isFinished())
	{
		 m_bTheme = true;
		pSndTheme = Audio::getISoundEngine()->play2D("ambient_white_dryforest.mp3",true,false, true);
	 }
	 if(BirdObjectManager::getInstance()->getList()->size() > 1)
		 RandomCommands::getInstance()->BirdChirp(time);
	 if(PigManager::getInstance()->getList()->size() > 0)
		 RandomCommands::getInstance()->PigOink(time);
	 else
	 {
		 if(RandomCommands::getInstance()->victory == false)
			 victorySound = RandomCommands::getInstance()->playVictory();
	 }
 }

 bool Audio::Victory()
 {
	return Audio::getInstance()->privVictory();
 }

 bool Audio::privVictory()
 {
	 if(victorySound != 0 && victorySound->isFinished())
	 {
		 victorySound->drop();
		 victorySound = 0;
		  return true;
	 }
	 return false;
 }


