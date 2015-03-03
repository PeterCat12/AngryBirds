#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H


#include "GameSprite.h"
#include "BoxSprite.h"
#include "Box2D.h"
#include "IGameObject.h"

class b2Body;



class GameObject : public IGameObject
{
public:
	//GameObject(GameObjectName::Name name, GameSprite *pGameSprite, Shape *pDebugSprite );
//	GameObject(float centerX, float centerY, float angle, b2World *pWorld,float width, float height,SpriteName::Name sName, ImageName::Name IName);
//	virtual void update( b2Vec2 posInMeters, float angleInRadians );
//	virtual void InitilizeBody();
//	virtual GameObjectName::Name getObjectName();
//	virtual float getDebugSpritePositionX();
//	virtual float getDebuSpritePositionY();
//	virtual float getDebugSpriteOrigWidth();
//	virtual float getDebugSpriteOrigHeight();
//	virtual GameSprite *getGameSprite();
//	virtual float getSpritePosX();
//	virtual float getSpritePosY();
//	virtual float getPosX();
//	virtual float getPosY();
//
//
//
//	virtual b2Body *getBody();
//	virtual float getAngle();
//	virtual void setBody(b2Body *body);
//
//
//
//	GameSprite	*pGameSprite;
//	//BoxSprite	*pBoxSprite;
//	Shape		*pShape;
//	b2Body		*pBody;
//
//	b2Vec2	pos;
//	float	angle;
//	GameObjectName::Name	gameObjName;
//private:
//	float width;
//	float height;
//	float centerX;
//	float centerY;
//	BoxSprite *pDebugSprite;
//	b2World *pWorld;
//	type bodyType;

};

#endif