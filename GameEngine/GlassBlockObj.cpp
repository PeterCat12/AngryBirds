
#include "GlassBlockObj.h"
#include "BoxSprite.h"
#include "Box2D.h"
#include "PixelToMeters.h"


GlassBlockObj::GlassBlockObj(Rect centerArea, b2World *pWorld,float angle,SpriteName::Name sName, ImageName::Name name)
{

	oldHStatus = HEALTHY;
	IName = name;
	this->height= height;
	this->width = width;
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
	maxHealth = GLASS_HEALTH_PER_PIXEL * height * width;
	pBody = 0;
	decideGameObjectName(name);
	InitilizeBody();
}

GlassBlockObj::~GlassBlockObj()
{
	SBNode *pSBNode;
	pSBNode = SpriteBatchManager::Find(this->pGameSprite->spriteBatchName);
	pSBNode->removeSprite( this->pGameSprite );
	pSBNode = SpriteBatchManager::Find(this->pDebugSprite->spriteBatchName);
	pSBNode->removeSprite(this->pDebugSprite);
	pWorld->DestroyBody(this->pBody);
	GlassSounds::getInstance()->playDestroy();
}

GameObjectName::Name GlassBlockObj::getObjectName()
{
	return this->gameObjName;
}

void GlassBlockObj::zeroHealth()
{
	ImageName::Name newName;
	this->health = 0;
	hStatus = HEALTHY;
	newName = getNextImageName(this->gameObjName,hStatus);
	pGameSprite->spriteModel->SwapImage(newName);
}

void GlassBlockObj::decideGameObjectName(ImageName::Name name){
	switch( name)
	{
	case ImageName::Image_Glass_Block :
		this->gameObjName = GameObjectName::GameObject_Glass_Block;
			break;

	case ImageName::Image_Glass_tinySquares :
		this->gameObjName = GameObjectName::GameObject_Glass_TinySquare;
			break;
	}
}


void GlassBlockObj::InitilizeBody(){

	b2BodyDef bodyDef;
	bodyDef.type= b2_dynamicBody;
	bodyDef.position.Set(PixelToMeter(pDebugSprite->posX), PixelToMeter(pDebugSprite->posY) );
	bodyDef.angle = this->angle;
	pBody = pWorld->CreateBody(&bodyDef);
	b2PolygonShape box;

	b2FixtureDef fixtureDef;

	box.SetAsBox(PixelToMeter(pDebugSprite->origWidth* 0.5f), PixelToMeter(pDebugSprite->origHeight * 0.5f));
	fixtureDef.shape = &box;
	fixtureDef.density = GLASSBLOCK_DENSITY;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 0.5f;
	pBody->CreateFixture(&box, fixtureDef.density);
	pBody->GetFixtureList()->SetUserData(this);
	pBody->SetUserData(this);
}


b2Body *GlassBlockObj::getBody()
{
	return this->pBody;
}

float GlassBlockObj::getPosX(){
	return this->centerX;
}
float GlassBlockObj::getPosY(){
	return this->centerY;
}

ImageName::Name GlassBlockObj::getNextImageName( GameObjectName::Name currName,HealthStatus hStatus )
{
	ImageName::Name tmp = IName;
	if(oldHStatus != hStatus)
	{
		oldHStatus = hStatus;
		GlassSounds::getInstance()->playDamaged();
		switch(currName)
		{
		case GameObjectName::GameObject_Glass_Block :
			switch(hStatus)
			{
			case HealthStatus::HEALTHY :
				IName = ImageName::Image_Glass_Block;
				tmp = ImageName::Image_Glass_Block;
				break;
			case HealthStatus::SLTDMG :
				IName = ImageName::Image_Glass_Block2;
				tmp = ImageName::Image_Glass_Block2;
				break;
			case HealthStatus::DMG :
				IName = ImageName::Image_Glass_Block3;
				tmp = ImageName::Image_Glass_Block3;
				break;
			case HealthStatus::SVDMG :
				IName = ImageName::Image_Glass_Block4;
				tmp = ImageName::Image_Glass_Block4;
				break;
			}
			break;
		case GameObjectName::GameObject_Glass_TinySquare :
			switch(hStatus)
			{
			case HealthStatus::HEALTHY :
				IName = ImageName::Image_Glass_tinySquares;
				tmp = ImageName::Image_Glass_tinySquares;
				break;
			case HealthStatus::SLTDMG :
				IName = ImageName::Image_Glass_tinySquares2;
				tmp = ImageName::Image_Glass_tinySquares2;
				break;
			case HealthStatus::DMG:
				IName = ImageName::Image_Glass_tinySquares3;
				tmp = ImageName::Image_Glass_tinySquares3;
				break;
			case HealthStatus::SVDMG :
				IName = ImageName::Image_Glass_tinySquares4;
				tmp = ImageName::Image_Glass_tinySquares4;
				break;
			}
			break;
		}
	}
	return tmp;
}

bool GlassBlockObj::updateGame()
{
	bool deleteMe = false;

	if( this->health > maxHealth )
	{	
		deleteMe = true;
	}
	return deleteMe;
}


void GlassBlockObj::updateHealth(float dmg)
{
	ImageName::Name newName;
	float t = DMGMULTIPLIER;
	if(dmg >= maxHealth / 4)
				GlassSounds::getInstance()->playContact();
	if (dmg >= this->maxHealth / t)
	{
		this->health += (dmg); 
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


void GlassBlockObj::setBody(b2Body *body){
	this->pBody = body;
}
GameSprite *GlassBlockObj::getGameSprite()
{
	return this->pGameSprite;
}


void GlassBlockObj::update(b2Vec2 posInMeters, float angleInRadians )
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

