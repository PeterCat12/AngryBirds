#include "LevelLoader.h"
#include "MultiFixtureObj.h"
#include "StaticObj.h"
#include "CircleDynamic.h"



#define WindowViewWidth 800
#define WindowViewHeight 600
#define RIGHTANGLE (90.0f * MATH_PI_180)

float yOffset = 10.0f;

bool LevelLoader::instanceFlag;

LevelLoader *LevelLoader::single;

LevelLoader *LevelLoader::getInstance()
{
	if(! instanceFlag)
	{
		single = new LevelLoader();
		instanceFlag = true;
		return single;
	}
	else
	{
		return single;
	}
}

void LevelLoader::loadTextures()
{
	TextMan::Load(TextType::Text2D, TextName::Texture_Clouds, "CloudLayer.tga");
	TextMan::Load(TextType::Text2D,TextName::Texture_TreeLayer,"TreeLayer.tga");
	TextMan::Load(TextType::Text2D, TextName::Texture_ForeGround,"foreground.tga");
	TextMan::Load(TextType::Text2D,TextName::Texture_Grass_Behind_Birds,"GrassBehindBirds.tga");

	//BlockSprites textures
	TextMan::Load(TextType::Text2D,TextName::Texture_Wood_Pallet, "MiscSprites.tga");
	TextMan::Load(TextType::Text2D,TextName::Texture_Wood_Plank, "woodBlocks.tga");
	TextMan::Load(TextType::Text2D, TextName::Texture_Unsorted, "unsorted.tga");
	TextMan::Load(TextType::Text2D, TextName::Texture_Glass, "glassBlocks.tga");
	TextMan::Load(TextType::Text2D,TextName::Texture_Stones, "stoneBlocks.tga");
}

LevelLoader::LevelLoader()
{}


void LevelLoader::loadPA3TestBed(b2World *pWorld)
{
		SpriteBatchManager::AddBatch(SpriteBatchName::SpriteBatch_Debug);
		SpriteBatchManager::AddBatch(SpriteBatchName::SpriteBatch_Middleground);

		ImageMan::Add(ImageName::Image_Wood_Plank, TextName::Texture_Wood_Plank, Rect(288, 168, 204, 22) ) ;
		ImageMan::Add(ImageName::Image_Bang, TextName::Texture_Unsorted,Rect(674, 354, 87,89 ) );
		ImageMan::Add(ImageName::Image_Glass_MedPlank, TextName::Texture_Glass,  Rect(288, 345, 85, 20) ) ;
		ImageMan::Add(ImageName::Image_RedDmg, TextName::Texture_Unsorted, Rect(852,892, 48 ,45));

			CircleObj *pBird = new CircleObj(Rect(450.0f, 500.0f, 45,45), pWorld, 0.0f, 
											SpriteName::Sprite_Red_1, ImageName::Image_RedDmg);
			

			//		GameSprite *pBlockSprite = new GameSprite( SpriteBatchName::SpriteBatch_Blocks,SpriteName::Sprite_Block, ImageName::Image_Long_Wood_Block, Rect(300, 50, 400, 50) );
		//BoxSprite *pBlockBox = new BoxSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_Box_Block, 2.0f, Vect(0,0,255,255), pBlockSprite);
			StaticObject *pBlock = new StaticObject(Rect(245, 50, 400, 50),pWorld,0.0f,SpriteName::Sprite_Wood_MedPlank, ImageName::Image_Wood_Plank);

		//GameSprite *pBlock2Sprite = new GameSprite( SpriteBatchName::SpriteBatch_Blocks,SpriteName::Sprite_Block2, ImageName::Image_Long_Wood_Block, Rect(503, 50, 400, 50) );
		//BoxSprite *pBlock2Box = new BoxSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_Box_Block2, 2.0f, Vect(255,255,255,255), pBlock2Sprite);
		StaticObject *pBlock2 = new StaticObject(Rect(653, 50, 400, 50), pWorld, 0.0f, SpriteName::Sprite_Wood_MedPlank, ImageName::Image_Wood_Plank);

		pBlock;
		pBlock2;

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.angularDamping = 4.0f;
	bodyDef.position.Set(PixelToMeter(pBird->centerX), PixelToMeter(pBird->centerY));
	pBird->pBody = pWorld->CreateBody(&bodyDef);
	//pBird->pBody->SetUserData(this);

	b2CircleShape birdCircle;
	birdCircle.m_p.Set(0,0);
	birdCircle.m_radius = PixelToMeter(pBird->pDebugSprite1->origHeight * 0.5f);

	b2FixtureDef birdFixtureDef;
	birdFixtureDef.shape = &birdCircle;
	birdFixtureDef.density = REDBIRD_DENSITY;
	birdFixtureDef.friction = REDBIRD_FRICTION;
	birdFixtureDef.restitution = 0.0f;
	pBird->pBody->CreateFixture( &birdFixtureDef);
	pBird->pBody->GetFixtureList()->SetUserData(pBird);
	pBird->pBody->SetUserData(pBird);
	pBird->pBody->SetActive(true);
}


