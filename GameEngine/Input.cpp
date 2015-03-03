#include <string>
#include "AzulCore.h"
#include "Input.h"
#include "PixelToMeters.h"
#include "ScreenLine.h"
#include "BirdObject.h" 
#include "YellowBirdObject.h"
#include "BlueBird.h"
#include "WhiteBird.h"
#include "Camera.h"
#include "CameraMan.h"

bool displayData = false;
extern bool reset;

enum PositionState
{
	INSIDE,
	OUTSIDE,
	UNKNOWN
};

enum MouseState
{
	RIGHT = 0x1,
	LEFT  = 0x2,
	NONE = 0
};

enum BirdState
{
	NORMAL,
	MOVING_LEFT_BUTTON,
	MOVING_RIGHT_BUTTON,
	MOVING
};

float originalx = ORIGINAL_X;
float originaly = ORIGINAL_Y;
float theStringSpace = STRING_SPACE;

static	BirdState bState = NORMAL;
static MouseState mState = NONE;
static PositionState pState = UNKNOWN;

//bool HitTest(float x, float y)
bool HitTest(Vect &vDiff, float ratio,float x, float y)
{
	vDiff;
	ratio;
	Vect r(x,y,0);
	Vect center(originalx,originaly,0);
	Vect result =  (r - center);
	return result.mag() < theStringSpace;
}

void getMousePos( GLFWwindow*window, Vect &x_y)
{
	double x;
	double y;
	glfwGetCursorPos(window, &x,&y);
	x_y.vx = (float)x;
	x_y.vy = (float)y;
	x_y.vz = 0.0f;
	Camera *pCamera = Camera::Instance();
	pCamera->CorrectForOrigin(x_y.vx, x_y.vy);
}


void MouseTest( GLFWwindow* window, IGameObject *pBird, ScreenLine* line1, ScreenLine* line2)
{
	// Quick and dirty test, if these work the rest do.
	// --> try move the mouse inside the window, click right, click left

	double xpos;
	double ypos;
	// get mouse position
	Vect MousePos;
	getMousePos(window, MousePos);
	glfwGetCursorPos( window, &xpos, &ypos);
	// correct for origin
	double t = ypos / 600.0;
	ypos = 600.0 + t * (-600.0);
	// correct bird for the local screen
	Camera *pCam = Camera::Instance();
	pCam;

	BirdObject *pBirdObject = (BirdObject*) pBird;
	//CameraManager::getInstance()->FollowBird(pBirdObject);
	Matrix viewMatrix = pCam->getViewMatrix();
	Matrix projMatrix = pCam->getProjMatrix();
	Matrix worldMatrix = pBirdObject->pGameSprite->getWorld();
		
	// world * View * projection
	Vect vout = Vect(0.0f,0.0f,0.0f) * worldMatrix * viewMatrix * projMatrix;

	// correction for zoom
	float ratio = vout[w];
		
	// make homogeneous
	vout[x] = vout[x]/vout[w];
	vout[y] = vout[y]/vout[w];
		
	// at this point we have a normalized device coordinates
	// process this through the viewport transformation
	float x2 = (vout[x]+1.0f)*(400.0f);
	float y2 = (vout[y]+1.0f)*(300.0f);
	//float left = pBird->getPosX() - pBird->getGameSprite()->origWidth * 0.5f;
	//float right = pBird->getPosX() + pBird->getGameSprite()->origWidth * 0.5f;
	//

	//float top = pBird->getPosY() + pBird->getGameSprite()->origHeight * 0.5f;
	//float bottom = pBird->getPosY() - pBird->getGameSprite()->origHeight * 0.5f;
	//bottom;
	//top;
	//left;
	//right;

	//Vect vMouse(xpos, ypos,0.0f);
	Vect vLocalScreen(x2,y2,0.0f);
		//if( xpos > left &&
		//	xpos < right &&
		//	ypos > bottom &&
		//	ypos < top )
		//{
		//	pState = INSIDE;
		//}
		//else
		//{
		//	pState = OUTSIDE;
		//}
		// Inside?

	Vect vDiff = MousePos - vLocalScreen;
				if ( vDiff.mag() < (10.0f / ratio) )
			{
				pState = INSIDE;
			}
			else
			{
				pState = OUTSIDE;
			}

	// Mouse - button press?
		mState = NONE;

		if( glfwGetMouseButton (window, GLFW_MOUSE_BUTTON_RIGHT ) == GLFW_PRESS)
		{
			mState = RIGHT;
		}
	
		if( glfwGetMouseButton (window, GLFW_MOUSE_BUTTON_LEFT ) == GLFW_PRESS)
		{
			mState = LEFT;
		}


	// Enter MOVING state
		if( mState == LEFT && pState == INSIDE)
		{
			bState = MOVING_LEFT_BUTTON;
			pBird->getBody()->SetActive(false);
		}

		// small sublty here, once moving, left dictates mode
		if( bState == MOVING_LEFT_BUTTON)
		{
			if( mState == LEFT )
			{
				if(HitTest(vDiff,ratio,(float) xpos,(float) ypos))
				{
					b2Vec2 newPos(PixelToMeter(pBirdObject->getPosX() + vDiff[x] * ratio), 
						PixelToMeter(pBirdObject->getPosY() + vDiff[y] * ratio )); 
					pBird->getBody()->SetActive(true);
					if(pBirdObject->select == false)
						pBirdObject->playSelect();
					pBird->getBody()->SetTransform( newPos, 0.0f);
			
					line1->posA.x = (float)xpos-10; //10, 3
					line1->posA.y = (float)ypos-3;
					line2->posA.x = (float)xpos-10;
					line2->posA.y = (float)ypos-3;
				}
				pBird->getBody()->SetActive(false);
			}
			else
			{
					bState = NORMAL;
					Vect r (pBird->getPosX(), pBird->getPosY(),0);
					Vect center(originalx,originaly,0);
					Vect result =  (center - r);
					Vect recal = 5.0f * result;
					float x = recal[X];
					float y = recal[Y];
					b2Vec2 fly(x,y);

					BirdObject *ptmp = (BirdObject*) pBird;
					ptmp->LaunchBird(fly);
					

					if(originalx - line1->posA.x >0)
					{
						line1->posA.x+=2;
					}
					if(originalx - line1->posA.x <0)
					{
						line1->posA.x-=2;
					}
					if(originalx - line2->posA.x >0)
					{
						line2->posA.x+=2;
					}
					if(originalx - line2->posA.x <0)
					{
						line2->posA.x-=2;
					}
					if(originaly - line1->posA.y >0)
					{
						line1->posA.y+=2;
					}
					if(originaly - line1->posA.y <0)
					{
						line1->posA.y-=2;
					}
					if(originaly - line2->posA.y >0)
					{
						line2->posA.y+=2;
					}
					if(originaly - line2->posA.y <0)
					{
						line2->posA.y-=2;
					}
			}
		}
		BirdObject* tmp = (BirdObject*) pBird;
		if( mState == LEFT && tmp->fired == true && tmp->used == false && tmp->madeContact == false)
		{
			tmp->ability();
		}
}


