#include "AzulCore.h"
#include "GameSprite.h"

class SpriteManipulation{

public:
	static void RotateSprite(GameSprite *Sprite, float Rate);
	static void MoveRight(GameSprite *Sprite, float Rate);
	static void MoveUp(GameSprite *Sprite, float Rate);
};