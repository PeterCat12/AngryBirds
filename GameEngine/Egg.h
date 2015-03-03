#ifndef EGG_OBJECT_H
#define EGG_BIRD_OBJECT_H

#include "BirdObject.h"

class Egg : public BirdObject
{
public:
	Egg(float centerX, float centerY, b2World *pWorld);
	~Egg() override;
	bool updateGame() override;
	void updateHealth(float dmg) override;
	void InitilizeBody() override;
private:
};
#endif