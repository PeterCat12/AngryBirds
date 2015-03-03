#ifndef BIRD_OBJECT_H
#define BIRD_OBJECT_H


#include "GameSprite.h"
#include "BoxSprite.h"
#include "Box2D.h"
#include "CircleSprite.h"
#include "GameObject.h"
#include "Shape.h"
#include "CloudTrailManager.h"
#include "PixelToMeters.h"
#include <cstdlib>

#include "Audio.h"

//#include "IGameObject.h"

class b2Body;

extern AzulStopWatch totalWatch;

enum MyBirdState
{
	IDLE,
	LAUNCHER,
	ABILITY,
	FLYING,
	CONTACT,
	AFTERCONTACT,
	BLINKING,
};


class BirdObject : public IGameObject
{
public:
	BirdObject(GameObjectName::Name name);
	BirdObject(float centerX, float centerY, b2World *pWorld);
	virtual ~BirdObject();
	virtual void InitilizeBody();
	virtual void update( b2Vec2 posInMeters, float angleInRadians ); 
	virtual GameSprite *getGameSprite();
	virtual float getPosX() override;
	virtual float getPosY() override;
	virtual ImageName::Name getNextImageName( GameObjectName::Name currName,HealthStatus HStatus );
	virtual GameObjectName::Name getObjectName();
	virtual void updateHealth(float dmg);
	virtual void zeroHealth();
	virtual b2Body *getBody();
	virtual bool updateGame();
	virtual void ability();
	virtual void SwapSprite(MyBirdState _state);
	virtual void LaunchBird(b2Vec2 speed);


	GameSprite	*pGameSprite;
	CircleSprite	*pDebugSprite;
	b2Body		*pBody;

	float	angle;
	bool fired;
	bool used;
	bool madeContact;
	GameObjectName::Name	gameObjName;
	MyBirdState state;
	virtual void playSelect();
		bool select;
protected:
		virtual void playLaunchMusic();
		virtual void playContactMusic();
	
	int timeToChirp;
	float size;
	float health;
	float centerX;
	float centerY;
	int stationaryCount;
	int cycleCount;
	b2Vec2 oldPosition;
	bool destory;
	bool chirping;

	b2World *pWorld;
};

#endif