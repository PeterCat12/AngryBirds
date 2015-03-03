#ifndef ENUM_NAME_H
#define ENUM_NAME_H

struct EnumName
{
	enum Name
	{
		Stubb // needed for overloading
	};

	bool operator == (EnumName tmp )
	{
		return ( this->value == tmp.value);
	}

	int value;
};

struct SpriteBatchName: public EnumName
{
	SpriteBatchName( SpriteBatchName::Name n )
	{
		this->value = n;
	}

	enum Name
	{
		/*SpriteBatch_Stitch = 10000,
		SpriteBatch_Invaders,
		
		SpriteBatch_Birds,
		SpriteBatch_Pigs,
		SpriteBatch_Blocks,*/

		//Will be using these four sprite batches

		SpriteBatch_Debug,

		//backgrounds sprites
		SpriteBatch_Background,

		SpriteBatch_Foreground,

		SpriteBatch_Middleground,

		Not_Initialized
	};
};

struct SpriteName: public EnumName
{
	SpriteName( SpriteName::Name n )
	{
		this->value = n;
	}

	enum Name
	{
		/*Sprite_Stitch_0 = 20000,
		Sprite_Stitch_1,
		Sprite_Alien_Green,
		Sprite_Alien_Blue,
		Sprite_Alien_Red_0,
		Sprite_Alien_Red_1,*/
		Sprite_Red_1,
		Sprite_Yellow1,
		Sprite_Blue1,
		Sprite_White1,
		Sprite_Egg,
		Sprite_Green1,

		Sprite_Pig_Normal,
		Sprite_Bang,

		Sprite_CloudTrail_1,
		/*Sprite_Pig_King,

		Sprite_GlassBlock_Triangle,
		Sprite_WoodBlock_Circle,*/

		//Background Sprite Names
		Sprite_BackGround_Clouds,
		Sprite_BackGround_Foreground,
		Sprite_BackGround_TreeLayer,
		Sprite_BackGround_GrassBehindBirds,
		Sprite_SlingShotBack,
		Sprite_SlingShotFront,


		Sprite_PATEST1,

		//Wood Block Sprite Names
		Sprite_Wood_Pallet,
		Sprite_Wood_Plank,
		Sprite_Wood_MedPlank,
		Sprite_Wood_MiniPlank,

		Sprite_Wood_Block,
		Sprite_Wood_BigSquare,


		Sprite_Glass_TinySquare,
		Sprite_Glass_block,

		//glass
		Sprite_Glass_MedPlank,
		Sprite_Stone_Block,

		Sprite_Box,
		Sprite_Circle,
		Sprite_Poly,


		Not_Initialized
	};
};

struct ImageName: public EnumName
{
	ImageName( ImageName::Name n )
	{
		this->value = n;
	}

	enum Name
	{
		Image_Alien_Small = 30000,
		Image_Alien_Medium,
		Image_Alien_Large,
		Image_Stitch,

		Image_RedDmg,
		Image_RedIdle,
		Image_RedLauncher,
		Image_RedFlying,

		Image_Yellow,
		Image_YellowDmg,
		Image_YellowAbility,
		Image_YellowLauncher,
		Image_YellowContact,
		Image_YellowFlying,

		Image_Blue,
		Image_BlueDmg,
		Image_BlueFlying,
		Image_BlueBlinking,

		Image_White,
		Image_WhiteFlying,
		Image_WhiteBlinking,
		Image_WhiteAbility,
		Image_WhiteChirping,
		Image_WhiteDmg,

		Image_Green,
		Image_GreenAbility,
		Image_GreenBlinking,
		Image_GreenDmg,

		Image_Egg,
		Image_White_Deflated,
	
		Image_Pig_Small,
		Image_Pig_Small2,
		Image_Pig_Small3,
		Image_Pig_Small4,

		Image_Pig_Med,
		Image_Pig_Med2,
		Image_Pig_Med3,
		Image_Pig_Med4,





		Image_Pig_King,
		Image_Glass_Triangle,
		Image_Wood_Circle,

		//Block Images
		Image_Wood_Pallet,
		Image_Wood_Plank,
		Image_Wood_Plank2,
		Image_Wood_Plank3,
		Image_Wood_Plank4,

		Image_PATEST,


		Image_Wood_MedPlank,
		Image_Wood_MedPlank2,
		Image_Wood_MedPlank3,
		Image_Wood_MedPlank4,


