#ifndef SMALL_PIG_OBJECT_H
#define SMALL_PIG_OBJECT_H


#include "GameSprite.h"
#include "BoxSprite.h"
#include "Box2D.h"
#include "CircleSprite.h"
#include "GameObject.h"
#include "Shape.h"
#include "PigObject.h"
//#include "IGameObject.h"

class b2Body;

enum PigState
{
	NORMALPIG,
	MOVINGPIG,
};



class SmallPigObject : public IGameObject, public PigObject
{
public:
	//SmallPigObject(GameObjectName::Name name, GameSprite *pGameSprite, Shape *pDebugSprite );
	SmallPigObject(float centerX, float centerY, b2World *pWorld);
	~SmallPigObject();
	virtual void InitilizeBody();
	virtual void update( b2Vec2 posInMeters, float angleInRadians ); 
	virtual GameSprite *getGameSprite();
	virtual float getPosX();
	virtual float getPosY();
	virtual bool updateGame();
	virtual void zeroHealth();

	virtual ImageName::Name getNextImageName( GameObjectName::Name currName,HealthStatus HStatus );	
	virtual void updateHealth(float dmg);
	virtual GameObjectName::Name getObjectName();
	virtual b2Body *getBody();


	GameSprite	*pGameSprite;
	CircleSprite	*pDebugSprite;
	b2Body		*pBody;

	float	angle;
	GameObjectName::Name	gameObjName;

private:
	float size;
	float health;
	float maxHealth;
	float centerX;
	float centerY;
	bool destory;
	HealthStatus hStatus;
	PigState bState;
	b2World *pWorld;
};

#endif