void LevelLoader::loadPATestBed(b2World *pWorld)
{
		SpriteBatchManager::AddBatch(SpriteBatchName::SpriteBatch_Debug);
		SpriteBatchManager::AddBatch(SpriteBatchName::SpriteBatch_Middleground);

		ImageMan::Add(ImageName::Image_Wood_Plank, TextName::Texture_Wood_Plank, Rect(288, 168, 204, 22) ) ;
		ImageMan::Add(ImageName::Image_Bang, TextName::Texture_Unsorted,Rect(674, 354, 87,89 ) );
		ImageMan::Add(ImageName::Image_Glass_MedPlank, TextName::Texture_Glass,  Rect(288, 345, 85, 20) ) ;
		ImageMan::Add(ImageName::Image_RedDmg, TextName::Texture_Unsorted, Rect(852,892, 48 ,45));
		ImageMan::Add(ImageName::Image_RedIdle, TextName::Texture_Unsorted, Rect(903,798,44,44) );


		StaticObject *pStatic1 = new StaticObject(Rect(300, 70, 350, 50), pWorld,-20.0f * MATH_PI_180,                               //(-20.0f * MATH_PI_180),
												SpriteName::Sprite_Glass_block, ImageName::Image_Glass_Block);
		pStatic1;

		StaticObject *pStatic2 = new StaticObject(Rect(503, 250, 100, 50), pWorld,-20.0f * MATH_PI_180,                               //(-20.0f * MATH_PI_180),
												SpriteName::Sprite_Glass_block, ImageName::Image_Glass_Block);
		pStatic2;
		//pStatic1->angle = -20.0f * MATH_PI_180;

		fixObj *pMulFix = new fixObj(Rect(400.0f,500.0f, 150, 25),pWorld, 45.0f * MATH_PI_180,
								SpriteName::Sprite_Wood_MedPlank,ImageName::Image_Wood_Plank);

		fixObj *pMulFix2 = new fixObj(Rect(400.0f,500.0f, 25,150),pWorld,100.0f, 
								SpriteName::Sprite_Wood_MedPlank,ImageName::Image_Wood_Plank);
		fixObj * pMulFix3 = new fixObj(Rect(400.0f, 600.0f, 25,150),pWorld,90.0f * MATH_PI_180,
									SpriteName::Sprite_Wood_MedPlank,ImageName::Image_Wood_Plank);

		CircleObj *pMulFix4 = new CircleObj(Rect(450.0f, 600.0f, 45,45), pWorld, 0.0f, 
											SpriteName::Sprite_Red_1, ImageName::Image_RedIdle);


		//pMulFix
		b2BodyDef GlassBlockDef;
		GlassBlockDef.type = b2_dynamicBody;

		GlassBlockDef.position.Set( PixelToMeter(pMulFix->pDebugSprite1->posX), PixelToMeter(pMulFix->pDebugSprite1->posY) );
		GlassBlockDef.angle = pMulFix->angle;
		b2Body *pGlassBlockBody = pWorld->CreateBody(&GlassBlockDef);
		
		b2PolygonShape GlassBlockBox;

		GlassBlockBox.SetAsBox( PixelToMeter(pMulFix->pDebugSprite1->origWidth * 0.5f), 
			PixelToMeter(pMulFix->pDebugSprite1->origHeight * 0.5f));
	//	GlassBlockBox.SetAsBox(
	

		b2FixtureDef GlassBlockFixtureDef;

		GlassBlockFixtureDef.shape = &GlassBlockBox;
		GlassBlockFixtureDef.density = 10.50f;
		GlassBlockFixtureDef.friction = 0.3f;
		GlassBlockFixtureDef.restitution = 0.50f;
		GlassBlockFixtureDef.userData = pMulFix;

		//pGlassBlockBody->CreateFixture( &GlassBlockFixtureDef);

		pGlassBlockBody->SetUserData( pMulFix);
		pMulFix->pBody = pGlassBlockBody;

	// Glass block2

		b2PolygonShape GlassBlock2Box;

		GlassBlock2Box.SetAsBox( PixelToMeter(pMulFix2->pDebugSprite1->origWidth * 0.5f), PixelToMeter(pMulFix2->pDebugSprite1->origHeight * 0.5f) );
		
		b2FixtureDef GlassBlock2FixtureDef;
		GlassBlock2FixtureDef.shape = &GlassBlock2Box;
		GlassBlock2FixtureDef.density = 10.50f;
		GlassBlock2FixtureDef.friction = 0.3f;
		GlassBlock2FixtureDef.restitution = 0.50f;
		GlassBlock2FixtureDef.userData = pMulFix2;

	
		b2PolygonShape GlassBlock3Box;
		GlassBlock3Box.SetAsBox(PixelToMeter(pMulFix3->pDebugSprite1->origWidth * 0.5f), 
								PixelToMeter(pMulFix3->pDebugSprite1->origHeight * 0.5f),
								b2Vec2(PixelToMeter(90),PixelToMeter(30)),0
								);

		b2FixtureDef GlassBlock3FixtureDef;
		GlassBlock3FixtureDef.shape = &GlassBlock3Box;
		GlassBlock3FixtureDef.density = 10.50f;
		GlassBlock3FixtureDef.friction = 0.3f;
		GlassBlock3FixtureDef.restitution = 0.50f;
		GlassBlock3FixtureDef.userData = pMulFix3;

		b2CircleShape birdCircle;
		birdCircle.m_p.Set(PixelToMeter(-100),0);
		birdCircle.m_radius = PixelToMeter(pMulFix4->pDebugSprite1->origHeight * 0.5f);

		b2FixtureDef birdFixtureDef;
		birdFixtureDef.shape = &birdCircle;
		birdFixtureDef.density = 200.50f;
		birdFixtureDef.friction = 0.3f;
		birdFixtureDef.restitution = .5f;
		birdFixtureDef.userData = pMulFix4;

		pGlassBlockBody->CreateFixture( &birdFixtureDef);
		pGlassBlockBody->CreateFixture(	&GlassBlock3FixtureDef);
		pGlassBlockBody->CreateFixture( &GlassBlock2FixtureDef);
		pGlassBlockBody->CreateFixture( &GlassBlockFixtureDef);

}

void LevelLoader::loadTestBedYellowBird(b2World *pWorld)
{
	
	pWorld;
	//load up yellow bird image
	ImageMan::Add(ImageName::Image_Yellow, TextName::Texture_Unsorted, Rect(669, 880, 57, 53) );



}

