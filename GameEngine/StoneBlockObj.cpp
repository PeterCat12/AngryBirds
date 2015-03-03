
#include "StoneBlockObj.h"
#include "BoxSprite.h"
#include "Box2D.h"
#include "PixelToMeters.h"


StoneBlockObj::StoneBlockObj(Rect centerArea, b2World *pWorld,float angle,SpriteName::Name sName, ImageName::Name name)
{
	IName = name;
	oldHStatus = HEALTHY;
	this->pWorld = pWorld;
	this->centerX = centerArea.x;
	this->centerY = centerArea.y;
	this->angle = angle;
	this->health = 0.0f;
	this->pGameSprite = new GameSprite(SpriteBatchName::SpriteBatch_Middleground, sName, name, Rect(centerX,centerY, centerArea.width,centerArea.height) ) ;  

	this->pDebugSprite = new BoxSprite(SpriteBatchName::SpriteBatch_Debug,
									SpriteName::Sprite_Box, 2.0f, Vect(55,0,255,255),centerArea);
	this->height= pDebugSprite->origHeight;
	this->width = pDebugSprite->origWidth;
	maxHealth = STONE_HEALTH_PER_PIXEL * height * width;

	pBody = 0;
	decideGameObjectName(name);
	InitilizeBody();
}

StoneBlockObj::~StoneBlockObj()
{
	SBNode *pSBNode;
	pSBNode = SpriteBatchManager::Find(this->pGameSprite->spriteBatchName);
	pSBNode->removeSprite( this->pGameSprite );
	pSBNode = SpriteBatchManager::Find(this->pDebugSprite->spriteBatchName);
	pSBNode->removeSprite(this->pDebugSprite);
	StoneSounds::getInstance()->playDestroy();
	pWorld->DestroyBody(this->pBody);
}

GameObjectName::Name StoneBlockObj::getObjectName()
{
	return this->gameObjName;
}

void StoneBlockObj::zeroHealth()
{
	ImageName::Name newName;
	this->health = 0.0f;
	hStatus = HEALTHY;
	newName = getNextImageName(this->gameObjName,hStatus);
	pGameSprite->spriteModel->SwapImage(newName);
}

void StoneBlockObj::decideGameObjectName(ImageName::Name name){
	switch( name)
	{
	case ImageName::Image_Stone_Blocks :
		this->gameObjName = GameObjectName::GameObject_Stone_Block;
			break;
	}
}


void StoneBlockObj::InitilizeBody(){

	b2BodyDef bodyDef;
	bodyDef.type= b2_dynamicBody;
	bodyDef.position.Set(PixelToMeter(pDebugSprite->posX), PixelToMeter(pDebugSprite->posY) );
	bodyDef.angle = this->angle;
	pBody = pWorld->CreateBody(&bodyDef);
	b2PolygonShape box;

	b2FixtureDef fixtureDef;

	box.SetAsBox(PixelToMeter(pDebugSprite->origWidth* 0.5f), PixelToMeter(pDebugSprite->origHeight * 0.5f));
	fixtureDef.shape = &box;
	fixtureDef.density = STONEBLOCK_DENSITY;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 0.5f;
	pBody->CreateFixture(&box, fixtureDef.density);
	pBody->GetFixtureList()->SetUserData(this);
	pBody->SetUserData(this);
}


b2Body *StoneBlockObj::getBody()
{
	return this->pBody;
}

float StoneBlockObj::getPosX(){
	return this->centerX;
}
float StoneBlockObj::getPosY(){
	return this->centerY;
}

ImageName::Name StoneBlockObj::getNextImageName( GameObjectName::Name currName,HealthStatus hStatus )
{
	ImageName::Name tmp = IName;
	if(oldHStatus != hStatus)
	{
		oldHStatus = hStatus;
		StoneSounds::getInstance()->playDamaged();
		switch(currName)
		{
		case GameObjectName::GameObject_Stone_Block :
			switch(hStatus)
			{
			case HealthStatus::HEALTHY:
				IName = ImageName::Image_Stone_Blocks;
				tmp = ImageName::Image_Stone_Blocks;
				break;
			case HealthStatus::SLTDMG :
				IName = ImageName::Image_Stone_Blocks2;
				tmp = ImageName::Image_Stone_Blocks2;
				break;
			case HealthStatus::DMG :
				IName = ImageName::Image_Stone_Blocks3;
				tmp = ImageName::Image_Stone_Blocks3;
				break;
			case HealthStatus::SVDMG :
				IName = ImageName::Image_Stone_Blocks4;
				tmp = ImageName::Image_Stone_Blocks4;
				break;
			}
			break;
		}
	}
	return tmp;
}

bool StoneBlockObj::updateGame()
{
	bool deleteMe = false;

	if( this->health > maxHealth )
	{	
		deleteMe = true;
	}
	return deleteMe;
}


void StoneBlockObj::updateHealth(float dmg)
{
	ImageName::Name newName;
	float t = DMGMULTIPLIER;
	if (dmg >= this->maxHealth / t)
	{
		this->health += (dmg); 
		StoneSounds::getInstance()->playContact();
	}
	if(health >= maxHealth *.10 && health < maxHealth *.20)
	{
		hStatus = SLTDMG;
		newName = getNextImageName(this->gameObjName,hStatus);
		pGameSprite->spriteModel->SwapImage(newName);
	}
	 else if(health >= maxHealth *.20 && health < maxHealth *.50)
	 {
		 hStatus = DMG;
		 newName = getNextImageName(this->gameObjName,hStatus);
		 pGameSprite->spriteModel->SwapImage(newName);
	 }
	else if(health >= maxHealth *.80)
	{
		hStatus = SVDMG;
		newName = getNextImageName(this->gameObjName,hStatus);
		pGameSprite->spriteModel->SwapImage(newName);
	}
}


void StoneBlockObj::setBody(b2Body *body){
	this->pBody = body;
}
GameSprite *StoneBlockObj::getGameSprite()
{
	return this->pGameSprite;
}


void StoneBlockObj::update(b2Vec2 posInMeters, float angleInRadians )
{

	if(pWorld->GetGravity().y == -10.0f)
		

	// updates position and angle from physics update
	this->centerX =  MeterToPixel(posInMeters.x );
	this->centerY =  MeterToPixel(posInMeters.y);
	this->angle = angleInRadians;


	// push the values to the GameSprite
	this->pGameSprite->posX = centerX;
	this->pGameSprite->posY = centerY;
	this->pGameSprite->angle = angle;

	// push the values to the DebugSprite
	this->pDebugSprite->posX  =centerX;
	this->pDebugSprite->posY = centerY;
	this->pDebugSprite->angle = angle;

}

