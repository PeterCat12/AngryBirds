
#include "BirdObject.h"
#include "Audio.h"
#include <math.h>


BirdObject::BirdObject(GameObjectName::Name name)
{
	srand(0);
	select = false;
	this->gameObjName = name;
	this->used = false;
	this->madeContact = false;
	this->fired = false;
}

void BirdObject::ability()
{

}

BirdObject::BirdObject(float centerX, float centerY, b2World *pWorld)
{
	select = false;
	state = IDLE;
	srand(0);
	chirping = false;
//	srand(totalWatch.timeInSeconds());
	//timeToChirp = rand() % (21 - 10) + 10;
	this->oldPosition = b2Vec2(0,0);
	size = 25;
	this->cycleCount = 0;
	this->fired = false;
	this->used = false;
	this->madeContact = false;
	this->pWorld = pWorld;
	this->pGameSprite = new GameSprite( SpriteBatchName::SpriteBatch_Middleground, SpriteName::Sprite_Red_1, ImageName::Image_RedIdle, Rect(centerX, centerY, size, size) );
	this->centerX = centerX;
	this->centerY = centerY;
	this->health = 0.0f;
	this->stationaryCount = 0;
	this->pDebugSprite  = new CircleSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_Circle, 2.0f, Vect(255,255,255,255),this->pGameSprite);
	pBody = 0;
	destory = false;
	this->gameObjName = GameObjectName::GameObject_RedBird;
	InitilizeBody();
}


BirdObject::~BirdObject()
{
	Audio::getISoundEngine()->play2D("birdDestroyed.mp3",false,false,true);
	if(this->gameObjName == GameObjectName::GameObject_RedBird)
	{
		SBNode *pSBNode;
		pSBNode = SpriteBatchManager::Find(this->pGameSprite->spriteBatchName);
		pSBNode->removeSprite( this->pGameSprite );
		pSBNode = SpriteBatchManager::Find(this->pDebugSprite->spriteBatchName);
		pSBNode->removeSprite(this->pDebugSprite);
		pWorld->DestroyBody(this->pBody);
	}
	 if(this->madeContact == false)
	{
		madeContact = true;
		CloudTrailManager::getInstance()->changeCurrentList();
	}
}

void BirdObject::InitilizeBody()
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

	b2FixtureDef birdFixtureDef;
	birdFixtureDef.shape = &birdCircle;
	birdFixtureDef.density = REDBIRD_DENSITY;
	birdFixtureDef.friction = REDBIRD_FRICTION;
	birdFixtureDef.restitution = REDBIRD_RESTITUTION;
	pBody->CreateFixture( &birdFixtureDef);
	pBody->GetFixtureList()->SetUserData(this);
	pBody->SetUserData(this);
	pBody->SetActive(false);
}

//needs destructor
b2Body *BirdObject::getBody()
{
	return this->pBody;
}

void BirdObject::zeroHealth()
{
	return;
}

GameObjectName::Name BirdObject::getObjectName()
{
	return this->gameObjName;
}

void BirdObject::updateHealth(float dmg)
{
	if(this->madeContact == false)
	{
		madeContact = true;
		state = AFTERCONTACT;
		SwapSprite(AFTERCONTACT);
		CloudTrailManager::getInstance()->changeCurrentList();
	}
		if(dmg > 100.0f)
			playContactMusic();
	dmg;
}

