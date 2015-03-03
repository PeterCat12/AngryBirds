#ifndef YELLOW_BIRD_OBJECT_H
#define YELLOW_BIRD_OBJECT_H

#include "BirdObject.h"


class YellowBirdObject : public BirdObject
{
public:
	YellowBirdObject(float centerX, float centerY, b2World *pWorld);
	~YellowBirdObject() override;
	void InitilizeBody() override;
	void ability() override;
	void SwapSprite(MyBirdState _state) override;


private:
	void playLaunchMusic() override;
	void playContactMusic() override;
	void playSelect() override;


};


#endif