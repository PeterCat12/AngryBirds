#include "MultiFixtureObj.h"
#include "PixelToMeters.h"

fixObj::fixObj(Rect centerArea,b2World *pWorld, float _angle,  SpriteName::Name sName, ImageName::Name iName)
{
	iName;
	sName;
	pWorld;
	gameObjName = GameObjectName::GameObject_MultiFix;
	centerX = centerArea.x;
	centerY= centerArea.y;
	angle = _angle;

	pGameSprite1 = new GameSprite(SpriteBatchName::SpriteBatch_Middleground, SpriteName::Sprite_PATEST1,
		ImageName::Image_Wood_Plank, Rect(centerX, centerY, centerArea.width, centerArea.height) );   //Rect(400.0f,300.0f, 42.5f,11.0f)); 
	pGameSprite1->angle =angle;

	pDebugSprite1 =  new BoxSprite(SpriteBatchName::SpriteBatch_Debug,
		SpriteName::Sprite_Box, 2.0f, Vect(55,0,255,255),centerArea);
	pDebugSprite1->angle = angle;
}

void fixObj::update(b2Vec2 posInMeters, float angleInRadians )
{
	 //updates position and angle from physics update
	this->centerX =  MeterToPixel(posInMeters.x );
	this->centerY =  MeterToPixel(posInMeters.y);
	this->angle = angleInRadians;



		b2Fixture *pFix = this->pBody->GetFixtureList();
		

	while( pFix != 0 )
	{
		//fixObj *pGObj = (fixObj *)pFix->GetUserData();
		b2MassData again;
		pFix->GetMassData(&again);
		b2Vec2 maybe =pBody->GetWorldPoint(again.center);
		fixObj *pGObj = (fixObj *)pFix->GetUserData(); 
		// push the values to the GameSprite
		pGObj->pGameSprite1->posX = MeterToPixel( maybe.x);
		pGObj->pGameSprite1->posY = MeterToPixel(maybe.y);
		pGObj->pGameSprite1->angle =angle;

		// push the values to the DebugSprite
		pGObj->pDebugSprite1->posX  = MeterToPixel( maybe.x);
		pGObj->pDebugSprite1->posY =  MeterToPixel(maybe.y);
		pGObj->pDebugSprite1->angle = angle;

		pFix = pFix->GetNext();
	}
}