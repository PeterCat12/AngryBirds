
#include "MediumPigObj.h"
#include "BoxSprite.h"
#include "Box2D.h"
#include "PixelToMeters.h"
#include "PigManager.h"


MediumPigObj::MediumPigObj(float centerX, float centerY, b2World *pWorld)
{
	size = 25;
	this->pWorld = pWorld;
	this->pGameSprite = new GameSprite(SpriteBatchName::SpriteBatch_Middleground, SpriteName::Sprite_Red_1, ImageName::Image_Pig_Med, Rect(655.0f, 302.0f, 39.0f, 39.0f) );
	this->centerY = centerY;
	this->centerX = centerX;
	this->pDebugSprite  = new CircleSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_Circle, 2.0f, Vect(255,255,255,255),this->pGameSprite);
	this->health = 0.0f;
	this->hStatus = HEALTHY;
	pBody = 0;
	PigManager::getInstance()->addPigToList((PigObject*) this);
	
	maxHealth = MEDPIG_HEALTH_PER_PIXEL * pDebugSprite->origHeight * pDebugSprite->origWidth;
	this->gameObjName = GameObjectName::GameObject_Med_Pig;
	InitilizeBody();
}

MediumPigObj::~MediumPigObj()
{
	PigManager::getInstance()->removePigFromList((PigObject*) this);
	SBNode *pSBNode;
	pSBNode = SpriteBatchManager::Find(this->pGameSprite->spriteBatchName);
	pSBNode->removeSprite( this->pGameSprite );
	pSBNode = SpriteBatchManager::Find(this->pDebugSprite->spriteBatchName);
	pSBNode->removeSprite(this->pDebugSprite);
	pWorld->DestroyBody(this->pBody);
}


bool MediumPigObj::updateGame()
{
	bool deleteMe = false;
	if( this->health >= maxHealth )
	{	
		deleteMe = true;
	}
	if(this->centerY < -100 )
		deleteMe = true;
	return deleteMe;
}

GameObjectName::Name MediumPigObj::getObjectName()
{
	return this->gameObjName;
}


void MediumPigObj::InitilizeBody()
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.angularDamping = 5.0f;
	bodyDef.position.Set(PixelToMeter(centerX), PixelToMeter(centerY));
	pBody = this->pWorld->CreateBody(&bodyDef);
	pBody->SetUserData(this);
	b2CircleShape birdCircle;
	birdCircle.m_p.Set(0,0);
	birdCircle.m_radius = PixelToMeter(this->pDebugSprite->origHeight * 0.5f);

	b2FixtureDef birdFixtureDef;
	birdFixtureDef.shape = &birdCircle;
	birdFixtureDef.density = MEDPIG_DENSITY;
	birdFixtureDef.friction = 0.1f;
	birdFixtureDef.restitution = 0.5f;
	pBody->CreateFixture( &birdFixtureDef);
	pBody->SetActive(true);
	pBody->GetFixtureList()->SetUserData(this);
	pBody->SetUserData(this);
}

ImageName::Name MediumPigObj::getNextImageName( GameObjectName::Name currName,HealthStatus hStatus ){
	ImageName::Name tmp = ImageName::Image_Alien_Medium;
	switch(currName)
	{
	case GameObjectName::GameObject_Med_Pig:
		switch(hStatus)
		{
		case HealthStatus::HEALTHY :
			tmp = ImageName::Image_Pig_Med;
			break;
		case HealthStatus::SLTDMG :
			tmp = ImageName::Image_Pig_Med2;
			break;
		case HealthStatus::DMG :
			tmp = ImageName::Image_Pig_Med3;
			break;
		case HealthStatus::SVDMG :
			tmp = ImageName::Image_Pig_Med4;
			break;
		}
		break;
	}
	return tmp;
}

void MediumPigObj::updateHealth(float dmg)
{
	ImageName::Name newName;
	float t = DMGMULTIPLIER;
	if (dmg >= this->maxHealth / t)
	{
		this->health += (dmg); 
	}
	
	if(health >= 10.0f && health <100.0f)
	{
		hStatus = SLTDMG;
		newName = getNextImageName(this->gameObjName,hStatus);
		pGameSprite->spriteModel->SwapImage(newName);
	}
	 else if(health < 50.0f && health >= 10.0f)
	 {
		 hStatus = DMG;
		 newName = getNextImageName(this->gameObjName,hStatus);
		 pGameSprite->spriteModel->SwapImage(newName);
	 }
	else if(health >=100.0f)
	 {
		hStatus = SVDMG;
		newName = getNextImageName(this->gameObjName,hStatus);
		pGameSprite->spriteModel->SwapImage(newName);
	}
}

void MediumPigObj::zeroHealth()
{
	ImageName::Name newName;
	this->health = 0.0f;
	hStatus = HEALTHY;
	newName = getNextImageName(this->gameObjName,hStatus);
	pGameSprite->spriteModel->SwapImage(newName);
}

void MediumPigObj::update(b2Vec2 posInMeters, float angleInRadians )
{
	 //updates position and angle from physics update
	this->centerX =  MeterToPixel(posInMeters.x );
	this->centerY =  MeterToPixel(posInMeters.y);
	this->angle = angleInRadians;

	// push the values to the GameSprite
	this->pGameSprite->posX = centerX;
	this->pGameSprite->posY =centerY;
	this->pGameSprite->angle = angle;

	this->pDebugSprite->posX = centerX;
	this->pDebugSprite->posY = centerY;
	this->pDebugSprite->angle= angle;	
}

b2Body *MediumPigObj::getBody()
{
	return this->pBody;
}

 GameSprite *MediumPigObj::getGameSprite()
 {
	 return this->pGameSprite;
 }


float MediumPigObj::getPosX(){
	return this->centerX;
}
float MediumPigObj::getPosY(){
	return this->centerY;
}
