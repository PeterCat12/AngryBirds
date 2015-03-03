#ifndef CAMERA_MAN_H
#define CAMERA_MAN_H

#include "AzulCore.h"
#include "Box2D.h"
#include "Time.h"
#include "MathEngine.h"
#include "BirdObject.h"

class CameraManager
{
public:
	static CameraManager *getInstance();
	static void Initialize(GLFWwindow* const windowIn);
	static void FollowBird(BirdObject* const pBird);
	static void ChaseBird();
	static void GoBackToStart();
	BirdObject *pTarget;
	bool goBackToStart;
private:
	CameraManager();
	float birdOffsetX;
	Vect startLook;
	Vect startUp;
	Vect startPos;
	GLFWwindow*				window;		
	Camera*					pCam;

	static bool instanceFlag;
	static CameraManager *single;
};
#endif
