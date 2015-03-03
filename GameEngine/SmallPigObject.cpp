
#include "SmallPigObject.h"
#include "BoxSprite.h"
#include "Box2D.h"
#include "PixelToMeters.h"
#include "PigManager.h"


SmallPigObject::SmallPigObject(float centerX, float centerY, b2World *pWorld)
{
	size = 25;
	this->pWorld = pWorld;
	this->pGameSprite = new GameSprite(SpriteBatchName::SpriteBatch_Middleground, SpriteName::Sprite_Red_1, ImageName::Image_Pig_Small, Rect(655.0f, 302.0f, 25.0f, 25.0f) );
	this->centerY = centerY;
	this->centerX = centerX;
	this->pDebugSprite  = new CircleSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_Circle, 2.0f, Vect(255,255,255,255),this->pGameSprite);
	this->bState = NORMALPIG;
	this->health = 0.0f;
	this->hStatus = HEALTHY;
	pBody = 0;
	PigManager::getInstance()->addPigToList((PigObject*) this);
	maxHealth = PIG_HEALTH_PER_PIXEL * pDebugSprite->origHeight * pDebugSprite->origWidth;
	this->gameObjName = GameObjectName::GameObject_Small_Pig;
	InitilizeBody();
}

SmallPigObject::~SmallPigObject()
{
	SBNode *pSBNode;
	PigManager::getInstance()->removePigFromList((PigObject*) this);
	pSBNode = SpriteBatchManager::Find(this->pGameSprite->spriteBatchName);
	pSBNode->removeSprite( this->pGameSprite );
	pSBNode = SpriteBatchManager::Find(this->pDebugSprite->spriteBatchName);
	pSBNode->removeSprite(this->pDebugSprite);
	pWorld->DestroyBody(this->pBody);
}

bool SmallPigObject::updateGame()
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

GameObjectName::Name SmallPigObject::getObjectName()
{
	return this->gameObjName;
}

void SmallPigObject::zeroHealth()
{
	ImageName::Name newName;
	hStatus = HEALTHY;
	this->health = 0;
	newName = getNextImageName(this->gameObjName,hStatus);
	pGameSprite->spriteModel->SwapImage(newName);
}


void SmallPigObject::InitilizeBody()
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
	birdFixtureDef.density = PIG_DENSITY;
	birdFixtureDef.friction = PIG_FRICTION;
	birdFixtureDef.restitution = PIG_RESTITUTION;
	pBody->CreateFixture( &birdFixtureDef);
	pBody->GetFixtureList()->SetUserData(this);
	pBody->SetUserData(this);
}

//needs destructor
ImageName::Name SmallPigObject::getNextImageName( GameObjectName::Name currName,HealthStatus hStatus ){
	ImageName::Name tmp = ImageName::Image_Alien_Medium;
	switch(currName)
	{
	case GameObjectName::GameObject_Small_Pig :
		switch(hStatus)
		{
		case HealthStatus::HEALTHY :
			tmp = ImageName::Image_Pig_Small;
			break;
		case HealthStatus::SLTDMG :
			tmp = ImageName::Image_Pig_Small2;
			break;
		case HealthStatus::DMG :
			tmp = ImageName::Image_Pig_Small3;
			break;
		case HealthStatus::SVDMG :
			tmp = ImageName::Image_Pig_Small4;
			break;
		}
		break;
	}
	return tmp;
}

void SmallPigObject::updateHealth(float dmg)
{
	ImageName::Name newName;
	float t = DMGMULTIPLIER;
	if (dmg >= this->maxHealth / t)
	{
		this->health += (dmg); 
	}
	
	if(health >= 5.0f && health <25.0f)
	{
		hStatus = SLTDMG;
		newName = getNextImageName(this->gameObjName,hStatus);
		pGameSprite->spriteModel->SwapImage(newName);
	}
	 else if(health < 25.0f && health >= 45.0f)
	 {
		 hStatus = DMG;
		 newName = getNextImageName(this->gameObjName,hStatus);
		 pGameSprite->spriteModel->SwapImage(newName);
	 }
	else if(health >=45.0f)
	 {
		hStatus = SVDMG;
		newName = getNextImageName(this->gameObjName,hStatus);
		pGameSprite->spriteModel->SwapImage(newName);
	}
}

void SmallPigObject::update(b2Vec2 posInMeters, float angleInRadians )
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
	
	//printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
}

b2Body *SmallPigObject::getBody()
{
	return this->pBody;
}

 GameSprite *SmallPigObject::getGameSprite()
 {
	 return this->pGameSprite;
 }


float SmallPigObject::getPosX(){
	return this->centerX;
}
float SmallPigObject::getPosY(){
	return this->centerY;
}
