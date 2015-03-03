#ifndef CLOUDTRAIL_OBJECT_H
#define CLOUDTRAIL_OBJECT_H


#include "GameSprite.h"
#include "SBNode.h"
//#include "GameObject.h"

class CloudTrail_Obj
{
public:

	CloudTrail_Obj(float centerX, float centerY);
	~CloudTrail_Obj();
	static void CreateCloudTrail();

	GameSprite *pGameSprite;

};
#endif