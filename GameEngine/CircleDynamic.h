#ifndef CIRCLE_DYNAMIC_OBJECT_H
#define CIRCLE_DYNAMIC_OBJECT_H

#include "GameSprite.h"
#include "BoxSprite.h"
#include"Box2D.h"
#include "CircleSprite.h"
#include "Object.h"

class CircleObj : public Object
{
public:
	
	CircleObj(Rect centerArea,b2World *pWorld,float _angle,  SpriteName::Name sName, ImageName::Name iName);
	void update(b2Vec2 posInMeters, float angleInRadians );
	GameObjectName::Name getName();
	void startContact();
	void endContact();

	GameObjectName::Name	gameObjName;
		float centerX;
	float centerY;
	float angle;
	CircleSprite *pDebugSprite1;
	GameSprite *pGameSprite1;
	b2Body		*pBody;
	int contactCount;

private:
	
};
#endif