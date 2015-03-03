
#include "PalletObj.h"
#include "BoxSprite.h"
#include "Box2D.h"
#include "PixelToMeters.h"

PalletObj::PalletObj(Rect centerArea, b2World *pWorld)
{
	this->height= height;
	this->width = width;
	this->pWorld = pWorld;
	this->centerX = centerArea.x;
	this->centerY = centerArea.y;
	this->pGameSprite = new GameSprite(SpriteBatchName::SpriteBatch_Middleground, SpriteName::Sprite_Wood_Pallet, ImageName::Image_Wood_Pallet, Rect(700,140, 90,27.5) ) ;  
	this->pDebugSprite = new BoxSprite(SpriteBatchName::SpriteBatch_Debug,
									SpriteName::Sprite_Box, 2.0f, Vect(55,0,255,255),centerArea);
	pBody = 0;
	this->gameObjName = GameObjectName::GameObject_Wood_Pallet;
	InitilizeBody();
}

PalletObj::~PalletObj()
{
	SBNode *pSBNode;
	pSBNode = SpriteBatchManager::Find(this->pGameSprite->spriteBatchName);
	pSBNode->removeSprite( this->pGameSprite );
	pSBNode = SpriteBatchManager::Find(this->pDebugSprite->spriteBatchName);
	pSBNode->removeSprite(this->pDebugSprite);

	pWorld->DestroyBody(this->pBody);
}


bool PalletObj::updateGame()
{
	return false; 
}

void PalletObj::zeroHealth()
{
	return;
}

GameObjectName::Name PalletObj::getObjectName()
{
	return this->gameObjName;
}

ImageName::Name PalletObj::getNextImageName( GameObjectName::Name currName,HealthStatus HStatus )
{
	currName;
	HStatus;
	ImageName::Name tmp = ImageName::Image_Alien_Small;

	return tmp;
}

void PalletObj::updateHealth(float dmg)
{
	dmg;
	return;
}

void PalletObj::InitilizeBody(){

	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(PixelToMeter(pDebugSprite->posX), PixelToMeter(pDebugSprite->posY) );	
	pBody = pWorld->CreateBody(&bodyDef);
	b2PolygonShape box;

	box.SetAsBox(PixelToMeter(pDebugSprite->origWidth * 0.5f), PixelToMeter(pDebugSprite->origHeight * 0.5f));
	pBody->CreateFixture(&box, 10);
	pBody->GetFixtureList()->SetUserData(this);
	pBody->SetUserData(this);
}

b2Body *PalletObj::getBody()
{
	return this->pBody;
}

float PalletObj::getPosX(){
	return this->centerX;
}
float PalletObj::getPosY(){
	return this->centerY;
}

GameSprite *PalletObj::getGameSprite()
{
	return this->pGameSprite;
}

void PalletObj::update(b2Vec2 posInMeters, float angleInRadians )
{
	// updates position and angle from physics update
	this->centerX =  MeterToPixel(posInMeters.x );
	this->centerY =  MeterToPixel(posInMeters.y);
	this->angle = angleInRadians;


	// push the values to the GameSprite
	this->pGameSprite->posX = centerX;
	this->pGameSprite->posY = centerY;
	this->pGameSprite->angle = angle;

	// push the values to the DebugSprite
	this->pDebugSprite->posX  = centerX;
	this->pDebugSprite->posY = centerY;
	this->pDebugSprite->angle = angle;

}

