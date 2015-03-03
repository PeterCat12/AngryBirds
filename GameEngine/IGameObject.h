#ifndef IGAME_OBJECT_MANAGER_H
#define IGAME_OBJECT_MANAGER_H

#include "Box2D.h"
#include "Shape.h"
#include "EnumName.h"
#include "SBNode.h"
#include "GameObjectInfo.h"
class b2Body;

enum HealthStatus
{
	HEALTHY,
	SLTDMG,
	DMG,
	SVDMG
};


class IGameObject
{
public:
	IGameObject(){};
	virtual	~IGameObject(){};
	virtual void update( b2Vec2 posInMeters, float angleInRadians ) = 0;
	virtual b2Body *getBody() = 0;
	virtual GameSprite *getGameSprite() = 0;
	virtual float getPosX() = 0;
	virtual float getPosY() = 0;
	//will delete getHealth...
	virtual bool updateGame() = 0;
	virtual ImageName::Name getNextImageName( GameObjectName::Name currName,HealthStatus HStatus ) = 0;
	virtual void updateHealth(float dmg) = 0;
	virtual void zeroHealth() = 0;
	virtual GameObjectName::Name getObjectName() = 0;
	virtual void InitilizeBody() = 0;
};
#endif