void LevelLoader::loadBackgroundImages_And_Sprites()
{
	ImageMan::Add(ImageName::Image_Background_Clouds, TextName::Texture_Clouds, Rect(0,0,1280, 846) );
	ImageMan::Add(ImageName::Image_Background_TreeLayer, TextName::Texture_TreeLayer, Rect(0,0,1289,846) );
	ImageMan::Add(ImageName::Image_Background_Foreground, TextName::Texture_ForeGround, Rect(0,0,1280,846) );
	ImageMan::Add(ImageName::Image_Background_GrassBehindBirds, TextName::Texture_Grass_Behind_Birds, Rect(0,0, 1280, 846) );

	ImageMan::Add(ImageName::Image_Background_Clouds2, TextName::Texture_Clouds, Rect(0,0,1280, 846) );
	ImageMan::Add(ImageName::Image_Background_TreeLayer2, TextName::Texture_TreeLayer, Rect(0,0,1289,846) );
	ImageMan::Add(ImageName::Image_Background_Foreground2, TextName::Texture_ForeGround, Rect(0,0,1280,846) );
	ImageMan::Add(ImageName::Image_Background_GrassBehindBirds2, TextName::Texture_Grass_Behind_Birds, Rect(0,0, 1280, 846) );

	ImageMan::Add(ImageName::Image_Background_Clouds3, TextName::Texture_Clouds, Rect(0,0,1280, 846) );
	ImageMan::Add(ImageName::Image_Background_TreeLayer3, TextName::Texture_TreeLayer, Rect(0,0,1289,846) );
	ImageMan::Add(ImageName::Image_Background_Foreground3, TextName::Texture_ForeGround, Rect(0,0,1280,846) );
	ImageMan::Add(ImageName::Image_Background_GrassBehindBirds3, TextName::Texture_Grass_Behind_Birds, Rect(0,0, 1280, 846) );



	ImageMan::Add(ImageName::Image_SlingShot_Back, TextName::Texture_Unsorted, Rect(0.0f,0.0f,40.0f,200.0f) ) ;
	ImageMan::Add(ImageName::Image_SlingShot_Front, TextName::Texture_Unsorted, Rect(832.0f,0.0f,45.0f,125.0f) ) ;

	SpriteBatchManager::AddBatch(SpriteBatchName::SpriteBatch_Debug);
	SpriteBatchManager::AddBatch(SpriteBatchName::SpriteBatch_Middleground);
	SpriteBatchManager::AddBatch(SpriteBatchName::SpriteBatch_Foreground);
	SpriteBatchManager::AddBatch(SpriteBatchName::SpriteBatch_Background);

	// Background Sprites
	GameSprite *pA3 = 0;
	GameSprite *pSlingBack = 0;
	GameSprite *pA4 = 0;
	GameSprite *pA2 = 0;
	GameSprite *pA1 = 0;
	GameSprite *pA0 = 0;
	GameSprite *pSlingFront = 0;



pA3 = new GameSprite( SpriteBatchName::SpriteBatch_Background, SpriteName::Sprite_BackGround_GrassBehindBirds, ImageName::Image_Background_GrassBehindBirds, Rect(400.0f, 300.0f, WindowViewWidth + 400, WindowViewHeight) ) ;
pSlingBack = new GameSprite( SpriteBatchName::SpriteBatch_Background, SpriteName::Sprite_SlingShotBack, ImageName::Image_SlingShot_Back, Rect(100,180,20,100) );
pA4 = new GameSprite( SpriteBatchName::SpriteBatch_Background, SpriteName::Sprite_BackGround_Foreground, ImageName:: Image_Background_Foreground, Rect(400.0f, 300.0f, WindowViewWidth+600, WindowViewHeight) );
pA2 = new GameSprite( SpriteBatchName::SpriteBatch_Background, SpriteName::Sprite_BackGround_Foreground, ImageName:: Image_Background_Foreground, Rect(400.0f, 300.0f, WindowViewWidth+600, WindowViewHeight) );
pA1 = new GameSprite( SpriteBatchName::SpriteBatch_Background, SpriteName::Sprite_BackGround_TreeLayer, ImageName::Image_Background_TreeLayer, Rect (400.0f, 300.0f, WindowViewWidth+600 , WindowViewHeight) );
pA0 = new GameSprite( SpriteBatchName::SpriteBatch_Background, SpriteName::Sprite_BackGround_Clouds, ImageName::Image_Background_Clouds, Rect( 400.0f, 300.0f, WindowViewWidth+600 , WindowViewHeight) );	


pSlingFront = new GameSprite( SpriteBatchName::SpriteBatch_Foreground, SpriteName::Sprite_SlingShotFront, ImageName::Image_SlingShot_Front, Rect(82,203,22.5f,62.0f) );
pSlingFront->angle = pSlingFront->angle + .15f;
}

