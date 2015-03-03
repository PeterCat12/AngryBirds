#ifndef PALLET_OBJECT_H
#define PALLET_OBJECT_H


#include "GameSprite.h"
#include "BoxSprite.h"
#include "Box2D.h"
#include "GameObject.h"


class b2Body;

class PalletObj : public IGameObject
{
public:
	PalletObj(Rect centerArea,b2World *pWorld);
	~PalletObj();
	virtual void update( b2Vec2 posInMeters, float angleInRadians );
	virtual void InitilizeBody();
	virtual bool updateGame();
	virtual GameSprite *getGameSprite();
	virtual float getPosX();
	virtual float getPosY();
	virtual ImageName::Name getNextImageName( GameObjectName::Name currName,HealthStatus HStatus );
	virtual GameObjectName::Name getObjectName();
	virtual void updateHealth(float dmg);
	virtual void zeroHealth();
	virtual b2Body *getBody();
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