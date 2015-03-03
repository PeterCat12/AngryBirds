
#include "PhysicsManager.h"

#include "TextMan.h"
#include "BoxModel.h"
#include "BoxSprite.h"
#include "CircleModel.h"
#include "CircleSprite.h"

#include "Box2D.h"
#include "GameObject.h"
#include "BirdObject.h"
#include "SmallPigObject.h"




#include "BirdObjectManager.h"
#include "GameObjectManager.h"
#include "MultiFixtureObj.h"
#include "PhysicsManager.h"
#include "StaticObj.h"
#include "CircleDynamic.h"
#include "Audio.h"
#include "RandomCommands.h"
#include "PigManager.h"

//Static vars
bool PhysicsMan::instanceFlag;

PhysicsMan *PhysicsMan::single;

PhysicsMan::PhysicsMan()
{
}

PhysicsMan* PhysicsMan::Instance()
{
	if(! instanceFlag)
	{
		single = new PhysicsMan();
		instanceFlag = true;
		return single;
	}
	else
	{
		return single;
	}
}


void PhysicsMan::UpdatePhysics(b2World* world)
{
	PhysicsMan::Instance()->privUpdatePhysics(world);
}

void PhysicsMan::privUpdatePhysics(b2World* pWorld)
{
	b2Body *pBody = pWorld->GetBodyList();

	while( pBody != 0 )
	{
		IGameObject *pGameObj = (IGameObject *)pBody->GetUserData();

		if( pGameObj != 0 )
		{	
			pGameObj->update( pBody->GetPosition(), pBody->GetAngle());
		}
		else
		{
			assert( pGameObj );
		}
		pBody = pBody->GetNext();
	}
}

void PhysicsMan::Delete()
{
	delete PhysicsMan::Instance();
}

PhysicsMan::~PhysicsMan()
{

}