void LevelLoader::loadNonBackGroundImages()
{
	ImageMan::Add(ImageName::Image_RedIdle, TextName::Texture_Unsorted, Rect(903,798, 44 ,44));
	ImageMan::Add(ImageName::Image_RedDmg, TextName::Texture_Unsorted, Rect(854, 892, 44,44) );
	ImageMan::Add(ImageName::Image_RedLauncher, TextName::Texture_Unsorted, Rect(951,798,45,44) );
	ImageMan::Add(ImageName::Image_RedFlying,  TextName::Texture_Unsorted, Rect(957, 846, 45,44) ) ;

	ImageMan::Add(ImageName::Image_Yellow, TextName::Texture_Unsorted, Rect(669, 880, 57, 53) );
	ImageMan::Add(ImageName::Image_YellowDmg, TextName::Texture_Unsorted, Rect(793, 744, 58, 53) );
	ImageMan::Add(ImageName::Image_YellowFlying, TextName::Texture_Unsorted, Rect(669, 880, 57, 53) );
	ImageMan::Add(ImageName::Image_YellowContact, TextName::Texture_Unsorted, Rect(732, 745, 58, 53) );
	ImageMan::Add(ImageName::Image_YellowLauncher, TextName::Texture_Unsorted, Rect(588, 916, 68, 51) );
	ImageMan::Add(ImageName::Image_YellowAbility, TextName::Texture_Unsorted, Rect(864, 745, 58, 53) );

	ImageMan::Add(ImageName::Image_Blue,TextName::Texture_Unsorted, Rect(1, 379, 30,30) );
	ImageMan::Add(ImageName::Image_BlueFlying,TextName::Texture_Unsorted, Rect(1, 538, 29,28) );
	ImageMan::Add(ImageName::Image_BlueBlinking,TextName::Texture_Unsorted, Rect(1, 508, 29,28) );
	ImageMan::Add(ImageName::Image_BlueDmg,TextName::Texture_Unsorted, Rect(1, 379, 30,30) );

	ImageMan::Add(ImageName::Image_White, TextName::Texture_Unsorted, Rect(410, 353, 79, 93) );
	ImageMan::Add(ImageName::Image_White_Deflated, TextName::Texture_Unsorted, Rect(670, 752, 47, 65) );
	ImageMan::Add(ImageName::Image_WhiteDmg, TextName::Texture_Unsorted, Rect(410, 638, 77, 85) );

	ImageMan::Add(ImageName::Image_WhiteFlying, TextName::Texture_Unsorted, Rect(493, 352, 85, 93) );
	ImageMan::Add(ImageName::Image_WhiteBlinking, TextName::Texture_Unsorted, Rect(410, 448, 81, 93) );
	ImageMan::Add(ImageName::Image_WhiteChirping, TextName::Texture_Unsorted, Rect(409, 543, 80, 93) );
	ImageMan::Add(ImageName::Image_Egg, TextName::Texture_Unsorted, Rect(669,820,43, 57));

	ImageMan::Add(ImageName::Image_Green, TextName::Texture_Unsorted, Rect(933, 530, 97, 70) );
	ImageMan::Add(ImageName::Image_GreenAbility, TextName::Texture_Unsorted, Rect(831, 530, 99, 70) );
	ImageMan::Add(ImageName::Image_GreenBlinking, TextName::Texture_Unsorted, Rect(669, 606, 98, 70) );
	ImageMan::Add(ImageName::Image_GreenDmg, TextName::Texture_Unsorted, Rect(952, 605, 97, 70) );

	ImageMan::Add(ImageName::Image_Pig_Small, TextName::Texture_Unsorted, Rect(733,904, 47,46) );
	ImageMan::Add(ImageName::Image_Pig_Small2, TextName::Texture_Unsorted, Rect(733,903, 47,46) );
	ImageMan::Add(ImageName::Image_Pig_Small3, TextName::Texture_Unsorted, Rect(853,844, 48,46) );
	ImageMan::Add(ImageName::Image_Pig_Small4, TextName::Texture_Unsorted, Rect(986,743, 48,46) );

	ImageMan::Add(ImageName::Image_Wood_Pallet, TextName::Texture_Wood_Pallet, Rect(450,355,180,55) );

	ImageMan::Add(ImageName::Image_Wood_Plank, TextName::Texture_Wood_Plank, Rect(288, 168, 204, 22) ) ;
	ImageMan::Add(ImageName::Image_Wood_Plank2, TextName::Texture_Wood_Plank, Rect(288, 190, 204, 22) ) ;
	ImageMan::Add(ImageName::Image_Wood_Plank3, TextName::Texture_Wood_Plank, Rect(288, 212, 204, 22) ) ;
	ImageMan::Add(ImageName::Image_Wood_Plank4, TextName::Texture_Wood_Plank, Rect(288, 234, 204, 22) ) ;

	ImageMan::Add(ImageName::Image_Wood_MedPlank, TextName::Texture_Wood_Plank, Rect(288, 345, 85, 20) ) ;
	ImageMan::Add(ImageName::Image_Wood_MedPlank2, TextName::Texture_Wood_Plank, Rect(288, 367, 85, 20) ) ;
	ImageMan::Add(ImageName::Image_Wood_MedPlank3, TextName::Texture_Wood_Plank, Rect(372, 345, 85, 20) ) ;
	ImageMan::Add(ImageName::Image_Wood_MedPlank4, TextName::Texture_Wood_Plank, Rect(372, 367, 85, 20) ) ;

	ImageMan::Add(ImageName::Image_Wood_MiniPlank, TextName::Texture_Wood_Plank, Rect(458, 256, 40, 20) ) ;
	ImageMan::Add(ImageName::Image_Wood_MiniPlank2, TextName::Texture_Wood_Plank, Rect(458, 278, 40, 20) ) ;
	ImageMan::Add(ImageName::Image_Wood_MiniPlank3, TextName::Texture_Wood_Plank, Rect(458, 300, 40, 20) ) ;
	ImageMan::Add(ImageName::Image_Wood_MiniPlank4, TextName::Texture_Wood_Plank, Rect(458, 322, 40, 20) ) ;

	ImageMan::Add(ImageName::Image_Glass_MedPlank, TextName::Texture_Glass,  Rect(288, 345, 85, 20) ) ;
	ImageMan::Add(ImageName::Image_Glass_MedPlank2, TextName::Texture_Glass, Rect(288, 367, 85, 20) ) ;
	ImageMan::Add(ImageName::Image_Glass_MedPlank3, TextName::Texture_Glass, Rect(372, 345, 85, 20) ) ;
	ImageMan::Add(ImageName::Image_Glass_MedPlank4, TextName::Texture_Glass, Rect(372, 367, 85, 20) ) ;
	//bang
	ImageMan::Add(ImageName::Image_Bang, TextName::Texture_Unsorted,Rect(674, 354, 87,89 ) );

	ImageMan::Add(ImageName::Image_Pig_Med, TextName::Texture_Unsorted, Rect(929, 446, 78,76) );
	ImageMan::Add(ImageName::Image_Pig_Med2, TextName::Texture_Unsorted, Rect(410,892, 78,73) );
	ImageMan::Add(ImageName::Image_Pig_Med3, TextName::Texture_Unsorted, Rect(749,529, 78,73) );
	ImageMan::Add(ImageName::Image_Pig_Med4, TextName::Texture_Unsorted, Rect(588,687, 79,73) );

	ImageMan::Add(ImageName::Image_Wood_Blocks, TextName::Texture_Wood_Plank, Rect(247, 84, 83,41) ) ;
	ImageMan::Add(ImageName::Image_Wood_Blocks2, TextName::Texture_Wood_Plank, Rect(332, 83, 83,41) ) ;
	ImageMan::Add(ImageName::Image_Wood_Blocks3, TextName::Texture_Wood_Plank, Rect(417, 83, 83,41) ) ;
	ImageMan::Add(ImageName::Image_Wood_Blocks4, TextName::Texture_Wood_Plank, Rect(247, 126, 83,41) ) ;

	ImageMan::Add(ImageName::Image_Wood_bigSquares, TextName::Texture_Wood_Plank,Rect(2,338,40,40) );
	ImageMan::Add(ImageName::Image_Wood_bigSquares2, TextName::Texture_Wood_Plank,Rect(86,338,40,40) );
	ImageMan::Add(ImageName::Image_Wood_bigSquares3, TextName::Texture_Wood_Plank,Rect(332,127,40,40) );
	ImageMan::Add(ImageName::Image_Wood_bigSquares4, TextName::Texture_Wood_Plank,Rect(375,127,40,40) );

	ImageMan::Add(ImageName::Image_Stone_Blocks, TextName::Texture_Stones,Rect(247.0f, 84.0f, 83.0f,41.0f) ) ;
	ImageMan::Add(ImageName::Image_Stone_Blocks2, TextName::Texture_Stones, Rect(332.0f, 83.0f, 83.0f,41.0f) ) ;
	ImageMan::Add(ImageName::Image_Stone_Blocks3, TextName::Texture_Stones, Rect(417.0f, 83.0f, 83.0f,41.0f) ) ;
	ImageMan::Add(ImageName::Image_Stone_Blocks4, TextName::Texture_Stones, Rect(247.0f, 126.0f, 83.0f,41.0f) ) ;
	ImageMan::Add(ImageName::Image_CloudTrail_1, TextName::Texture_Unsorted, Rect(17.0f, 769.0f, 12.0f,11.0f) );


	ImageMan::Add(ImageName::Image_Glass_tinySquares, TextName::Texture_Glass,Rect(47,337,19,19) );
	ImageMan::Add(ImageName::Image_Glass_tinySquares2, TextName::Texture_Glass,Rect(47,359,19,19) );
	ImageMan::Add(ImageName::Image_Glass_tinySquares3, TextName::Texture_Glass,Rect(130,337,19,19) );
	ImageMan::Add(ImageName::Image_Glass_tinySquares4, TextName::Texture_Glass,Rect(130,359,19,19) );

	ImageMan::Add(ImageName::Image_Glass_Block, TextName::Texture_Glass,Rect(333,83,83,41) );
	ImageMan::Add(ImageName::Image_Glass_Block2, TextName::Texture_Glass,Rect(418,83,83,41) );
	ImageMan::Add(ImageName::Image_Glass_Block3, TextName::Texture_Glass,Rect(245,128,83,41) );
	ImageMan::Add(ImageName::Image_Glass_Block4, TextName::Texture_Glass,Rect(330,128,83,41) );

}


