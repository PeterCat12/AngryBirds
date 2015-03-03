
#include "BlueBird.h"

BlueBird::BlueBird(float centerX, float centerY, b2World *pWorld, b2Vec2 velocity)
	: BirdObject(GameObjectName::GameObject_BlueBirdSpawn)
{
	state =FLYING;
	size = 20;
	select = false;
	copy = true;
	this->oldPosition = b2Vec2(0,0);
	this->cycleCount = 0;
	this->fired = true;
	this->madeContact = false;
	this->pWorld = pWorld;
	this->pGameSprite = new GameSprite( SpriteBatchName::SpriteBatch_Middleground, SpriteName::Sprite_Blue1, ImageName::Image_Blue, Rect(centerX, centerY, size, size) );
	this->centerX = centerX;
	this->centerY = centerY;
	this->health = 0.0f;
	this->stationaryCount = 0;
	this->pDebugSprite  = new CircleSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_Circle, 2.0f, Vect(255,255,255,255),this->pGameSprite);
	pBody = 0;
	destory = false;
	this->gameObjName = GameObjectName::GameObject_BlueBirdSpawn;
	InitilizeBody();
	pBody->SetLinearVelocity(velocity);
	pBody->SetActive(true);
	SwapSprite(state);
}


void BlueBird::SwapSprite(MyBirdState _state)
{
	select = false;
	switch (_state)
	{
	case LAUNCHER :
		this->pGameSprite->spriteModel->SwapImage(ImageName::Image_Blue);
		//Play noises here? that'd be a good thing to do...
		break;
	case FLYING :
		this->pGameSprite->spriteModel->SwapImage(ImageName::Image_BlueFlying);
		break;
	case AFTERCONTACT :
		this->pGameSprite->spriteModel->SwapImage(ImageName::Image_BlueDmg);
		break;
	case BLINKING :
		this->pGameSprite->spriteModel->SwapImage(ImageName::Image_BlueBlinking);
		break;
	case ABILITY :
		this->pGameSprite->spriteModel->SwapImage(ImageName::Image_BlueFlying);
		break;
	default:
		this->pGameSprite->spriteModel->SwapImage(ImageName::Image_Blue);
		break;
	}
}

BlueBird::BlueBird(float centerX, float centerY, b2World *pWorld)
	: BirdObject(GameObjectName::GameObject_BlueBird)
{
	copy = false;
	select  = false;
	size = 20;
	state = IDLE;
	this->oldPosition = b2Vec2(0,0);
	this->cycleCount = 0;
	this->fired = false;
	this->madeContact = false;
	this->pWorld = pWorld;
	this->pGameSprite = new GameSprite( SpriteBatchName::SpriteBatch_Middleground, SpriteName::Sprite_Blue1, ImageName::Image_Blue, Rect(centerX, centerY, size, size) );
	this->centerX = centerX;
	this->centerY = centerY;
	this->health = 0.0f;
	this->stationaryCount = 0;
	this->pDebugSprite  = new CircleSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_Circle, 2.0f, Vect(255,255,255,255),this->pGameSprite);
	pBody = 0;
	destory = false;
	this->gameObjName = GameObjectName::GameObject_BlueBird;
	InitilizeBody();
}

	//Audio::getISoundEngine()->play2D("blue select.mp3", false, false, true); 

void BlueBird::playLaunchMusic()
{
	Audio::getISoundEngine()->play2D("blue flying.mp3",false,false,true);
}
void BlueBird::playContactMusic()
{
	int randNum = (rand() % 4);
	if(randNum == 0)
		Audio::getISoundEngine()->play2D("blue collision a1.mp3",false,false,true);
	else if(randNum == 1)
		Audio::getISoundEngine()->play2D("blue collision a2.mp3",false,false,true);
	else if(randNum == 2)
		Audio::getISoundEngine()->play2D("blue collision a3.mp3",false,false,true);
	else if(randNum == 3)
		Audio::getISoundEngine()->play2D("blue collision a4.mp3",false,false,true);
}

void BlueBird::playSelect()
{
	select = true;
	Audio::getISoundEngine()->play2D("blue select.mp3",false,false,true);
}

void BlueBird::updateHealth(float dmg) 
{
		if(madeContact == false)
	{
		state = AFTERCONTACT;
		SwapSprite(state);
	}
	if(this->madeContact == false && copy == false)
	{
		madeContact = true;
		CloudTrailManager::getInstance()->changeCurrentList(); 
		//If you are a copied blue bird dont change the lists...
	}
	if(dmg > 50.0f)
		playContactMusic();
	madeContact = true;
}


void BlueBird::ability()
{
	
		playContactMusic();
		b2Vec2 velocity = this->pBody->GetLinearVelocity();
		b2Vec2 perp = b2Vec2(velocity.y, velocity.x);
		perp.Normalize();

		//center x, centery
		b2Vec2 pos1 = pBody->GetPosition() + PixelToMeter(30.0f) * perp;
		b2Vec2 pos2 = pBody->GetPosition() - PixelToMeter(30.0f) * perp;

		float cos = cosf(0.15f);
		float sin = sinf(0.15f);

		float adjPosX1 = velocity.x * cos + velocity.y * -sin;
		float adjPosY1 = velocity.x * sin + velocity.y * cos;

		float adjPosX2 = velocity.x * cos + velocity.y * sin;
		float adjPosY2 = velocity.x * -sin + velocity.y * cos;
		
		b2Vec2 velocity1 = b2Vec2( adjPosX1, adjPosY1);
		b2Vec2 velocity2 = b2Vec2( adjPosX2, adjPosY2);
		used = true;
		state = ABILITY;
		SwapSprite(state);

		BlueBird * blue1 = new BlueBird(MeterToPixel(pos1.x), MeterToPixel(pos1.y),pWorld, velocity1);
		GameObjectManager::getInstance()->addGameObjectToList(blue1);
		BlueBird * blue2 = new BlueBird(MeterToPixel(pos2.x), MeterToPixel(pos2.y),pWorld, velocity2);
		GameObjectManager::getInstance()->addGameObjectToList(blue2);

}

BlueBird::~BlueBird()
{
	//Understanding inheritance...
		Audio::getISoundEngine()->play2D("birdDestroyed.mp3",false,false,true);
	SBNode *pSBNode;
	pSBNode = SpriteBatchManager::Find(this->pGameSprite->spriteBatchName);
	pSBNode->removeSprite( this->pGameSprite );
	pSBNode = SpriteBatchManager::Find(this->pDebugSprite->spriteBatchName);
	pSBNode->removeSprite(this->pDebugSprite);
	pWorld->DestroyBody(this->pBody);
	if(this->madeContact == false && copy == false)
	{
		madeContact = true;
		CloudTrailManager::getInstance()->changeCurrentList();
	}
}

void BlueBird::InitilizeBody()
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
	birdFixtureDef.density = BLUEBIRD_DENSITY;
	birdFixtureDef.friction = BLUEBIRD_FRICTION;
	birdFixtureDef.restitution = BLUEBIRD_FRICTION;
	pBody->CreateFixture( &birdFixtureDef);
	pBody->GetFixtureList()->SetUserData(this);
	pBody->SetUserData(this);
	pBody->SetActive(false);
}