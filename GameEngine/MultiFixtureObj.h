#ifndef FIX_OBJECT_H
#define FIX_OBJECT_H

#include "GameSprite.h"
#include "BoxSprite.h"
#include"Box2D.h"
#include "CircleSprite.h"


class fixObj
{
public:
	
	fixObj(Rect centerArea,b2World *pWorld,float _angle,  SpriteName::Name sName, ImageName::Name iName);
	void update(b2Vec2 posInMeters, float angleInRadians );
	GameObjectName::Name	gameObjName;
		float centerX;
	float centerY;
	float angle;
	BoxSprite *pDebugSprite1;
	GameSprite *pGameSprite1;
		b2Body		*pBody;
private:



	/*BoxSprite *pDebugSprite2;
	GameSprite *pGameSprite2;
	BoxSprite *pDebugSprite3;
	GameSprite *pGameSprite3;
	CircleSprite *pCircleSprite;
	GameSprite *pGameSprite4;*/

	
};
#endif