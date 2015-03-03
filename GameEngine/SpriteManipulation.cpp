#include "SpriteManipulation.h"


void SpriteManipulation::RotateSprite(GameSprite *Sprite, float Rate){
	Sprite->angle += Rate;
}

void SpriteManipulation::MoveRight(GameSprite *Sprite, float Rate){
	Sprite->posX += Sprite->directionRight * Rate;
	if (Sprite->posX > 800.0|| Sprite->posX < 0.0f)
		{
			Sprite->directionRight *= -1.0f;
		}
}
/*
static float pB2_dir = 1.0f;
		pB2->posX += pB2_dir * 3.0f;
		if (pB2->posX > 800.0 || pB2->posX < 0.0f)
		{
			pB2_dir *= -1.0f;
		}
*/


void SpriteManipulation::MoveUp(GameSprite *Sprite, float Rate){
	Sprite->posY += Sprite->directionUp * Rate;
	if (Sprite->posY > 600.0|| Sprite->posY < 0.0f)
		{
			Sprite->directionUp *= -1.0f;
		}
}


//ToDo needs error checking
/*void SpriteManipulation::RotateSprite(GameSprite *Sprite, float Rate){
	Sprite->angle = Rate;
}
//void SpriteManipulation(GameSprite *Sprite, float Rate){
	Sprite->posX =+ Sprite->directionRight * Rate;
	if (Sprite->posX > 800.0|| Sprite->posX < 0.0f)
		{
			Sprite->directionRight *= -1.0f;
		}
}

	//void SpriteManipulation(GameSprite *Sprite, float Rate){
		Sprite->posY =+ Sprite->directionUp * Rate;
	if (Sprite->posY > 600.0|| Sprite->posY < 0.0f)
		{
			Sprite->directionUp *= -1.0f;
		}
	}*/