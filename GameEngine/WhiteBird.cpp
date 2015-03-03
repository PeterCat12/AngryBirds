
#include "WhiteBird.h"



WhiteBird::WhiteBird(float centerX, float centerY, b2World *pWorld)
	: BirdObject(GameObjectName::GameObject_WhiteBird)
{
	state = IDLE;
	bAbility = false;
	select = false;
	this->oldPosition = b2Vec2(0,0);
	size = 25;
	this->cycleCount = 0;
	this->fired = false;
	this->madeContact = false;
	this->pWorld = pWorld;
	this->pGameSprite = new GameSprite( SpriteBatchName::SpriteBatch_Middleground, SpriteName::Sprite_White1, ImageName::Image_White, Rect(centerX, centerY, size, size) );
	this->centerX = centerX;
	this->centerY = centerY;
	this->health = 0.0f;
	this->stationaryCount = 0;
	//Don't waste time fiddling with debug sprite too much. save that for tweaking on Monday
	this->pDebugSprite  = new CircleSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_Circle, 2.0f, Vect(255,255,255,255),Rect(centerX, centerY,20,20 ) );
	pBody = 0;
	destory = false;
	this->gameObjName = GameObjectName::GameObject_WhiteBird;
	InitilizeBody();
}

void WhiteBird::ability()
{
		used = true;
		Audio::getISoundEngine()->play2D("EggPush.mp3",false,false,true);
		Audio::getISoundEngine()->play2D("bird misc a7.mp3",false,false,true);
		egg = new Egg(centerX,centerY-50,pWorld);
		egg->pBody->ApplyLinearImpulse(b2Vec2( 0, -5), pBody->GetWorldCenter(), true);
		GameObjectManager::getInstance()->addGameObjectToList(egg);
		//Put this in sprite swap
		state = ABILITY;
		bAbility = true;
		SwapSprite(state);
		//this->pGameSprite->spriteModel->SwapImage(ImageName::Image_White_Deflated);
		pBody->SetLinearDamping(1.0f);
		pBody->ApplyLinearImpulse(b2Vec2(0, 200), pBody->GetWorldCenter(), true);
		pBody->ApplyAngularImpulse(0.5f, true);
}


void WhiteBird::SwapSprite(MyBirdState _state)
{
	switch (_state)
	{
	case LAUNCHER :
		this->pGameSprite->spriteModel->SwapImage(ImageName::Image_White);
		//Play noises here? that'd be a good thing to do...
		break;
	case FLYING :
		this->pGameSprite->spriteModel->SwapImage(ImageName::Image_WhiteFlying);
		break;
	case AFTERCONTACT :
		if(bAbility)
			break;
		else
			this->pGameSprite->spriteModel->SwapImage(ImageName::Image_WhiteDmg);
		break;
	case BLINKING :
		this->pGameSprite->spriteModel->SwapImage(ImageName::Image_WhiteBlinking);
		break;
	case ABILITY:
		this->pGameSprite->spriteModel->SwapImage(ImageName::Image_White_Deflated);
		break;
	default:
		this->pGameSprite->spriteModel->SwapImage(ImageName::Image_White);
		break;
	}

}


void WhiteBird::playLaunchMusic() 
{
	Audio::getISoundEngine()->play2D("WhiteFlying.mp3",false,false,true);
}

void WhiteBird::playContactMusic()
{
	int randNum = (rand() % 4);
	if(randNum == 0)
		Audio::getISoundEngine()->play2D("white collision a1.mp3",false,false,true);
	else if(randNum == 1)
		Audio::getISoundEngine()->play2D("white collision a2.mp3",false,false,true);
	else if(randNum == 2)
		Audio::getISoundEngine()->play2D("white collision a3.mp3",false,false,true);
	else if(randNum == 3)
		Audio::getISoundEngine()->play2D("white collision a4.mp3",false,false,true);
}

void WhiteBird::playSelect()
{
	Audio::getISoundEngine()->play2D("WhiteSelect.mp3",false,false,true);
	select = true;
}

WhiteBird::~WhiteBird()
{
	Audio::getISoundEngine()->play2D("birdDestroyed.mp3",false,false,true);
	SBNode *pSBNode;
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

void WhiteBird::InitilizeBody()
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
	pBody->SetActive(false);
}