		Image_Wood_MiniPlank,
		Image_Wood_MiniPlank2,
		Image_Wood_MiniPlank3,
		Image_Wood_MiniPlank4,

		Image_Wood_Blocks,
		Image_Wood_Blocks2,
		Image_Wood_Blocks3,
		Image_Wood_Blocks4,
		Image_Wood_tinySquares,
		Image_Wood_bigSquares,
		Image_Wood_bigSquares2,
		Image_Wood_bigSquares3,
		Image_Wood_bigSquares4,



		Image_Glass_Plank,
		Image_Glass_Plank2,
		Image_Glass_Plank3,
		Image_Glass_Plank4,

		Image_Glass_MedPlank,
		Image_Glass_MedPlank2,
		Image_Glass_MedPlank3,
		Image_Glass_MedPlank4,

		Image_Glass_MiniPlank,
		Image_Glass_MiniPlank2,
		Image_Glass_MiniPlank3,
		Image_Glass_MiniPlank4,

		Image_Glass_Block,
		Image_Glass_Block2,
		Image_Glass_Block3,
		Image_Glass_Block4,

		Image_Glass_tinySquares,
		Image_Glass_tinySquares2,
		Image_Glass_tinySquares3,
		Image_Glass_tinySquares4,

		Image_Stone_Blocks,
		Image_Stone_Blocks2,
		Image_Stone_Blocks3,
		Image_Stone_Blocks4,

		Image_CloudTrail_1,

		Image_Bang,

		//Background images
		Image_Background_Clouds,
		Image_Background_Foreground,
		Image_Background_TreeLayer,
		Image_Background_GrassBehindBirds,

		Image_Background_Clouds2,
		Image_Background_Foreground2,
		Image_Background_TreeLayer2,
		Image_Background_GrassBehindBirds2,

		Image_Background_Clouds3,
		Image_Background_Foreground3,
		Image_Background_TreeLayer3,
		Image_Background_GrassBehindBirds3,

		Image_SlingShot_Back,
		Image_SlingShot_Front,

		Not_Initialized,
	};
};

struct TextName: public EnumName
{
	TextName( TextName::Name n )
	{
		this->value = n;
	}

	enum Name
	{
		Texture_SpaceInvaders = 40000,
		Texture_Stitch,
		Texture_Stones,
		Texture_Red,
		Texture_Pig_Small,
		Texture_Pig_King,
		Texture_Glass_Triangle,
		Texture_Wood_Circle,
		Texture_Unsorted,
		Texture_Glass,

		//block tectures
		Texture_Wood_Pallet,
		Texture_Wood_Plank,
		Texture_Wood_MiniPlank,

		//Background textures
		Texture_Clouds,
		Texture_ForeGround,
		Texture_TreeLayer,
		Texture_Grass_Behind_Birds, //goes int background? 

		Not_Initialized
	};
};

struct BodyTypeName: public EnumName
{
	BodyTypeName ( BodyTypeName::Name n)
	{
		this->value = n;
	}
	enum Name
	{
		BodyTypeStatic,
		BodyTypeDynamic,

		Not_Initialized
	};

};


struct GameObjectName: public EnumName
{
	GameObjectName( GameObjectName::Name n )
	{
		this->value = n;
	}
	enum Name
	{
		GameObject_Ground,
		GameObject_Block = 50000,
		GameObject_Block2,
		GameObject_RedBird,
		GameObject_YellowBird,
		GameObject_BlueBird,
		GameObject_BlueBirdSpawn,
		GameObject_GreenBird,
		GameObject_WhiteBird,
		GameObject_Egg,


		GameObject_Small_Pig,
		GameObject_Med_Pig,

		GameObject_MultiFix,
		GameObject_StaticBody,

		GameObject_Stone_Block,

		//woodBlock NAmes
		GameObject_Wood_Pallet,
		GameObject_Wood_Plank,
		GameObject_Wood_MedPlank,
		GameObject_Wood_MiniPlank,

		GameObject_Wood_Block,
		GameObject_Wood_Square,


		GameObject_Glass_Plank,
		GameObject_Glass_MedPlank,
		GameObject_Glass_MiniPlank,

		GameObject_Glass_Block,
		GameObject_Glass_TinySquare,

		Not_Initialized
	};
};





#endif