
#include "WoodBlockObj.h"
#include "BoxSprite.h"
#include "Box2D.h"
#include "PixelToMeters.h"


WoodBlockObj::WoodBlockObj(Rect centerArea, b2World *pWorld,float angle,SpriteName::Name sName, ImageName::Name name)
{
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
	Iname = name;

	maxHealth = WOOD_HEALTH_PER_PIXEL * width * height;
	pBody = 0;
	Iname = name;
	decideGameObjectName(name);
	InitilizeBody();
}

WoodBlockObj::~WoodBlockObj()
{
	WoodSounds::getInstance()->playDestroy();
	SBNode *pSBNode;
	pSBNode = SpriteBatchManager::Find(this->pGameSprite->spriteBatchName);
	pSBNode->removeSprite( this->pGameSprite );
	pSBNode = SpriteBatchManager::Find(this->pDebugSprite->spriteBatchName);
	pSBNode->removeSprite(this->pDebugSprite);

	pWorld->DestroyBody(this->pBody);
}

GameObjectName::Name WoodBlockObj::getObjectName()
{
	return this->gameObjName;
}


void WoodBlockObj::decideGameObjectName(ImageName::Name name){

	switch( name)
	{
	case ImageName::Image_Wood_Blocks :
		this->gameObjName = GameObjectName::GameObject_Wood_Block;
			break;
	case ImageName::Image_Wood_bigSquares :
		this->gameObjName = GameObjectName::GameObject_Wood_Square;
			break;
	}
}


void WoodBlockObj::InitilizeBody(){

	b2BodyDef bodyDef;
	bodyDef.type= b2_dynamicBody;
	bodyDef.angularDamping = 5.0f;
	bodyDef.position.Set(PixelToMeter(pDebugSprite->posX), PixelToMeter(pDebugSprite->posY) );
	bodyDef.angle = this->angle;
	pBody = pWorld->CreateBody(&bodyDef);
	b2PolygonShape box;

	b2FixtureDef fixtureDef;

	box.SetAsBox(PixelToMeter(pDebugSprite->origWidth* 0.5f), PixelToMeter(pDebugSprite->origHeight * 0.5f));
	fixtureDef.shape = &box;
	fixtureDef.density = WOODBLOCK_DENSITY;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 0.5f;
	pBody->CreateFixture(&box, fixtureDef.density);
	pBody->GetFixtureList()->SetUserData(this);
	pBody->SetUserData(this);
}


b2Body *WoodBlockObj::getBody()
{
	return this->pBody;
}

float WoodBlockObj::getPosX(){
	return this->centerX;
}
float WoodBlockObj::getPosY(){
	return this->centerY;
}

void WoodBlockObj::zeroHealth()
{
	ImageName::Name newName;
	this->health = 0.0f;
	hStatus = HEALTHY;
	newName = getNextImageName(this->gameObjName,hStatus);
	pGameSprite->spriteModel->SwapImage(newName);
}


ImageName::Name WoodBlockObj::getNextImageName( GameObjectName::Name currName,HealthStatus hStatus )
{
	ImageName::Name tmp = Iname;
	if(oldHStatus != hStatus)
	{
		oldHStatus = hStatus;
		WoodSounds::getInstance()->playDamaged();
	switch(currName)
	{
	case GameObjectName::GameObject_Wood_Block :
		switch(hStatus)
		{
		case HealthStatus::HEALTHY :
			Iname = ImageName::Image_Wood_Blocks;
			tmp = ImageName::Image_Wood_Blocks;
			break;
		case HealthStatus::SLTDMG :
			Iname = ImageName::Image_Wood_Blocks2;
			tmp = ImageName::Image_Wood_Blocks2;
			break;
		case HealthStatus::DMG :
			Iname = ImageName::Image_Wood_Blocks3;
			tmp = ImageName::Image_Wood_Blocks3;
			break;
		case HealthStatus::SVDMG :
			Iname = ImageName::Image_Wood_Blocks4;
			tmp = ImageName::Image_Wood_Blocks4;
			break;
		}
		break;
	case GameObjectName::GameObject_Wood_Square :
		switch(hStatus)
		{
		case HealthStatus::HEALTHY :
			Iname = ImageName::Image_Wood_bigSquares;
			tmp = ImageName::Image_Wood_bigSquares;
			break;
		case HealthStatus::SLTDMG :
			Iname = ImageName::Image_Wood_bigSquares2;
			tmp = ImageName::Image_Wood_bigSquares2;
			break;
		case HealthStatus::DMG:
			Iname = ImageName::Image_Wood_bigSquares3;
			tmp = ImageName::Image_Wood_bigSquares3;
			break;
		case HealthStatus::SVDMG :
			Iname = ImageName::Image_Wood_bigSquares4;
			tmp = ImageName::Image_Wood_bigSquares4;
			break;
		}
		break;
		}
	}
return tmp;	
}

bool WoodBlockObj::updateGame()
{
	bool deleteMe = false;

	if( this->health > maxHealth )
	{	
		deleteMe = true;
	}
	return deleteMe;
}


void WoodBlockObj::updateHealth(float dmg)
{
	ImageName::Name newName;
		float t = DMGMULTIPLIER;
	if (dmg >= this->maxHealth / t)
	{
		this->health += (dmg); 
		WoodSounds::getInstance()->playContact();
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


void WoodBlockObj::setBody(b2Body *body){
	this->pBody = body;
}
GameSprite *WoodBlockObj::getGameSprite()
{
	return this->pGameSprite;
}


void WoodBlockObj::update(b2Vec2 posInMeters, float angleInRadians )
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
	this->pDebugSprite->posX  =centerX;
	this->pDebugSprite->posY = centerY;
	this->pDebugSprite->angle = angle;

}

