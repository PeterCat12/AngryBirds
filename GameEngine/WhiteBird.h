#ifndef WHITEBIRD_OBJECT_H
#define WHITEBIRD_OBJECT_H

#include "BirdObject.h"
#include "GameObjectManager.h"
#include "Egg.h"

class WhiteBird : public BirdObject
{
public:
	void ability() override;
	WhiteBird(float centerX, float centerY, b2World *pWorld);
	~WhiteBird() override;
	void InitilizeBody() override;
		void SwapSprite(MyBirdState _state) override;
private:
	Egg * egg;
	bool bAbility;
	void playLaunchMusic() override;
	void playContactMusic() override;
	void playSelect() override;
};
#endif