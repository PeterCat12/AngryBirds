
#include "GlassPlankObj.h"
#include "BoxSprite.h"
#include "Box2D.h"
#include "PixelToMeters.h"


GlassPlankObj::GlassPlankObj(Rect centerArea, b2World *pWorld,float angle,SpriteName::Name sName, ImageName::Name name)
{

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
	oldHStatus = HEALTHY;
	maxHealth = GLASS_HEALTH_PER_PIXEL * width * height;
	pBody = 0;
	decideGameObjectName(name);
	InitilizeBody();
}

GlassPlankObj::~GlassPlankObj()
{
	SBNode *pSBNode;
	GlassSounds::getInstance()->playDestroy();
	pSBNode = SpriteBatchManager::Find(this->pGameSprite->spriteBatchName);
	pSBNode->removeSprite( this->pGameSprite );
	pSBNode = SpriteBatchManager::Find(this->pDebugSprite->spriteBatchName);
	pSBNode->removeSprite(this->pDebugSprite);

	pWorld->DestroyBody(this->pBody);
}

GameObjectName::Name GlassPlankObj::getObjectName()
{
	return this->gameObjName;
}

void GlassPlankObj::zeroHealth()
{
	ImageName::Name newName;
	this->health = 0.0f;
	hStatus = HEALTHY;
	newName = getNextImageName(this->gameObjName,hStatus);
	pGameSprite->spriteModel->SwapImage(newName);
}


void GlassPlankObj::decideGameObjectName(ImageName::Name name){

	switch( name)
	{
	case ImageName::Image_Glass_Plank :
		this->gameObjName = GameObjectName::GameObject_Glass_Plank;
			break;

	case ImageName::Image_Glass_MedPlank :
		this->gameObjName = GameObjectName::GameObject_Glass_MedPlank;
			break;
	case ImageName::Image_Wood_MiniPlank :
		this->gameObjName = GameObjectName::GameObject_Glass_MiniPlank;
			break;
	}
}


void GlassPlankObj::InitilizeBody(){

	b2BodyDef bodyDef;
	bodyDef.type= b2_dynamicBody;
	bodyDef.angularDamping = 3.0f;
	bodyDef.position.Set(PixelToMeter(pDebugSprite->posX), PixelToMeter(pDebugSprite->posY) );
	bodyDef.angle = this->angle;
	pBody = pWorld->CreateBody(&bodyDef);
	b2PolygonShape box;

	b2FixtureDef fixtureDef;

	box.SetAsBox(PixelToMeter(pDebugSprite->origWidth* 0.5f), PixelToMeter(pDebugSprite->origHeight * 0.5f));
	fixtureDef.shape = &box;
	fixtureDef.density = GLASS_DENSITY;
	fixtureDef.friction = GLASS_FRICTION;
	fixtureDef.restitution = GLASS_RESTITUTION;
	pBody->CreateFixture(&box, fixtureDef.density);
	pBody->GetFixtureList()->SetUserData(this);
	pBody->SetUserData(this);
}


b2Body *GlassPlankObj::getBody()
{
	return this->pBody;
}

float GlassPlankObj::getPosX(){
	return this->centerX;
}
float GlassPlankObj::getPosY(){
	return this->centerY;
}

ImageName::Name GlassPlankObj::getNextImageName( GameObjectName::Name currName,HealthStatus hStatus )
{
	ImageName::Name tmp = Iname;
	if(oldHStatus != hStatus)
	{
		oldHStatus = hStatus;
		GlassSounds::getInstance()->playDamaged();
		switch(currName)
		{
		case GameObjectName::GameObject_Glass_Plank :
			switch(hStatus)
			{
			case HealthStatus::HEALTHY :
				Iname = ImageName::Image_Glass_Plank;
				tmp = ImageName::Image_Glass_Plank;
				break;
			case HealthStatus::SLTDMG :
				Iname = ImageName::Image_Glass_Plank2;
				tmp = ImageName::Image_Glass_Plank2;
				break;
			case HealthStatus::DMG :
				Iname = ImageName::Image_Glass_Plank3;
				tmp = ImageName::Image_Glass_Plank3;
				break;
			case HealthStatus::SVDMG :
				Iname = ImageName::Image_Glass_Plank4;
				tmp = ImageName::Image_Glass_Plank4;
				break;
			}
			break;
		case GameObjectName::GameObject_Glass_MedPlank :
			switch(hStatus)
			{
			case HealthStatus::HEALTHY :
				Iname = ImageName::Image_Glass_MedPlank;
				tmp = ImageName::Image_Glass_MedPlank;
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
		case GameObjectName::GameObject_Glass_MiniPlank :
			switch(hStatus)
			{
			case HealthStatus::HEALTHY :
				Iname = ImageName::Image_Glass_MiniPlank;
				tmp = ImageName::Image_Glass_MiniPlank;
				break;
			case HealthStatus::SLTDMG :

				Iname = ImageName::Image_Glass_MiniPlank2;
				tmp = ImageName::Image_Glass_MiniPlank2;
				break;
			case HealthStatus::DMG:
				Iname = ImageName::Image_Glass_MiniPlank3;
				tmp = ImageName::Image_Glass_MiniPlank3;
				break;
			case HealthStatus::SVDMG :
				Iname = ImageName::Image_Glass_MiniPlank4;
				tmp = ImageName::Image_Glass_MiniPlank4;
				break;
			}
			break;
		}
	}
	return tmp;

}

bool GlassPlankObj::updateGame()
{
	bool deleteMe = false;

	if( this->health > maxHealth )
	{	
		deleteMe = true;
	}
	return deleteMe;
}


void GlassPlankObj::updateHealth(float dmg)
{
	ImageName::Name newName;
	float t = DMGMULTIPLIER;
	if (dmg >= this->maxHealth / t)
	{
		this->health += (dmg); 
		GlassSounds::getInstance()->playContact();
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


void GlassPlankObj::setBody(b2Body *body){
	this->pBody = body;
}
GameSprite *GlassPlankObj::getGameSprite()
{
	return this->pGameSprite;
}


void GlassPlankObj::update(b2Vec2 posInMeters, float angleInRadians )
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

