#include "Egg.h"


Egg::Egg(float centerX, float centerY, b2World *pWorld)
	: BirdObject(GameObjectName::GameObject_Egg)
{
	//this->oldPosition = b2Vec2(0,0);
	size = 25;
	state = IDLE;
	//this->cycleCount = 0;
	this->fired = true;
	this->madeContact = false;
	this->pWorld = pWorld;
	this->pGameSprite = new GameSprite( SpriteBatchName::SpriteBatch_Middleground, SpriteName::Sprite_Egg, ImageName::Image_Egg, Rect(centerX, centerY, 25, 25) );
	this->centerX = centerX;
	this->centerY = centerY;
	this->health = 0.0f;
	this->stationaryCount = 0;
	this->pDebugSprite  = new CircleSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_Circle, 2.0f, Vect(255,255,255,255), pGameSprite );
	pBody = 0;
	destory = false;
	this->gameObjName = GameObjectName::GameObject_Egg;
	InitilizeBody();
}

void Egg::updateHealth(float dmg)
{
	dmg;
	if(madeContact == false)
		Audio::getISoundEngine()->play2D("Explosion.mp3",false,false,true);
	madeContact = true;
}


Egg::~Egg()
{
	SBNode *pSBNode;
	pSBNode = SpriteBatchManager::Find(this->pGameSprite->spriteBatchName);
	pSBNode->removeSprite( this->pGameSprite );
	pSBNode = SpriteBatchManager::Find(this->pDebugSprite->spriteBatchName);
	pSBNode->removeSprite(this->pDebugSprite);
	pWorld->DestroyBody(this->pBody);
}

void Egg::InitilizeBody()
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.angularDamping = 4.0f;
	bodyDef.position.Set(PixelToMeter(centerX), PixelToMeter(centerY));
	pBody = this->pWorld->CreateBody(&bodyDef);
	pBody->SetUserData(this);
	b2CircleShape birdCircle;
	birdCircle.m_p.Set(0,0);
	birdCircle.m_radius = PixelToMeter(this->pDebugSprite->origHeight * 0.5f);

//original
	b2FixtureDef birdFixtureDef;
	birdFixtureDef.shape = &birdCircle;
	birdFixtureDef.density = WHITEBIRD_DENSITY;
	birdFixtureDef.friction = WHITEBIRD_FRICTION;
	birdFixtureDef.restitution = WHITEBIRD_RESTITUTION;
	pBody->CreateFixture( &birdFixtureDef);
	pBody->GetFixtureList()->SetUserData(this);
	pBody->SetUserData(this);
}


bool Egg::updateGame(){
	if(madeContact == true)
		return true;
	return false;
}