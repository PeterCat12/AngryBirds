#include "AZULCore.h"

#include <list>

#include "irrKlang.h"
#include "TextMan.h"
#include "EnumName.h"
#include "Rect.h"
#include "ImageMan.h"
#include "Image.h"
#include "SpriteBatchManager.h"
#include "SpriteBatch.h"
#include "BoxModel.h"
#include "BoxSprite.h"
#include "CircleModel.h"
#include "CircleSprite.h"
#include "PolyModel.h"
#include "PolySprite.h"
#include "AzulStopWatch.h"
#include "Input.h"
#include "SpriteManipulation.h"
#include "Box2D.h"
#include "GameObject.h"
#include "BirdObject.h"
#include "SmallPigObject.h"
#include "PixelToMeters.h"
#include "Color.h"
#include "AngryContactListener.h"
#include "ScreenLine.h"
#include "GroundObj.h"
#include "PalletObj.h"
#include "WoodPlankObj.h"
#include "GlassPlankObj.h"
#include "MediumPigObj.h"
#include "GlassBlockObj.h"
#include "StoneBlockObj.h"
#include "WoodBlockObj.h"
#include "LevelLoader.h"
#include "BirdObjectManager.h"
#include "GameObjectManager.h"
#include "MultiFixtureObj.h"
#include "PhysicsManager.h"
#include "StaticObj.h"
#include "CircleDynamic.h"
#include "Audio.h"
#include "RandomCommands.h"
#include "PigManager.h"

using namespace irrklang;

AzulStopWatch stopWatch;
AzulStopWatch totalWatch;
GLShaderManager		shaderManager;
ISound *victorySound;
ScreenLine *pLine;
ScreenLine *pLine2;

b2Vec2 normalGrav(0.0f, -10.0f);
b2Vec2 lowGrav(0.0f, -5.0f);


bool setGravity; 
bool reset;
bool themeMusic;
float time;
float time3;

ScreenLine* SetScreenLine(float x, float y);

#define RIGHTANGLE (90.0f * MATH_PI_180)
//-----------------------------------------------------------------------------
//  AzulCore::AzulCore()
//		Game Engine Constructor
//-----------------------------------------------------------------------------
AzulCore::AzulCore()
{
	joystickActive = false;
	printf("createGraphicsWindows()\n");

	// create graphics windows with defaults
	char title[256];
	sprintf_s(title,"%s\n",MONKEY);
	window = createGraphicsWindow(title, WindowViewWidth , WindowViewHeight);

	// inputs creation
	initInputInterface(window, joystickActive);
}


//-----------------------------------------------------------------------------
// AzulCore::Initialize()
//		Allows the engine to perform any initialization it needs to before 
//      starting to run.  This is where it can query for any required services 
//      and load any non-graphic related content. 
//-----------------------------------------------------------------------------
void AzulCore::Initialize()
{
	time = 0;
	AZUL_UNUSED( window );

	// Rendering Context
	this->SetupRC();

	// Setup & compile shaders
	shaderManager.InitializeStockShaders();

	//initialize the sound system
	//unit scaler 
	UnitScale::Create( 50.0f );

	// Setup the managers
	TextMan::Create();
	ImageMan::Create();
	SpriteBatchManager::Create();

	// Initialize timer
	AzulStopWatch::initStopWatch();
	AzulStopWatch stopWatch;
	reset = false;
	themeMusic = false;
}

b2World *pWorld;
b2Body *pBody;
b2Body *pBody2;
b2Body *pBody3;

enum type{ Static, Dynamic};