void KeyboardTest( GLFWwindow* window, IGameObject *pBird )
{
	// Quick and dirty test, if these work the rest do.
	// ---> try a,s,d,<SPACE> keys

	if ( glfwGetKey (window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		// reset
		bState = NORMAL;
		b2Vec2 pos(PixelToMeter(100.0f),PixelToMeter(215.0f));
		pBird->getBody()->SetTransform( pos, 0.0f);
		b2Vec2 clear( 0, 0);
		pBird->getBody()->ApplyLinearImpulse( clear, pBird->getBody()->GetWorldCenter(), true);
		pBird->getBody()->SetActive(false);
		pBird->getBody()->SetAngularVelocity( 0.0f );
		pBird->getBody()->SetLinearVelocity( clear );
	}	

	if ( glfwGetKey (window, GLFW_KEY_LEFT) == GLFW_PRESS)
		{
			Camera *pCam = Camera::Instance();
			Vect pos;
			Vect dir;
			Vect lookAt;
			Vect up;
			Vect right;

			pCam->getPos( pos );
			pCam->getDir( dir );
			pCam->getLookAt( lookAt );
			pCam->getUp( up );
			pCam->getRight( right );

			pos += right * 1.0f;
			lookAt += right * 1.0f;

			pCam->setOrientAndPosition( up, lookAt, pos );
		}

	if ( glfwGetKey (window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		{
			Camera *pCam = Camera::Instance();
			Vect pos;
			Vect dir;
			Vect lookAt;
			Vect up;
			Vect right;

			pCam->getPos( pos );
			pCam->getDir( dir );
			pCam->getLookAt( lookAt );
			pCam->getUp( up );
			pCam->getRight( right );


			pos -= right * 1.0f;
			lookAt -= right * 1.0f;
			pCam->setOrientAndPosition( up, lookAt, pos );
		}



}


void KeyboardTest(GLFWwindow* window)
{
	if(glfwGetKey (window,GLFW_KEY_R) == GLFW_PRESS)
		{
			printf("\nR Key PRessed\n");
			reset = true;
		}
}