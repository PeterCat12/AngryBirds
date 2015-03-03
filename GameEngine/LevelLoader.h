#ifndef LEVEL_LOADER_H
#define LEVEL_LOADER_H

#include "TextMan.h"
#include "ImageMan.h"
#include "GameObject.h"
#include "ScreenLine.h"
#include "Vect2D.h"
#include "Input.h"
#include "Box2D.h"
#include "Color.h"

#include "GameObjectManager.h"
#include "BirdObjectManager.h"
#include "BirdObject.h"
#include "YellowBirdObject.h"
#include "BlueBird.h"
#include "WhiteBird.h"
#include "GreenBird.h"
#include "SmallPigObject.h"
#include "GroundObj.h"
#include "PalletObj.h"
#include "WoodPlankObj.h"
#include "GlassPlankObj.h"
#include "MediumPigObj.h"
#include "GlassBlockObj.h"
#include "StoneBlockObj.h"
#include "WoodBlockObj.h"


class LevelLoader
{
public:
	static LevelLoader *getInstance();

	void LoadTexturesSpritesImages();

	void loadTextures();
	void loadBackgroundImages_And_Sprites();
	void loadNonBackGroundImages();
	void loadLevel_1(b2World *pWorld);
	void loadLevel_2(b2World *pWorld);
	void loadTestBedYellowBird(b2World *pWorld);
	void loadPATestBed(b2World *pWorld);
	void loadPA3TestBed(b2World *pWorld);


private:
	ScreenLine *pLine;
	ScreenLine *pLine2;

	LevelLoader();

	void SimulateSetup();


	static bool instanceFlag;
	static LevelLoader *single;
};
#endif


