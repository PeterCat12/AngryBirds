
#include "GroundObj.h"
#include "BoxSprite.h"
#include "Box2D.h"
#include "PixelToMeters.h"

GroundObj::GroundObj(Rect centerArea, b2World *pWorld)
{
	this->height= height;
	this->width = width;
	this->pWorld = pWorld;
	this->centerX = centerArea.x;
	this->centerY = centerArea.y;

	this->pDebugSprite = new BoxSprite(SpriteBatchName::SpriteBatch_Debug,
									SpriteName::Sprite_Box, 2.0f, Vect(55,0,255,255),centerArea);
	pBody = 0;
	this->gameObjName = GameObjectName::GameObject_Ground;
	InitilizeBody();
}

GroundObj::~GroundObj()
{
	SBNode *pSBNode;
	pSBNode = SpriteBatchManager::Find(this->pDebugSprite->spriteBatchName);
	pSBNode->removeSprite(this->pDebugSprite);
	pWorld->DestroyBody(this->pBody);
}


bool GroundObj::updateGame()
{
	//don't want to ever delete the ground object
	return false;
}

void GroundObj::zeroHealth()
{
	return;
}

GameObjectName::Name GroundObj::getObjectName()
{
	return this->gameObjName;
}

void GroundObj::updateHealth(float dmg)
{
	dmg;
	return;
}

void GroundObj::InitilizeBody(){

	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(PixelToMeter(centerX),PixelToMeter(centerY));
	this->pBody = pWorld->CreateBody(&groundBodyDef);
	b2PolygonShape groundBox;
	groundBox.SetAsBox(PixelToMeter(pDebugSprite->origWidth* 0.5f),PixelToMeter(pDebugSprite->origHeight * 0.5f));


	b2FixtureDef groundFixtureDef;
	groundFixtureDef.shape = &groundBox;
	groundFixtureDef.friction = 50.0f;
	groundFixtureDef.restitution = 0.0f;
	pBody->CreateFixture(&groundFixtureDef);   //&groundBox, 0.0f);

	pBody->GetFixtureList()->SetUserData(this);
	pBody->SetUserData( this);
}

b2Body *GroundObj::getBody()
{
	return this->pBody;
}

ImageName::Name GroundObj::getNextImageName( GameObjectName::Name currName,HealthStatus HStatus )
{
	currName;
	HStatus;
	ImageName::Name tmp = ImageName::Image_Alien_Small;

	return tmp;
}




float GroundObj::getPosX(){
	return this->centerX;
}
float GroundObj::getPosY(){
	return this->centerY;
}

GameSprite *GroundObj::getGameSprite()
{
	return this->pGameSprite;
}

void GroundObj::update(b2Vec2 posInMeters, float angleInRadians )
{
	// updates position and angle from physics update
	this->centerX =  MeterToPixel(posInMeters.x );
	this->centerY =  MeterToPixel(posInMeters.y);
	this->angle = angleInRadians;

		// push the values to the DebugSprite
	this->pDebugSprite->posX = centerX;
	this->pDebugSprite->posY = centerY;
}

