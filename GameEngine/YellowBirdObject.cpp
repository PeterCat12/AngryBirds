#include "YellowBirdObject.h"
#include "Vect2D.h"

YellowBirdObject::YellowBirdObject(float centerX, float centerY, b2World *pWorld)
	: BirdObject(GameObjectName::GameObject_YellowBird)
{
	size = 25;
	state = IDLE;
	this->oldPosition = b2Vec2(0,0);
	this->cycleCount = 0;
	this->fired = false;
	this->madeContact = false;
	this->pWorld = pWorld;
	this->pGameSprite = new GameSprite( SpriteBatchName::SpriteBatch_Middleground, SpriteName::Sprite_Yellow1, ImageName::Image_Yellow, Rect(centerX, centerY, size, size) );
	this->centerX = centerX;
	this->centerY = centerY;
	this->health = 0.0f;
	this->stationaryCount = 0;

	this->pDebugSprite  = new CircleSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_Circle, 2.0f, Vect(255,255,255,255),this->pGameSprite);
	pBody = 0;
	destory = false;
	this->gameObjName = GameObjectName::GameObject_YellowBird;
	InitilizeBody();
}




YellowBirdObject::~YellowBirdObject()
{
	SBNode *pSBNode;
		Audio::getISoundEngine()->play2D("birdDestroyed.mp3",false,false,true);
	pSBNode = SpriteBatchManager::Find(this->pGameSprite->spriteBatchName);
	pSBNode->removeSprite( this->pGameSprite );
	pSBNode = SpriteBatchManager::Find(this->pDebugSprite->spriteBatchName);
	pSBNode->removeSprite(this->pDebugSprite);
	pWorld->DestroyBody(this->pBody);
	 if(this->madeContact == false)
	{
		madeContact = true;
		CloudTrailManager::getInstance()->changeCurrentList();
	}

}

void YellowBirdObject::InitilizeBody()
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
	birdFixtureDef.density = YELLOWBIRD_DENSITY;
	birdFixtureDef.friction = YELLOWBIRD_FRICTION;
	birdFixtureDef.restitution = YELLOWBIRD_RESTITUTION;
	pBody->CreateFixture( &birdFixtureDef);
	pBody->GetFixtureList()->SetUserData(this);
	pBody->SetUserData(this);
	pBody->SetActive(false);
}


void YellowBirdObject::ability()
{
	state = ABILITY;
	playContactMusic();
	SwapSprite(state);
	b2Vec2 vel(pBody->GetLinearVelocity());
	b2Vec2 newVel(vel.x * 2.0f, vel.y * 2.0f);
	pBody->SetLinearVelocity(newVel);
	used = true;
	Audio::getISoundEngine()->play2D("special boost.mp3",false,false,true);
}

void YellowBirdObject::playLaunchMusic()
{
	Audio::getISoundEngine()->play2D("yellow flying.mp3",false,false,true);
}
void YellowBirdObject::playContactMusic()
{
	int randNum = (rand() % 4);
	if(randNum == 0)
		Audio::getISoundEngine()->play2D("yellow collision a1.mp3",false,false,true);
	else if(randNum == 1)
		Audio::getISoundEngine()->play2D("yellow collision a2.mp3",false,false,true);
	else if(randNum == 2)
		Audio::getISoundEngine()->play2D("yellow collision a3.mp3",false,false,true);
	else if(randNum == 3)
		Audio::getISoundEngine()->play2D("yellow collision a4.mp3",false,false,true);
}

void YellowBirdObject::playSelect()
{
	select = true;
	Audio::getISoundEngine()->play2D("yellow select.mp3",false,false,true);
}



void YellowBirdObject::SwapSprite(MyBirdState _state)
{
		switch (_state)
	{
	case LAUNCHER :
		this->pGameSprite->spriteModel->SwapImage(ImageName::Image_YellowLauncher);
		//Play noises here? that'd be a good thing to do...
		break;
	case FLYING :
		this->pGameSprite->spriteModel->SwapImage(ImageName::Image_YellowFlying);
		break;
	case AFTERCONTACT :
		this->pGameSprite->spriteModel->SwapImage(ImageName::Image_YellowContact);
		break;
	case BLINKING :
		this->pGameSprite->spriteModel->SwapImage(ImageName::Image_YellowLauncher);
		break;
	case ABILITY:
		this->pGameSprite->spriteModel->SwapImage(ImageName::Image_YellowAbility);
		break;
	default:
		this->pGameSprite->spriteModel->SwapImage(ImageName::Image_Yellow);
		break;
	}
}