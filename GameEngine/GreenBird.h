#ifndef GREENBIRD_OBJECT_H
#define GREENBIRD_OBJECT_H

#include "BirdObject.h"


class GreenBird : public BirdObject
{
public :
	void ability() override;
	GreenBird(float centerX, float centerY, b2World *pWorld);
	~GreenBird() override;
	void updateHealth(float dmg) override;
	void update( b2Vec2 posInMeters, float angleInRadians ) override;
	bool updateGame() override;
	void InitilizeBody() override;
	void SwapSprite(MyBirdState _state) override;
private:
	bool abilityB;
	b2Vec2 newDir;
	void turnAround();
	void playLaunchMusic() override;
	void playContactMusic() override;
	void playSelect() override;

};

#endif // ! GREENBIRD_OBJECT_H
