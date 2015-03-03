#ifndef WOOD_BLOCK_OBJECT_H
#define WOOD_BLOCK_OBJECT_H

#include "GameSprite.h"
#include "BoxSprite.h"
#include "Box2D.h"
#include "GameObject.h"
#include "WoodSounds.h"

class b2Body;
class WoodBlockObj : public IGameObject
{
public:
	WoodBlockObj(Rect centerArea,b2World *pWorld, float angle, SpriteName::Name sName, ImageName::Name iName);
	~WoodBlockObj();
	virtual void update( b2Vec2 posInMeters, float angleInRadians );
	virtual void InitilizeBody();
	virtual GameSprite *getGameSprite();
	virtual float getPosX();
	virtual float getPosY();
	virtual void updateHealth(float dmg);
	virtual ImageName::Name getNextImageName( GameObjectName::Name currName,HealthStatus HStatus );
	virtual bool updateGame();
	virtual void zeroHealth();


	virtual b2Body *getBody();
	virtual void setBody(b2Body *body);
	virtual GameObjectName::Name getObjectName();

	BoxSprite	*pBoxSprite;
	b2Body		*pBody;
	float	angle;
	GameObjectName::Name	gameObjName;

private:
	float width;
	float height;
	float maxHealth;
	ImageName::Name Iname;
	float centerX;
	float centerY;
	float health;
	bool destory;
	HealthStatus hStatus;
	HealthStatus oldHStatus;
	BoxSprite *pDebugSprite;
	GameSprite *pGameSprite;
	b2World *pWorld;
	void decideGameObjectName(ImageName::Name name);

};

#endif