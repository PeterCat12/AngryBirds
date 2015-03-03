
#include "GreenBird.h"

#define debugOffsetX 5
#define debugOffsetY 5

GreenBird::GreenBird(float centerX, float centerY, b2World *pWorld)
	: BirdObject(GameObjectName::GameObject_GreenBird)
{
	state = IDLE;
	select = false;
	this->oldPosition = b2Vec2(0,0);
//	size = 25;
	 newDir = b2Vec2(0,0);
	abilityB = false;
	this->cycleCount = 0;
	this->fired = false;
	this->madeContact = false;
	this->pWorld = pWorld;
	this->pGameSprite = new GameSprite( SpriteBatchName::SpriteBatch_Middleground, SpriteName::Sprite_Green1, ImageName::Image_Green, Rect(centerX, centerY, 45, 25) );
	this->centerX = centerX;
	this->centerY = centerY;
	this->health = 0.0f;
	this->stationaryCount = 0;
	//Don't waste time fiddling with debug sprite too much. save that for tweaking on Monday
	this->pDebugSprite  = new CircleSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_Circle, 2.0f, Vect(255,255,255,255),Rect(centerX,centerY,20,20) );
	pBody = 0;
	destory = false;
	this->gameObjName = GameObjectName::GameObject_GreenBird;
	InitilizeBody();
}


void GreenBird::SwapSprite(MyBirdState _state)
{
	switch (_state)
	{
	case LAUNCHER :
		this->pGameSprite->spriteModel->SwapImage(ImageName::Image_Green);
		//Play noises here? that'd be a good thing to do...
		break;
	case FLYING :
		this->pGameSprite->spriteModel->SwapImage(ImageName::Image_Green);
		break;
	case AFTERCONTACT :
		this->pGameSprite->spriteModel->SwapImage(ImageName::Image_GreenDmg);
		break;
	case BLINKING :
		this->pGameSprite->spriteModel->SwapImage(ImageName::Image_Green);
		break;
	case ABILITY:
		this->pGameSprite->spriteModel->SwapImage(ImageName::Image_GreenAbility);
		break;
	default:
		this->pGameSprite->spriteModel->SwapImage(ImageName::Image_Green);
		break;
	}
}


 bool GreenBird::updateGame() 
 {
	 if(this->pBody->IsActive() && this->madeContact == false)
	{
		b2Vec2 dist = pBody->GetPosition() - this->oldPosition;
		if(dist.Length() > .5)
		{
			this->oldPosition = pBody->GetPosition();
			CloudTrailManager::getInstance()->spawnCloud(this->centerX, this->centerY);
		}
	}
	bool deleteMe = false;
	turnAround();
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

 void GreenBird::updateHealth(float dmg)
 {
	 if(this->madeContact == false)
	{
		state = AFTERCONTACT;
		SwapSprite(state);
		madeContact = true;
		CloudTrailManager::getInstance()->changeCurrentList();
	}
	 if(dmg > 100.0f)
		 playContactMusic();
	 abilityB = false;
 }

 void GreenBird::ability()
{
		Audio::getISoundEngine()->play2D("boomerang_activate.mp3",false,false,true);
		used = true;
		abilityB = true;
		state = ABILITY;
		SwapSprite(state);
		b2Vec2 direction = pBody->GetLinearVelocity();
		newDir = b2Vec2( -direction.x * 20, 0);
}

void GreenBird::turnAround()
{
	if(abilityB)
	{
		if(pBody->GetLinearVelocity().Length() < 30.f)
		{
			pBody->ApplyForce(newDir, pBody->GetWorldCenter(), true);

		}
		pBody->ApplyAngularImpulse(0.05f, true);
	}
}

void GreenBird::playLaunchMusic() 
{
	Audio::getISoundEngine()->play2D("GreenFlying.mp3",false,false,true);
}

void GreenBird::playContactMusic()
{
	int randNum = (rand() % 4);
	if(randNum == 0)
		Audio::getISoundEngine()->play2D("bird 02 collision a1.mp3",false,false,true);
	else if(randNum == 1)
		Audio::getISoundEngine()->play2D("bird 02 collision a2.mp3",false,false,true);
	else if(randNum == 2)
		Audio::getISoundEngine()->play2D("bird 02 collision a3.mp3",false,false,true);
	else if(randNum == 3)				  
		Audio::getISoundEngine()->play2D("bird 02 collision a4.mp3",false,false,true);
}

void GreenBird::playSelect()
{
	select = true;
	Audio::getISoundEngine()->play2D("boomerang_select.mp3",false,false,true);
}

GreenBird::~GreenBird()
{
		Audio::getISoundEngine()->play2D("birdDestroyed.mp3",false,false,true);
	if(madeContact == false)
	{
		madeContact = true;
		CloudTrailManager::getInstance()->changeCurrentList();
	}
	//Understanding inheritance...
	SBNode *pSBNode;
	pSBNode = SpriteBatchManager::Find(this->pGameSprite->spriteBatchName);
	pSBNode->removeSprite( this->pGameSprite );
	pSBNode = SpriteBatchManager::Find(this->pDebugSprite->spriteBatchName);
	pSBNode->removeSprite(this->pDebugSprite);
	pWorld->DestroyBody(this->pBody);
}

void GreenBird::InitilizeBody()
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.angularDamping = 4.0f;
	bodyDef.position.Set(PixelToMeter(centerX-debugOffsetX), PixelToMeter(centerY-debugOffsetY));
	//bodyDef.position.Set(PixelToMeter(centerX), PixelToMeter(centerY));

	pBody = this->pWorld->CreateBody(&bodyDef);
	pBody->SetUserData(this);
	b2CircleShape birdCircle;
	birdCircle.m_p.Set(0,0);
	birdCircle.m_radius = PixelToMeter(this->pDebugSprite->origHeight * 0.5f);

	b2FixtureDef birdFixtureDef;
	birdFixtureDef.shape = &birdCircle;
	birdFixtureDef.density = GREENBIRD_DENSITY;
	birdFixtureDef.friction = GREENBIRD_FRICTION;
	birdFixtureDef.restitution = GREENBIRD_RESTITUTION;
	pBody->CreateFixture( &birdFixtureDef);
	pBody->GetFixtureList()->SetUserData(this);
	pBody->SetUserData(this);
	pBody->SetActive(false);
}


void GreenBird::update( b2Vec2 posInMeters, float angleInRadians )
{
	
	 //updates position and angle from physics update
	this->centerX =  MeterToPixel(posInMeters.x );// + debugOffsetX ;
	this->centerY =  MeterToPixel(posInMeters.y);// + debugOffsetY;
	this->angle = angleInRadians;

	// push the values to the GameSprite
	this->pGameSprite->posX = centerX + debugOffsetX;
	this->pGameSprite->posY = centerY + debugOffsetY;
	this->pGameSprite->angle = angle;

	// push the values to the DebugSprite
	this->pDebugSprite->posX = centerX;// - debugOffsetX;
	this->pDebugSprite->posY = centerY;//  - debugOffsetY;
	this->pDebugSprite->angle= angle;	
}
