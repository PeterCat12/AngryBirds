#ifndef STATIC_OBJECT_H
#define STATIC_OBJECT_H

#include "GameSprite.h"
#include "BoxSprite.h"
#include"Box2D.h"
#include "CircleSprite.h"
#include "Object.h"

class StaticObject : public Object
{

public:
	StaticObject(Rect centerArea,b2World *pWorld, float angle,SpriteName::Name sName, ImageName::Name iName);
	void update( b2Vec2 posInMeters, float angleInRadians );
	GameObjectName::Name getName();
	void endContact();
	void startContact();

	GameSprite *pGameSprite1;
	BoxSprite *pDebugSprite1;
	float width;
	float height;
	float centerX;
	float centerY;
	float angle;
		
	b2Body		*pBody;
	GameObjectName::Name	gameObjName;
private:


	b2World *pWorld;
};
#endif
