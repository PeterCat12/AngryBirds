
#include "WoodPlankObj.h"
#include "BoxSprite.h"
#include "Box2D.h"
#include "PixelToMeters.h"



WoodPlankObj::WoodPlankObj(Rect centerArea, b2World *pWorld,float angle,SpriteName::Name sName, ImageName::Name name)
{
	
	this->pWorld = pWorld;
	this->centerX = centerArea.x;
	this->centerY = centerArea.y;
	this->angle = angle;
	this->health = 0.0f;
	this->hStatus = HEALTHY;
	this->destory = false;
	this->oldHStatus = HEALTHY;

	this->pGameSprite = new GameSprite(SpriteBatchName::SpriteBatch_Middleground, sName, name, Rect(centerX,centerY, centerArea.width,centerArea.height) ) ;  

	this->pDebugSprite = new BoxSprite(SpriteBatchName::SpriteBatch_Debug,
									SpriteName::Sprite_Box, 2.0f, Vect(55,0,255,255),centerArea);

	this->height= pDebugSprite->origHeight;
	this->width = pDebugSprite->origWidth;
	maxHealth = WOOD_HEALTH_PER_PIXEL * height * width;
	pBody = 0;
	this->Iname = name;
	decideGameObjectName(name);
	InitilizeBody();
}

WoodPlankObj::~WoodPlankObj()
{
	WoodSounds::getInstance()->playDestroy();
	SBNode *pSBNode;
	pSBNode = SpriteBatchManager::Find(this->pGameSprite->spriteBatchName);
	pSBNode->removeSprite( this->pGameSprite );
	pSBNode = SpriteBatchManager::Find(this->pDebugSprite->spriteBatchName);
	pSBNode->removeSprite(this->pDebugSprite);
	pWorld->DestroyBody(this->pBody);

}

GameObjectName::Name WoodPlankObj::getObjectName()
{
	return this->gameObjName;
}

void WoodPlankObj::zeroHealth()
{
	ImageName::Name newName;
	this->health = 0;
	hStatus = HEALTHY;
	newName = getNextImageName(this->gameObjName,hStatus);
	pGameSprite->spriteModel->SwapImage(newName);
}


//set gameobject name based on image
void WoodPlankObj::decideGameObjectName(ImageName::Name name)
{
	switch( name)
	{
	case ImageName::Image_Wood_Plank :
		this->gameObjName = GameObjectName::GameObject_Wood_Plank;
			break;
	case ImageName::Image_Wood_MedPlank :
		this->gameObjName = GameObjectName::GameObject_Wood_MedPlank;
			break;
	case ImageName::Image_Wood_MiniPlank :
		this->gameObjName = GameObjectName::GameObject_Wood_MiniPlank;
			break;
	}
}

void WoodPlankObj::InitilizeBody(){

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
	fixtureDef.density = WOOD_DENSITY;
	fixtureDef.friction = WOOD_FRICTION;
	fixtureDef.restitution = WOOD_RESTITUTION;
	pBody->SetActive(true);
	pBody->CreateFixture(&box, fixtureDef.density);
	pBody->GetFixtureList()->SetUserData(this);
	pBody->SetUserData(this);
}

ImageName::Name WoodPlankObj::getNextImageName( GameObjectName::Name currName, HealthStatus hStatus )
{
	ImageName::Name tmp = this->Iname;

	if(oldHStatus != hStatus)
	{
		oldHStatus = hStatus;
		WoodSounds::getInstance()->playDamaged();
	switch(currName)
	{
	case GameObjectName::GameObject_Wood_Plank :
		switch(hStatus)
		{
		case HealthStatus::HEALTHY :
			Iname = ImageName::Image_Wood_Plank;
			tmp = ImageName::Image_Wood_Plank;
			break;
		case HealthStatus::SLTDMG :
			Iname = ImageName::Image_Wood_Plank2;
			tmp = ImageName::Image_Wood_Plank2;
			break;
		case HealthStatus::DMG :
			Iname = ImageName::Image_Wood_Plank3;
			tmp = ImageName::Image_Wood_Plank3;
			break;
		case HealthStatus::SVDMG :
			Iname = ImageName::Image_Wood_Plank4;
			tmp = ImageName::Image_Wood_Plank4;
			break;
		}
		break;
	case GameObjectName::GameObject_Wood_MedPlank :
		switch(hStatus)
		{
		case HealthStatus::HEALTHY :
			Iname = ImageName::Image_Wood_MedPlank;
			tmp = ImageName::Image_Wood_MedPlank;
			break;
		case HealthStatus::SLTDMG :
			Iname = ImageName::Image_Glass_MedPlank2;
			tmp = ImageName::Image_Glass_MedPlank2;
			break;
		case HealthStatus::DMG:
			Iname = ImageName::Image_Glass_MedPlank3;
			tmp = ImageName::Image_Glass_MedPlank3;
			break;
		case HealthStatus::SVDMG :
			Iname = ImageName::Image_Glass_MedPlank4;
			tmp = ImageName::Image_Glass_MedPlank4;
			break;
		}
		break;
	case GameObjectName::GameObject_Wood_MiniPlank :
		switch(hStatus)
		{
		case HealthStatus::HEALTHY :
			Iname = ImageName::Image_Wood_MiniPlank;
			tmp = ImageName::Image_Wood_MiniPlank;
			break;
		case HealthStatus::SLTDMG :
			Iname = ImageName::Image_Wood_MiniPlank2;
			tmp = ImageName::Image_Wood_MiniPlank2;
			break;
		case HealthStatus::DMG:
			Iname = ImageName::Image_Wood_MiniPlank3;
			tmp = ImageName::Image_Wood_MiniPlank3;
			break;
		case HealthStatus::SVDMG :
			Iname = ImageName::Image_Wood_MiniPlank4;
			tmp = ImageName::Image_Wood_MiniPlank4;
			break;
		}
		break;
		}
	}
	return tmp;
}


b2Body *WoodPlankObj::getBody()
{
	return this->pBody;
}

float WoodPlankObj::getPosX(){
	return this->centerX;
}
float WoodPlankObj::getPosY(){
	return this->centerY;
}

GameSprite *WoodPlankObj::getGameSprite()
{
	return this->pGameSprite;
}

bool WoodPlankObj::updateGame()
{
	bool deleteMe = false;

	if( this->health >= this->maxHealth  )
	{	
		deleteMe = true;
	}
	return deleteMe;
}


void WoodPlankObj::updateHealth(float dmg)
{
	
	ImageName::Name newName;
	float t = DMGMULTIPLIER;
	if (dmg >= this->maxHealth / t)
	{
		this->health += (dmg); 
		//doesn't sound too bad...
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


void WoodPlankObj::update(b2Vec2 posInMeters, float angleInRadians )
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

//b2Fixture *pFix = this->pBody->GetFixtureList();
// while( pFix != 0 )
// { 
// 
// b2MassData again;
// pFix->GetMassData(&again);
// b2Vec2 maybe =pBody->GetWorldPoint(again.center);
// GameObject *pGObj = (GameObject *)pFix->GetUserData(); 
// // push the values to the GameSprite
// pGObj->pGameSprite->posX = MeterToPixel(maybe.x);
// pGObj->pGameSprite->posY = MeterToPixel(maybe.y);
// pGObj->pGameSprite->angle = angle;
// 
// // push the values to the DebugSprite
// pGObj->pBoxSprite->posX = MeterToPixel(maybe.x);
// pGObj->pBoxSprite->posY = MeterToPixel(maybe.y);
// pGObj->pBoxSprite->angle = angle;
//pFix = pFix->GetNext();