void LevelLoader::loadLevel_1(b2World *pWorld)
{
	GameObjectManager *GM = GameObjectManager::getInstance();

	/*IGameObject *pFirstBird = new BirdObject(100.0f, 215.0f,pWorld);
	GameObjectManager::getInstance()->addGameObjectToList(pFirstBird);
	BirdObjectManager::getInstance()->addBirdToList((BirdObject*) pFirstBird);*/
	
		//white bird
	 
	IGameObject * pSecondBird = new BirdObject(100.0f, 215.0f, pWorld); 
	GameObjectManager::getInstance()->addGameObjectToList(pSecondBird);
	BirdObjectManager::getInstance()->addBirdToList((BirdObject*)  pSecondBird);

	IGameObject *pFifthBird = new GreenBird(155.0f, 150.0f, pWorld);
	GameObjectManager::getInstance()->addGameObjectToList(pFifthBird);
	BirdObjectManager::getInstance()->addBirdToList((BirdObject*) pFifthBird);


	IGameObject *pFourthBird = new WhiteBird(300.0f, 150.0f, pWorld);
	GameObjectManager::getInstance()->addGameObjectToList(pFourthBird);
	BirdObjectManager::getInstance()->addBirdToList((BirdObject*) pFourthBird);

	//blue bird
	IGameObject *pFirstBird = new BlueBird(255.0f, 150.0f,pWorld);
	GameObjectManager::getInstance()->addGameObjectToList(pFirstBird);
	BirdObjectManager::getInstance()->addBirdToList((BirdObject*) pFirstBird);

	/*IGameObject * pSecondBird = new BirdObject(155.0f, 150.0f, pWorld);
	GameObjectManager::getInstance()->addGameObjectToList(pSecondBird);
	BirdObjectManager::getInstance()->addBirdToList((BirdObject*)  pSecondBird);*/

	//Add birds and Ground Object
	/*IGameObject *pFirstBird = new YellowBirdObject(100.0f, 215.0f,pWorld);
	GameObjectManager::getInstance()->addGameObjectToList(pFirstBird);
	BirdObjectManager::getInstance()->addBirdToList((BirdObject*) pFirstBird);*/

	
	/*IGameObject *pThirdBird = new BirdObject(200.0f, 150.0f, pWorld);
	GameObjectManager::getInstance()->addGameObjectToList(pThirdBird);
	BirdObjectManager::getInstance()->addBirdToList((BirdObject*) pThirdBird);*/

	IGameObject *pThirdBird = new YellowBirdObject(200.0f, 150.0f, pWorld);
	GameObjectManager::getInstance()->addGameObjectToList(pThirdBird);
	BirdObjectManager::getInstance()->addBirdToList((BirdObject*) pThirdBird);

	


	IGameObject *pGround = new GroundObj( Rect(400.0f, 0.0f, 1600, 250),pWorld);
	GameObjectManager::getInstance()->addGameObjectToList(pGround);

	//PLanks objects and whatever...

	
	IGameObject *pPalletObj = new PalletObj(Rect(700,140, 90,27.5),pWorld);
	IGameObject *pPalletObj2 = new PalletObj(Rect(610,140, 90, 27.5),pWorld);
	GameObjectManager::getInstance()->addGameObjectToList(pPalletObj);
	GameObjectManager::getInstance()->addGameObjectToList(pPalletObj2);
	
	IGameObject *pPlankObj = new WoodPlankObj(Rect(700,205, 102.5f,11.0f),pWorld,90.0f * MATH_PI_180, SpriteName::Sprite_Wood_Plank, ImageName::Image_Wood_Plank);
	IGameObject *pPlankObj2 = new WoodPlankObj(Rect(610,205, 102.5f,11.0f),pWorld,90.0f * MATH_PI_180, SpriteName::Sprite_Wood_Plank, ImageName::Image_Wood_Plank);
	IGameObject *pPlankObj3 = new WoodPlankObj(Rect(655,266, 102.5f,11.0f),pWorld,0.0f, SpriteName::Sprite_Wood_Plank, ImageName::Image_Wood_Plank);
	IGameObject *pPlankObj4 = new WoodPlankObj(Rect(675,322, 102.5f,11.0f),pWorld,90.0f * MATH_PI_180, SpriteName::Sprite_Wood_Plank, ImageName::Image_Wood_Plank);
	IGameObject *pPlankObj5 = new WoodPlankObj(Rect(635,322, 102.5f,11.0f),pWorld,90.0f * MATH_PI_180, SpriteName::Sprite_Wood_Plank, ImageName::Image_Wood_Plank);
	GM->addGameObjectToList(pPlankObj);
	GM->addGameObjectToList(pPlankObj2);
	GM->addGameObjectToList(pPlankObj3);
	GM->addGameObjectToList(pPlankObj4);
	GM->addGameObjectToList(pPlankObj5);
	
	IGameObject *pMedPlankObj = new WoodPlankObj(Rect(655,216, 42.5f,11.0f),pWorld,0.0f,SpriteName::Sprite_Wood_MedPlank,ImageName::Image_Wood_MedPlank);
	IGameObject *pMedPlankObj2 = new WoodPlankObj(Rect(655,379, 42.5f,11.0f),pWorld, 0.0f,SpriteName::Sprite_Wood_MedPlank,ImageName::Image_Wood_MedPlank);
	IGameObject *pMedPlankObj3 = new WoodPlankObj( Rect(655,162, 42.5f,11.0f),pWorld, 0.0f,SpriteName::Sprite_Wood_MedPlank,ImageName::Image_Wood_MedPlank);

	GM->addGameObjectToList(pMedPlankObj);
	GM->addGameObjectToList(pMedPlankObj2);
	GM->addGameObjectToList(pMedPlankObj3);


	IGameObject *pMiniPlankObj = new WoodPlankObj(Rect(575,165,20,10),pWorld, RIGHTANGLE,SpriteName::Sprite_Wood_MiniPlank,ImageName::Image_Wood_MiniPlank);
	IGameObject *pMiniPlankObj2 = new WoodPlankObj(Rect(735,165,20,10),pWorld, RIGHTANGLE,SpriteName::Sprite_Wood_MiniPlank,ImageName::Image_Wood_MiniPlank);
	IGameObject *pMiniPlankObj3 = new WoodPlankObj(Rect(655,278,20,10),pWorld, 0.0,SpriteName::Sprite_Wood_MiniPlank,ImageName::Image_Wood_MiniPlank);
	IGameObject *pMiniPlankObj4 = new WoodPlankObj(Rect(655,390.0f,20,10),pWorld,RIGHTANGLE,SpriteName::Sprite_Wood_MiniPlank,ImageName::Image_Wood_MiniPlank);


	GM->addGameObjectToList(pMiniPlankObj);
	GM->addGameObjectToList(pMiniPlankObj2);
	GM->addGameObjectToList(pMiniPlankObj3);
	GM->addGameObjectToList(pMiniPlankObj4);

	
	IGameObject *pMedGlassPlankObj = new GlassPlankObj(Rect(665.5f,188.0f, 42.5f,11.0f),pWorld,90.0f * MATH_PI_180, SpriteName::Sprite_Glass_MedPlank, ImageName::Image_Glass_MedPlank);
	IGameObject *pMedGlassPlankObj2 = new GlassPlankObj(Rect(642.5,188, 42.5f,11.0f),pWorld, 90.0f * MATH_PI_180, SpriteName::Sprite_Glass_MedPlank, ImageName::Image_Glass_MedPlank);
	GM->addGameObjectToList(pMedGlassPlankObj);
	GM->addGameObjectToList(pMedGlassPlankObj2);

#pragma endregion Planks

	IGameObject *pPigObj = new SmallPigObject(655.0f, 297.0f,pWorld);
	GM->addGameObjectToList(pPigObj);

	//successfully loaded 1st level??
}

