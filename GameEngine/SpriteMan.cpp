#include "SpriteMan.h"
#include "GameSprite.h"
#include "EnumName.h"


SpriteMan::SpriteMan()
{
}

void SpriteMan::Create(int _numReserve /*= 3*/, int _reserveGrow /*= 1*/)
{
	privInstance()->privCreate(_numReserve,_reserveGrow);
}

void SpriteMan::Add(SpriteName::Name _spriteName, SpriteBatchName::Name _batchName, ImageName::Name _imageName, Rect _rect)
{
	SpriteMan *pManager = privInstance();

	//Get a Object off the List
	Sprite* pSprite = (Sprite *)pManager->privGetReserveObject();

	// Initialize Object
	pSprite->Set(_spriteName, _batchName, _imageName, _rect);
}

void SpriteMan::Add(ScreenLine * line)
{
	SpriteMan* pManager = privInstance();
	pManager->privActiveAddToFront( (ManLink*) line, pManager->active);
}

Sprite * SpriteMan::Find(SpriteName::Name _ImageName)
{
	// find the object
	return (GameSprite *) privInstance()->privFind(ImageName( (EnumName::Name)_ImageName ) );
}

SpriteMan * SpriteMan::privInstance()
{
	static SpriteMan instance;
	return &instance;
}

void SpriteMan::Remove(Sprite * _sprite)
{
	SpriteMan *pManager = privInstance();

	pManager->privActiveRemoveNode(_sprite, pManager->active);
}

void SpriteMan::Clear()
{
	SpriteMan * pMan = privInstance();

	ManLink * ptr = pMan->active;

	while(ptr != 0)
	{
		pMan->Remove((Sprite *)ptr);

		ptr = ptr->next;
	}
}

ManLink * SpriteMan::privGetNewObj()
{
	ManLink * pObj = new GameSprite();
	return pObj;
}

void SpriteMan::privRemove(Sprite * _sprite)
{
	SpriteMan *pMan = privInstance();

	pMan->privActiveRemoveNode(_sprite, pMan->active);

	delete _sprite;
}
