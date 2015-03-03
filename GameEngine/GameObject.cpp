
#include "GameObject.h"
#include "BoxSprite.h"
#include "Box2D.h"
#include "PixelToMeters.h"
//
//GameObject::GameObject( GameObjectName::Name name, GameSprite *gSprite,  Shape(*dSprite))
//{
//	this->gameObjName = name;
//	this->pGameSprite = gSprite;
//	//this->pBoxSprite = dSprite;
//	this->pShape = dSprite;
//
//	this->pBody = 0;
//
//	this->pos.x = dSprite->box->posX;
//	this->pos.y = dSprite->box->posY;
//	this->angle = dSprite->box->angle;
//}
//
//GameObject::GameObject(float centerX, float centerY, float angle, b2World *pWorld, float width, float height, SpriteName::Name sName, ImageName::Name IName)
//{
//	this->height= height;
//	this->width = width;
//	this->pWorld = pWorld;
//	
//	this->pGameSprite = new GameSprite( SpriteBatchName::SpriteBatch_Middleground,sName, IName, Rect(centerX, centerY, width, height) );
//	this->pGameSprite->angle = angle;
//	this->angle = angle;
//	//this->bodyType = bodyType;
//	this->centerX = centerX;
//	this->centerY = centerY;
//	this->pDebugSprite = new BoxSprite(SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_Box, 2.0f, Vect(55,0,255,255), pGameSprite);
//	pBody = 0;
//}
//
//GameObjectName::Name GameObject::getObjectName()
//{
//	return GameObjectName::Not_Initialized;
//}
//
//
//void GameObject::InitilizeBody(){
//
//
//}
//
//float GameObject::getDebugSpritePositionX(){
//	return this->pShape->box->posX;
//}
//float GameObject::getDebuSpritePositionY(){
//	return this->pShape->box->posY;
//}
//
//float GameObject::getDebugSpriteOrigWidth()
//{
//	return this->pShape->box->origWidth;
//}
//float GameObject::getDebugSpriteOrigHeight()
//{
//	return this->pShape->box->origHeight;
//}
//
//b2Body *GameObject::getBody()
//{
//	return this->pBody;
//}
//
//float GameObject::getPosX(){
//	return this->pos.x;
//}
//float GameObject::getPosY(){
//	return this->pos.y;
//}
//
//
//float GameObject::getAngle()
//{
//	return this->angle;
//}
//
//void GameObject::setBody(b2Body *body){
//	this->pBody = body;
//}
//GameSprite *GameObject::getGameSprite()
//{
//	return this->pGameSprite;
//}
//float GameObject::getSpritePosX()
//{
//	return this->pGameSprite->posX;
//}
//float GameObject::getSpritePosY()
//{
//	return this->pGameSprite->posY;
//}
//
//
//
//void GameObject::update(b2Vec2 posInMeters, float angleInRadians )
//{
//	// updates position and angle from physics update
//	this->pos.x =  MeterToPixel(posInMeters.x );
//	this->pos.y =  MeterToPixel(posInMeters.y);
//	this->angle = angleInRadians;
//
//
//		// push the values to the GameSprite
//		this->pGameSprite->posX = pos.x;
//		this->pGameSprite->posY = pos.y;
//		this->pGameSprite->angle = angle;
//
//		// push the values to the DebugSprite
//		this->pShape->box->posX  = pos.x;
//		this->pShape->box->posY = pos.y;
//		this->pShape->box->angle = angle;
//}
//