void LevelLoader::loadLevel_2(b2World *pWorld)
{
	GameObjectManager *GM = GameObjectManager::getInstance();

	IGameObject *pFirstBird = new BirdObject(100.0f, 215.0f,pWorld);
	GM->addGameObjectToList(pFirstBird);
	BirdObjectManager::getInstance()->addBirdToList((BirdObject*) pFirstBird);

	IGameObject * pSecondBird = new BirdObject(155.0f, 150.0f, pWorld);
	GM->addGameObjectToList(pSecondBird);
	BirdObjectManager::getInstance()->addBirdToList((BirdObject*)  pSecondBird);

	IGameObject *pThirdBird = new BirdObject(200.0f, 150.0f, pWorld);
	GM->addGameObjectToList(pThirdBird);
	BirdObjectManager::getInstance()->addBirdToList((BirdObject*) pThirdBird);

	IGameObject *pGround = new GroundObj( Rect(400.0f, 0.0f, 1600, 250),pWorld);
	GM->addGameObjectToList(pGround);


	IGameObject *pStoneBlock2 = new StoneBlockObj(Rect(560.0f, 135.0f,41.5f, 20.5f),pWorld,0.0f,SpriteName::Sprite_Stone_Block,ImageName::Image_Stone_Blocks);
	IGameObject *pStoneBlock = new StoneBlockObj(Rect(600.0f, 135.0f,41.5f, 20.5f),pWorld,0.0f,SpriteName::Sprite_Stone_Block,ImageName::Image_Stone_Blocks);
	IGameObject *pStoneBlock3 = new StoneBlockObj(Rect(723.0f, 135.0f ,41.5f, 20.5f),pWorld,0.0f,SpriteName::Sprite_Stone_Block,ImageName::Image_Stone_Blocks);
	IGameObject *pStoneBlock4 = new StoneBlockObj(Rect(763.0f, 135.0f,41.5f, 20.5f),pWorld,0.0f,SpriteName::Sprite_Stone_Block,ImageName::Image_Stone_Blocks);
	IGameObject *pStoneBlock5 = new StoneBlockObj(Rect(575.0f, 210.0f,41.5f, 20.5f),pWorld,RIGHTANGLE,SpriteName::Sprite_Stone_Block,ImageName::Image_Stone_Blocks);
	IGameObject *pStoneBlock6 = new StoneBlockObj(Rect(743, 210.0f,41.5f, 20.5f),pWorld,RIGHTANGLE,SpriteName::Sprite_Stone_Block,ImageName::Image_Stone_Blocks);

	GM->addGameObjectToList(pStoneBlock);
	GM->addGameObjectToList(pStoneBlock2);
	GM->addGameObjectToList(pStoneBlock3);
	GM->addGameObjectToList(pStoneBlock4);
	GM->addGameObjectToList(pStoneBlock5);
	GM->addGameObjectToList(pStoneBlock6);


	IGameObject *pWoodBlock = new WoodBlockObj(Rect(570.375f,158.0f,41.5, 20.5f), pWorld,0.0f, SpriteName::Sprite_Wood_Block,ImageName::Image_Wood_Blocks);
	IGameObject *pWoodBlock2 = new WoodBlockObj(Rect(723.375f,158.0f,41.5, 20.5f), pWorld,0.0f, SpriteName::Sprite_Wood_Block,ImageName::Image_Wood_Blocks);
	IGameObject *pWoodBlock3 = new WoodBlockObj(Rect(585.375f,180.0f,41.5, 20.5f), pWorld,0.0f, SpriteName::Sprite_Wood_Block,ImageName::Image_Wood_Blocks);
	IGameObject *pWoodBlock4 = new WoodBlockObj(Rect(755.375f,180.0f,41.5, 20.5f), pWorld,0.0f, SpriteName::Sprite_Wood_Block,ImageName::Image_Wood_Blocks);
	IGameObject *pWoodBlock5 = new WoodBlockObj(Rect(535,255.0f,41.5f, 20.5f), pWorld,RIGHTANGLE, SpriteName::Sprite_Wood_Block,ImageName::Image_Wood_Blocks);
	IGameObject *pWoodBlock6 = new WoodBlockObj(Rect(615.0f,255.0f,41.5f, 20.5f), pWorld,RIGHTANGLE, SpriteName::Sprite_Wood_Block,ImageName::Image_Wood_Blocks);

	GM->addGameObjectToList(pWoodBlock);
	GM->addGameObjectToList(pWoodBlock2);
	GM->addGameObjectToList(pWoodBlock3);
	GM->addGameObjectToList(pWoodBlock4);
	GM->addGameObjectToList(pWoodBlock5);
	GM->addGameObjectToList(pWoodBlock6);

	IGameObject *pWoodSquare =  new WoodBlockObj(Rect(603.0f,158.0f,20.5f,20.5f), pWorld, 0.0f, SpriteName::Sprite_Wood_BigSquare, ImageName::Image_Wood_bigSquares);
	IGameObject *pWoodSquare2 = new WoodBlockObj(Rect(763.0f,158.0f,20.5f,20.5f), pWorld, 0.0f, SpriteName::Sprite_Wood_BigSquare, ImageName::Image_Wood_bigSquares);
	IGameObject *pWoodSquare3 = new WoodBlockObj(Rect(555.0f,175.5f,20.5f,20.5f), pWorld, 0.0f, SpriteName::Sprite_Wood_BigSquare, ImageName::Image_Wood_bigSquares);
	IGameObject *pWoodSquare4 = new WoodBlockObj(Rect(723.0f,175.5f,20.5f,20.5f), pWorld, 0.0f, SpriteName::Sprite_Wood_BigSquare, ImageName::Image_Wood_bigSquares);

	GM->addGameObjectToList(pWoodSquare);
	GM->addGameObjectToList(pWoodSquare2);
	GM->addGameObjectToList(pWoodSquare3);
	GM->addGameObjectToList(pWoodSquare4);

	IGameObject *pWoodPlankL2 = new WoodPlankObj(Rect(661.625f,152.75f, 102.5f, 11.0f), pWorld, 0.0f,SpriteName::Sprite_Wood_Plank, ImageName::Image_Wood_Plank) ;
	IGameObject *pWoodPlankL22 = new WoodPlankObj(Rect(575.0f,235.0f, 102.5f, 11.0f), pWorld, 0.0f,SpriteName::Sprite_Wood_Plank, ImageName::Image_Wood_Plank) ;
	IGameObject *pWoodPlankL23 = new WoodPlankObj(Rect(743.0f,235.0f, 102.5f, 11.0f), pWorld, 0.0f,SpriteName::Sprite_Wood_Plank, ImageName::Image_Wood_Plank) ;
	IGameObject *pWoodPlankL24 = new WoodPlankObj(Rect(575.0f,285.0f, 102.5f, 11.0f), pWorld, 0.0f,SpriteName::Sprite_Wood_Plank, ImageName::Image_Wood_Plank) ;
	IGameObject *pWoodPlankL25 = new WoodPlankObj(Rect(743.0f,285.0f, 102.5f, 11.0f), pWorld, 0.0f,SpriteName::Sprite_Wood_Plank, ImageName::Image_Wood_Plank) ;

	
	IGameObject *pWoodMedPlankL2 = new WoodPlankObj(Rect(550.0f,210.0f, 42.5, 11.0f), pWorld, RIGHTANGLE,SpriteName::Sprite_Wood_MedPlank, ImageName::Image_Wood_MedPlank) ;
	IGameObject *pWoodMedPlankL22 = new WoodPlankObj(Rect(600,210.0f, 42.5f, 11.0f), pWorld, RIGHTANGLE,SpriteName::Sprite_Wood_MedPlank, ImageName::Image_Wood_MedPlank) ;
	IGameObject *pWoodMedPlankL23 = new WoodPlankObj(Rect(718.0f,210.0f, 42.5, 11.0f), pWorld, RIGHTANGLE,SpriteName::Sprite_Wood_MedPlank, ImageName::Image_Wood_MedPlank) ;
	IGameObject *pWoodMedPlankL24 = new WoodPlankObj(Rect(768.0f,210.0f, 42.5f, 11.0f), pWorld, RIGHTANGLE,SpriteName::Sprite_Wood_MedPlank, ImageName::Image_Wood_MedPlank) ;

	IGameObject *pWoodMedPlankL25 = new WoodPlankObj(Rect(712.0f,255.0f, 42.5f, 11.0f), pWorld, RIGHTANGLE,SpriteName::Sprite_Wood_MedPlank, ImageName::Image_Wood_MedPlank) ;
	IGameObject *pWoodMedPlankL26 = new WoodPlankObj(Rect(773.0f,255.0f, 42.5f, 11.0f), pWorld, RIGHTANGLE,SpriteName::Sprite_Wood_MedPlank, ImageName::Image_Wood_MedPlank) ;
	IGameObject *pWoodMedPlankL27 = new WoodPlankObj(Rect(698.0f,255.0f, 42.5f, 11.0f), pWorld, RIGHTANGLE,SpriteName::Sprite_Wood_MedPlank, ImageName::Image_Wood_MedPlank) ;
	IGameObject *pWoodMedPlankL28 = new WoodPlankObj(Rect(785.0f,255.0f, 42.5f, 11.0f), pWorld, RIGHTANGLE,SpriteName::Sprite_Wood_MedPlank, ImageName::Image_Wood_MedPlank) ;



	GM->addGameObjectToList(pWoodPlankL2);
	GM->addGameObjectToList(pWoodPlankL22);
	GM->addGameObjectToList(pWoodPlankL23);
	GM->addGameObjectToList(pWoodPlankL24);
	GM->addGameObjectToList(pWoodPlankL25);

	GM->addGameObjectToList(pWoodMedPlankL2);
	GM->addGameObjectToList(pWoodMedPlankL22);
	GM->addGameObjectToList(pWoodMedPlankL23);
	GM->addGameObjectToList(pWoodMedPlankL24);
	GM->addGameObjectToList(pWoodMedPlankL25);
	GM->addGameObjectToList(pWoodMedPlankL26);
	GM->addGameObjectToList(pWoodMedPlankL27);
	GM->addGameObjectToList(pWoodMedPlankL28);


	IGameObject *pGlassTinySquare = new GlassBlockObj(Rect(555.0f,245,10.0f,10.0f), pWorld,0.0,SpriteName::Sprite_Glass_TinySquare, ImageName::Image_Glass_tinySquares);
	IGameObject *pGlassTinySquare2 = new GlassBlockObj(Rect(595,245,10.0f,10.0f), pWorld,0.0,SpriteName::Sprite_Glass_TinySquare, ImageName::Image_Glass_tinySquares);
	IGameObject *pGlassTinySquare3 = new GlassBlockObj(Rect(723.0f,245,10.0f,10.0f), pWorld,0.0,SpriteName::Sprite_Glass_TinySquare, ImageName::Image_Glass_tinySquares);
	IGameObject *pGlassTinySquare4 = new GlassBlockObj(Rect(768.0f,245,10.0f,10.0f), pWorld,0.0,SpriteName::Sprite_Glass_TinySquare, ImageName::Image_Glass_tinySquares);


	IGameObject *pGlassBlock = new GlassBlockObj(Rect(575.0f,303.0f, 41.5, 20.5f), pWorld, 0.0, SpriteName::Sprite_Glass_block, ImageName::Image_Glass_Block);
	IGameObject *pGlassBlock2 = new GlassBlockObj(Rect(743.0f,303.0f, 41.5, 20.5f), pWorld, 0.0, SpriteName::Sprite_Glass_block, ImageName::Image_Glass_Block);

	IGameObject *pGlassMedPlankL2 = new GlassPlankObj(Rect(575.0f, 335.0f, 42.5f, 11.0f), pWorld, RIGHTANGLE, SpriteName::Sprite_Glass_MedPlank, ImageName::Image_Glass_MedPlank);
	IGameObject *pGlassMedPlankL22 = new GlassPlankObj(Rect(743.0f, 335.0f, 42.5f, 11.0f), pWorld, RIGHTANGLE, SpriteName::Sprite_Glass_MedPlank, ImageName::Image_Glass_MedPlank);



	GM->addGameObjectToList(pGlassTinySquare);
	GM->addGameObjectToList(pGlassTinySquare2);
	GM->addGameObjectToList(pGlassTinySquare3);
	GM->addGameObjectToList(pGlassTinySquare4);

	GM->addGameObjectToList(pGlassBlock);
	GM->addGameObjectToList(pGlassBlock2);
	GM->addGameObjectToList(pGlassMedPlankL2);
	GM->addGameObjectToList(pGlassMedPlankL22);

	IGameObject *pSmallPigL2 = new SmallPigObject(575.0f,255.0f, pWorld);
	IGameObject *pSmallPigL22 = new SmallPigObject(743.0f,255.0f, pWorld);

	IGameObject *pMediumPig = new MediumPigObj(661.625f, 180.0f,pWorld);
	GM->addGameObjectToList(pMediumPig);
	GM->addGameObjectToList(pSmallPigL2);
	GM->addGameObjectToList(pSmallPigL22);
	

}

void LevelLoader::SimulateSetup()
{/*
	 for (int i = 0; i < 120; i++)
		{
            PhysicsMan::Update(0.016f);
		}

        GameObject* obj = 0;
        for (std::list<GameObject*>::iterator it = list.begin(); it != list.end(); it++)
		{
            obj = *it;
            obj->currHealth = obj->maxHealth;
		}*/
}

void LevelLoader::LoadTexturesSpritesImages()
{
	loadTextures();
	loadBackgroundImages_And_Sprites();
	loadNonBackGroundImages();
}