//-----------------------------------------------------------------------------
// AzulCore::LoadContent()
//		Allows you to load all content needed for your engine,
//	    such as objects, graphics, etc.
//-----------------------------------------------------------------------------
void AzulCore::LoadContent()
{
	setGravity = false;
	LevelLoader *LL = LevelLoader::getInstance();
	if(reset == false)
	{
		// Initially setup the camera  (screen size)
		Camera::setViewport( 0, 0, WindowViewWidth, WindowViewHeight);
		Camera::setOrthographic( (float) -WindowViewWidth/2,
			(float) WindowViewWidth/2, (float) -WindowViewHeight/2, 
			(float) WindowViewHeight/2, 1.0f, 1000.0f);
		Camera::setOrientAndPosition( Vect(0.0f,1.0f,0.0f), 
			Vect(0.0f,0.0f, -1.0f), Vect(0.0f,0.0f, 0.00f) );

		// Create and Load textures                   
		LL->LoadTexturesSpritesImages();

		pWorld = new b2World(lowGrav);
		pLine = SetScreenLine(75,215);
		pLine2 = SetScreenLine(105,215);
	}

	pWorld->SetGravity(lowGrav);

	LL->loadLevel_1(pWorld);
	//LL->loadLevel_2(pWorld);
	victorySound = 0;
	RandomCommands::getInstance()->victory = false;

	if(reset ==false)
	{
		totalWatch.tic();
		stopWatch.tic(); 
		AngryContactListener *myContactListener = new AngryContactListener();
		pWorld->SetContactListener( myContactListener );
		Audio::Start();
	}
	time = totalWatch.timeInSeconds(); 
	reset = false; 
};

extern bool displayData;

//-----------------------------------------------------------------------------
// AzulCore::Update()
//      Called once per frame, update data, tranformations, etc
//      Use this function to control process order
//      Input, AI, Physics, Animation, and Graphics
//-----------------------------------------------------------------------------
void AzulCore::Update()
{
	// Time update.
	//      Get the time that has passed.
	//      Feels backwards, but its not, need to see how much time has passed
	stopWatch.toc();
	stopWatch.tic();
	totalWatch.toc();

	float time2 = totalWatch.timeInSeconds() - time;

	if(setGravity == false && time2 > .25f)
	{
		pWorld->SetGravity(normalGrav);
		setGravity = true;
		GameObjectManager::ZeroHealth();
	}
	
	Audio::Update(time2);

	int32 velocityIterations = 6;
	int32 positionIterations = 2;

	float32 timeStep = 1.0f/60.0f;
	pWorld->Step(timeStep, velocityIterations, positionIterations);

	//Get Input
	BirdObjectManager::updateBirds(window,pLine,pLine2);

	//Update Physics
	PhysicsMan::UpdatePhysics(pWorld);

	// update game
	if( time2 > 0.25f)
	{
		GameObjectManager::UpdateGameObjects();
		if(Audio::Victory())
			reset = true;
		else if(BirdObjectManager::GetSize() == 0)
			reset = true;

		if(reset)
		{
			BirdObjectManager::Reset();
			GameObjectManager::Reset();
			CloudTrailManager::getInstance()->resetLists();
			LoadContent();
		}
	}
	// Camera System - needs to be updated once per frame
	Camera::updateCamera();

	// Input tests - quick and dirty
	//               Not complete, but execised enough to prove its works
	// checking for window quit, leave at bottom of Update()
	if(glfwWindowShouldClose(window))
	{
		this->Quit();
	}
}

//-----------------------------------------------------------------------------
// AzulCore::Draw()
//		This function is called once per frame
//	    Use this for draw graphics to the screen.
//      Only do rendering here
//-----------------------------------------------------------------------------
void AzulCore::Draw()
{
	// Clear the window with current clearing color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	// Add Rendering stuff below this line
	SpriteBatchManager::Process();

	// House keeping
	//    Swap buffers
	//    Poll for Events
	glfwSwapBuffers(window);
	glfwPollEvents();
}

//-----------------------------------------------------------------------------
// AzulCore::UnLoadContent()
//       unload content (resources loaded above)
//       unload all content that was loaded before the Engine Loop started
//-----------------------------------------------------------------------------
void AzulCore::UnLoadContent()
{
	// Todo - fix 
	//	TextureManager::deleteTextures();
	//	pSndEngine->drop();
	delete pLine;
	delete pLine2;
	Audio::unload();
	this->ShutdownRC(window);
}

ScreenLine* SetScreenLine(float x, float y)
{
	Vect2D A(ORIGINAL_X,ORIGINAL_Y);
	Vect2D B(x,y);
	return new ScreenLine( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_Poly, 4.0f, Color(Black),  A, B );
}



// End of File: AzulCore.cpp