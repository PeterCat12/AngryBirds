

#include "StaticObj.h"
#include "PixelToMeters.h"

StaticObject::StaticObject(Rect centerArea,b2World *pWorld, float _angle,  SpriteName::Name sName, ImageName::Name iName)
{
	this->centerX = centerArea.x;
	this->centerY = centerArea.y;
	this->angle = _angle;
	sName;
	iName;
	_angle;
	this->pGameSprite1 = new GameSprite(SpriteBatchName::SpriteBatch_Middleground, SpriteName::Sprite_Glass_MedPlank,
		ImageName::Image_Glass_MedPlank, centerArea);
	pGameSprite1->angle = angle;

	this->pDebugSprite1 = new BoxSprite(SpriteBatchName::SpriteBatch_Debug,
									SpriteName::Sprite_Box, 2.0f, Vect(55,0,255,255),centerArea);
	pDebugSprite1->angle = angle;

	pBody = 0;

	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(PixelToMeter(centerX),PixelToMeter(centerY));
	groundBodyDef.angle = angle;
	this->pBody = pWorld->CreateBody(&groundBodyDef);

	b2PolygonShape groundBox;
	groundBox.SetAsBox(PixelToMeter(pDebugSprite1->origWidth* 0.5f),PixelToMeter(pDebugSprite1->origHeight * 0.5f));

	gameObjName = GameObjectName::GameObject_StaticBody;

	b2FixtureDef groundFixtureDef;
	groundFixtureDef.shape = &groundBox;
	groundFixtureDef.friction = 50.0f;
	groundFixtureDef.restitution = 0.0f;
	pBody->CreateFixture(&groundFixtureDef);   //&groundBox, 0.0f);

	pBody->GetFixtureList()->SetUserData(this);
	pBody->SetUserData( this);
}


void StaticObject::endContact()
{
}

void StaticObject::startContact()
{}

void StaticObject::update(b2Vec2 posInMeters, float angleInRadians )
{

	//angleInRadians;
	//// updates position and angle from physics update
	this->centerX =  MeterToPixel(posInMeters.x );
	this->centerY =  MeterToPixel(posInMeters.y);
	this->angle = angleInRadians;

	//this->pDebugSprite1->posX = centerX;
	//this->pDebugSprite1->posY = centerY;


		// push the values to the GameSprite
		pGameSprite1->posX = centerX;
		pGameSprite1->posY = centerY;
		pGameSprite1->angle = angle;

		// push the values to the DebugSprite
		pDebugSprite1->posX  = centerX;
		pDebugSprite1->posY = centerY;
		pDebugSprite1->angle = angle;

		//pFix = pFix->GetNext();

}

	GameObjectName::Name StaticObject::getName()
	{
		return this->gameObjName;
	}
