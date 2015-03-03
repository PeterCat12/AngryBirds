#include "CameraMan.h"


bool CameraManager::instanceFlag;

CameraManager *CameraManager::single;

CameraManager::CameraManager()
{
	pTarget = 0;
	 startUp = Vect(0.0f,1.0f,0.0f);
	 startLook = Vect(0.0f,0.0f, -1.0f);
	 startPos =	 Vect(0.0f,0.0f, 0.00f);
	 goBackToStart = false;
}


void CameraManager::GoBackToStart()
{
	
	CameraManager *CH = CameraManager::getInstance();
	CH->goBackToStart = false;
	//CH->goBackToStart = false;
	//Vect CamPos;
	//Vect CamLookAt;
	//Vect up;
	//CH->pCam->getPos(CamPos);
	//CH->pCam->getLookAt(CamLookAt);
	//CH->pCam->getUp(up);


	////Where is the start??
	//Vect bPos = Vect( 0, 0, CamPos.vz);
	//Vect bLookAt = Vect( 0,0, CamLookAt.vz);

	//float distance = CamPos[x] - bPos[x];

	////store before adjustment
	//	Vect pos;
	//	Camera::Instance()->getPos(pos);

		//if(pos[x] < WindowViewWidth/2.0f)
		//{
		//	if(distance > 300)
		//	{
		//		CamPos[x] = CamPos[x] - (distance * 0.005f);
		//		CamLookAt[x] = CamLookAt[x] - (distance * 0.005f);
		//		
		//		if(pos[z] < 0.075f)
		//		{
		//			float diff = 0.25f - pos[z];
		//			diff *= 0.0025f;
		//		}
		//	}
		//	else if(distance < 0)
		//	{
		//		CamPos[x] = CamPos[x] - (distance * 0.05f);
		//		CamLookAt[x] = CamLookAt[x] - (distance * 0.05f);
		//			
		//	}
		//	if(pos[x] <= -WindowViewWidth/2.0f)
		//	{
		//		CamPos[x] = -WindowViewWidth/2.0f;
		//		CamLookAt[x] = -WindowViewWidth/2.0f;
		//	}
		//}

		//if(pos[x] >= WindowViewWidth/2.0f)
		//{
		//	CamPos[x] = WindowViewWidth/2.0f;
		//	CamLookAt[x] = WindowViewWidth/2.0f;
		//}
		////	CH->pCam->setOrientAndPosition(up,CamLookAt,CamPos);

	CH->pCam->setOrientAndPosition( CH->startUp,CH->startLook,CH->startPos);
}
void CameraManager::Initialize(GLFWwindow* const windowIn)
{
	CameraManager *cam = CameraManager::getInstance();
	cam->pCam = Camera::Instance();
	cam->window = windowIn;
}

void CameraManager::FollowBird(BirdObject* const pBird)
{
	CameraManager *cam = CameraManager::getInstance();
	cam->pTarget = pBird;
	Vect camPos;
		cam->pCam->getPos(camPos);
		cam->birdOffsetX = camPos[X] - pBird->getPosX();
}

CameraManager* CameraManager::getInstance()
{
	if(! instanceFlag)
	{
		single = new CameraManager();
		instanceFlag = true;
		return single;
	}
	else
	{
		return single;
	}
}


void CameraManager::ChaseBird()
{

	CameraManager *CH = CameraManager::getInstance();

	if(CH->pTarget->fired == true)
	{
	Vect CamPos;
	Vect CamLookAt;
	Vect up;
	CH->pCam->getPos(CamPos);
	CH->pCam->getLookAt(CamLookAt);
	CH->pCam->getUp(up);
	//Where is the bird?
	Vect bPos = Vect( CH->pTarget->getPosX() - WindowViewWidth/2, CH->pTarget->getPosY() - WindowViewHeight/2, CamPos.vz);
	Vect bLookAt = Vect( CH->pTarget->getPosX() - WindowViewWidth/2, CH->pTarget->getPosY() - WindowViewHeight/2, CamLookAt.vz);

	float distance = CamPos[x] - bPos[x];

	//store before adjustment
		Vect pos;
		Camera::Instance()->getPos(pos);
	if(bPos[x] > CamPos[x])
	{
		if(pos[x] < WindowViewWidth/2.0f)
		{
			if(distance > 250)
			{
				CamPos[x] = CamPos[x] - (distance * 0.005f);
				CamLookAt[x] = CamLookAt[x] - (distance * 0.005f);
				

				if(pos[z] < 0.075f)
				{
					float diff = 0.25f - pos[z];
					diff *= 0.0025f;
				}
			}
			else if(distance < 0)
			{
				CamPos[x] = CamPos[x] - (distance * 0.05f);
				CamLookAt[x] = CamLookAt[x] - (distance * 0.05f);
					
			}
			if(pos[x] <= -WindowViewWidth/2.0f)
			{
				CamPos[x] = -WindowViewWidth/2.0f;
				CamLookAt[x] = -WindowViewWidth/2.0f;
			}
		}

		if(pos[x] >= WindowViewWidth/2.0f)
		{
			CamPos[x] = WindowViewWidth/2.0f;
			CamLookAt[x] = WindowViewWidth/2.0f;
		}
			CH->pCam->setOrientAndPosition(up,CamLookAt,CamPos);
	}

	}
	//This works... Just need to ease into it...
		if(CH->goBackToStart == true)
			GoBackToStart();
}