#ifndef BLUEBIRD_OBJECT_H
#define BLUEBIRD_OBJECT_H

#include "BirdObject.h"
#include "GameObjectManager.h"



class BlueBird : public BirdObject
{

public:
	void ability() override;
	BlueBird(float centerX, float centerY, b2World *pWorld);
	BlueBird(float centerX, float centerY, b2World *pWorld, b2Vec2 velocity);
	~BlueBird() override;
	void SwapSprite(MyBirdState _state) override;
	void InitilizeBody() override;
	void updateHealth(float dmg) override;
	void playSelect() override;

private:
	bool copy;
		 void playLaunchMusic() override;
		 void playContactMusic() override;
		 

};

#endif