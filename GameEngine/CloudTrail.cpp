#include "CloudTrail.h"


CloudTrail_Obj::CloudTrail_Obj(float centerX, float centerY)
{
	this->pGameSprite = new GameSprite(SpriteBatchName::SpriteBatch_Middleground, SpriteName::Sprite_CloudTrail_1, ImageName::Image_CloudTrail_1, Rect(centerX, centerY, 10.0f, 10.0f) );
}


CloudTrail_Obj::~CloudTrail_Obj()
{
	SBNode *pSBNode;
	pSBNode = SpriteBatchManager::Find(this->pGameSprite->spriteBatchName);
	pSBNode->removeSprite( this->pGameSprite );
}