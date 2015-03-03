#ifndef WOOD_PLANK_OBJECT_H
#define WOOD_PLANK_OBJECT_H


#include "GameSprite.h"
#include "BoxSprite.h"
#include "Box2D.h"
#include "GameObject.h"
#include "WoodSounds.h"


class b2Body;

class WoodPlankObj : public IGameObject
{
public:
	WoodPlankObj(Rect centerArea,b2World *pWorld, float angle, SpriteName::Name sName, ImageName::Name iName);
	~WoodPlankObj();
	virtual void update( b2Vec2 posInMeters, float angleInRadians );
	virtual void InitilizeBody();
	virtual GameSprite *getGameSprite();
	virtual ImageName::Name getNextImageName( GameObjectName::Name currName, HealthStatus HStatus);
	virtual void updateHealth(float dmg);
	virtual GameObjectName::Name getObjectName();
	virtual float getPosX();
	virtual float getPosY();
	virtual bool updateGame();
	virtual b2Body *getBody();
	virtual void zeroHealth();

	BoxSprite	*pBoxSprite;
	b2Body		*pBody;

	float	angle;
	GameObjectName::Name	gameObjName;
private:

	void decideGameObjectName(ImageName::Name name);
	float width;
	float height;
	float maxHealth;
	float centerX;
	float centerY;
	float health;
	bool destory;
	HealthStatus hStatus;
	HealthStatus oldHStatus;
	BoxSprite *pDebugSprite;
	GameSprite *pGameSprite;
	ImageName::Name Iname;
	b2World *pWorld;


};

#endif