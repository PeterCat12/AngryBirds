#ifndef SPRITEMAN_H
#define SPRITEMAN_H

#include "Man.h"
#include "ScreenLine.h"
#include "EnumName.h"
#include "Sprite.h"
#include "Rect.h"

class SpriteMan: public Man
{
	static void Create(int _numReserve = 3, int _reserveGrow = 1);
	static void Add(SpriteName::Name _spriteName, SpriteBatchName::Name _batchName, ImageName::Name _imageName, Rect _rect);
	static void Add(ScreenLine * line);
	static Sprite *Find(SpriteName::Name _spriteName);
	static void Remove(Sprite * _sprite);
	static void Clear();

protected:
	ManLink *SpriteMan::privGetNewObj();

private: 
	static SpriteMan *privInstance();
	static void privRemove(Sprite * _sprite);
	SpriteMan();
};
#endif // !1
