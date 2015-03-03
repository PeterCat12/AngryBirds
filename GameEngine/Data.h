#ifndef DATA_H
#define DATA_H

#include "TextMan.h"

void LoadTextres()
{
	TextMan::Load(TextType::Text2D, TextName::Texture_Clouds, "CloudLayer.tga");
	TextMan::Load(TextType::Text2D,TextName::Texture_TreeLayer,"TreeLayer.tga");
	TextMan::Load(TextType::Text2D, TextName::Texture_ForeGround,"foreground.tga");
	TextMan::Load(TextType::Text2D,TextName::Texture_Grass_Behind_Birds,"GrassBehindBirds.tga");
	TextMan::Load(TextType::Text2D,TextName::Texture_Wood_Pallet, "MiscSprites.tga");
	TextMan::Load(TextType::Text2D,TextName::Texture_Wood_Plank, "woodBlocks.tga");
	TextMan::Load(TextType::Text2D, TextName::Texture_Unsorted, "unsorted.tga");
	TextMan::Load(TextType::Text2D, TextName::Texture_Glass, "glassBlocks.tga");
	TextMan::Load(TextType::Text2D,TextName::Texture_Stones, "stoneBlocks.tga");
}

void LoadImages()
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




#endif // !DATA_H
