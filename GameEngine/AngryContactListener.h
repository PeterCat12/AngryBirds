#ifndef ANGRY_CONTACT_LISTENER_H
#define ANGRY_CONTACT_LISTENER_H

#include "Box2D.h"
#include "PixelToMeters.h"

#include "AzulStopWatch.h"

#include "AngryContactListener.h"
#include "WoodPlankObj.h"

#include "Object.h"
#include "StaticObj.h"
#include "CircleDynamic.h"

extern AzulStopWatch stopWatch;
extern AzulStopWatch totalWatch;
extern bool displayData;

class AngryContactListener : public b2ContactListener
{

public:

	AngryContactListener()
	{
	}

	void BeginContact(b2Contact* pContact)
	{ /* handle begin event */ 
		pContact;
	}

	void EndContact(b2Contact* )
	{ /* handle end event */ 
	}

	void PreSolve(b2Contact* , const b2Manifold* )
	{ /* handle pre-solve event */
	}

	void PostSolve(b2Contact*  pContact, const b2ContactImpulse* impulse )
	{ /* handle post-solve event */

		b2Fixture *fixtureA = pContact->GetFixtureA();
		b2Fixture *fixtureB = pContact->GetFixtureB();
		
		IGameObject *gObjA = (IGameObject *)fixtureA->GetUserData();
		IGameObject *gObjB = (IGameObject *)fixtureB->GetUserData();


		gObjA;
		gObjB;

		int numPoints = pContact->GetManifold()->pointCount;
		b2WorldManifold worldManifold;
		pContact->GetWorldManifold( &worldManifold );
		numPoints;

		float impulseFloat = 0.0f;
		int numImpulse = impulse->count;
	   // assert( numImpulse == numPoints);
		for( int i = 0; i< numImpulse; i++ )
		{
		 if (impulse->normalImpulses[i] > impulseFloat)
			{
                impulseFloat = impulse->normalImpulses[i];
			}

	//	 printf("%d contact: %f %f  t:%f %f\n", i, (float)MeterToPixel(worldManifold.points[i].x), (float)MeterToPixel( worldManifold.points[i].y), stopWatch.timeInSeconds(), totalWatch.timeInSeconds());

			//if %norm is below a  certain num
			if(impulse->normalImpulses[i] > 0.5f)
			{
				//calculate dmg
					IGameObject *gObjA = (IGameObject *)pContact->GetFixtureA()->GetBody()->GetUserData();
					IGameObject *gObjB = (IGameObject *)pContact->GetFixtureB()->GetBody()->GetUserData();

						float dmg =  (impulse->normalImpulses[i]); 
							gObjA->updateHealth(dmg);
							gObjB->updateHealth(dmg);
							displayData = true;
						
						/*	if(dmg >100){
								GameSprite *pBang2 = new GameSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_Bang, ImageName::Image_Bang, Rect( 0, 0, 50,50 ) );
								pBang2->posX = MeterToPixel(worldManifold.points[i].x);
								pBang2->posY = MeterToPixel(worldManifold.points[i].y);
								pBang2->enable();
							}*/
			}
			/*printf("%d norm: %f tan: %f ",i, impulse->normalImpulses[i], impulse->tangentImpulses[i]);
			printf("  contact: %f %f  t:%f\n",(float)MeterToPixel(worldManifold.points[i].x), (float)MeterToPixel( worldManifold.points[i].y), totalWatch.timeInSeconds());
			printf("\n dmg done Norm: %f tan: %f", impulse->normalImpulses[i]*10.0f,impulse->tangentImpulses[i]);*/
		}

		gObjA->updateHealth(impulseFloat);
		gObjB->updateHealth(impulseFloat);
	}
};

#endif