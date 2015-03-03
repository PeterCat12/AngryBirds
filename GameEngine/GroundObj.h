#ifndef GROUND_OBJECT_H
#define GROUND_OBJECT_H


#include "GameSprite.h"
#include "BoxSprite.h"
#include "Box2D.h"
#include "GameObject.h"


class b2Body;

class GroundObj : public IGameObject
{
public:
	GroundObj(Rect centerArea,b2World *pWorld);
	~GroundObj();
	virtual void update( b2Vec2 posInMeters, float angleInRadians );
	virtual void InitilizeBody();
	virtual GameSprite *getGameSprite();
	virtual float getPosX();
	virtual float getPosY();
	virtual bool updateGame();
	virtual b2Body *getBody();
	virtual ImageName::Name getNextImageName( GameObjectName::Name currName,HealthStatus HStatus );
	virtual void updateHealth(float dmg);
	virtual void zeroHealth();
	virtual GameObjectName::Name getObjectName();
	BoxSprite	*pBoxSprite;
	b2Body		*pBody;
	float	angle;

	GameObjectName::Name	gameObjName;
private:
	float width;
	float height;
	float centerX;
	float centerY;
	bool destory;
	BoxSprite *pDebugSprite;
	GameSprite *pGameSprite;
	b2World *pWorld;

};

#endif