bool BirdObject::updateGame()
{

	if(this->pBody->IsActive() && this->madeContact == false)
	{
		//call some sort of manager? Think that's the best way to do it... Because then I can extern total time, create them every third second or something.
		//cycleCount = 0;
		
		b2Vec2 dist = pBody->GetPosition() - this->oldPosition;
		if(dist.Length() > .5)
		{
			this->oldPosition = pBody->GetPosition();
			CloudTrailManager::getInstance()->spawnCloud(this->centerX, this->centerY);
		}
	}
	cycleCount++;
	if(cycleCount == timeToChirp && chirping == false)
	{
		chirping = true;
		cycleCount = 0;
		//this->pGameSprite->spriteModel->SwapImage( );

	}


	bool deleteMe = false;


	float angle = this->pBody->GetAngularVelocity();
	b2Vec2 vel = this->pBody->GetLinearVelocity();
	float delta = 0.04f;

	if( this->pBody->IsActive() )
	{
		if( angle < delta && fabsf(vel.x) < delta && fabsf(vel.y) < delta )
		{
			stationaryCount++;
			if( stationaryCount > 3 )
			{
				this->pGameSprite->display = false;
				this->pDebugSprite->display = false;
				this->pBody->SetActive(false);
				deleteMe = true;
			}
		}
		else
		{
			this->stationaryCount = 0;
		}
	}
	if(this->centerY < -100 )
		deleteMe = true;
	return deleteMe;
}

//ImageName::Name getNextImageName( GameObjectName::Name currName,HealthStatus HStatus );
ImageName::Name BirdObject::getNextImageName( GameObjectName::Name currName,HealthStatus HStatus)
{
	//Birds need a swap image...
	currName;
	HStatus;
	ImageName::Name tmp = ImageName::Image_Alien_Small;

	return tmp;
}
void BirdObject::SwapSprite(MyBirdState _state)
{
	switch (_state)
	{
	case LAUNCHER :
		this->pGameSprite->spriteModel->SwapImage(ImageName::Image_RedLauncher);
		//Play noises here? that'd be a good thing to do...
		break;
	case FLYING :
		this->pGameSprite->spriteModel->SwapImage(ImageName::Image_RedFlying);
		break;
	case AFTERCONTACT :
		this->pGameSprite->spriteModel->SwapImage(ImageName::Image_RedDmg);
		break;
	default:
		this->pGameSprite->spriteModel->SwapImage(ImageName::Image_RedIdle);
		break;
	}
}

 GameSprite *BirdObject::getGameSprite()
 {
	 return this->pGameSprite;
 }

float BirdObject::getPosX(){
	return this->centerX;
}
float BirdObject::getPosY(){
	return this->centerY;
}

void BirdObject::playLaunchMusic()
{
	Audio::getISoundEngine()->play2D("red flying.mp3",false,false,true);
}

void BirdObject::playContactMusic()
{
	int randNum = (rand() % 4);
	if(randNum == 0)
		Audio::getISoundEngine()->play2D("red collision a1.mp3",false,false,true);
	else if(randNum == 1)
		Audio::getISoundEngine()->play2D("red collision a2.mp3",false,false,true);
	else if(randNum == 2)
		Audio::getISoundEngine()->play2D("red collision a3.mp3",false,false,true);
	else if(randNum == 3)
		Audio::getISoundEngine()->play2D("red collision a4.mp3",false,false,true);
}

void BirdObject::playSelect()
{
	select = true;
	Audio::getISoundEngine()->play2D("red select.mp3",false,false,true);
}


void BirdObject::LaunchBird(b2Vec2 speed)
{
	pBody->ApplyLinearImpulse(speed, pBody->GetWorldCenter(),true);
	//play launch mp3
	playLaunchMusic();
	pBody->SetActive(true);
	fired = true;
	state = FLYING;
	SwapSprite(FLYING);
}

void BirdObject::update(b2Vec2 posInMeters, float angleInRadians )
{
	 //updates position and angle from physics update
	this->centerX =  MeterToPixel(posInMeters.x );
	this->centerY =  MeterToPixel(posInMeters.y);
	this->angle = angleInRadians;

	// push the values to the GameSprite
	this->pGameSprite->posX = centerX;
	this->pGameSprite->posY = centerY;
	this->pGameSprite->angle = angle;

	// push the values to the DebugSprite
	this->pDebugSprite->posX = centerX;
	this->pDebugSprite->posY = centerY;
	this->pDebugSprite->angle= angle;	
}

