#ifndef BIRD_OBJ_MANAGER_H
#define BIRD_OBJ_MANAGER_H


#include <list>
#include "BirdObject.h"
#include "CameraMan.h"

class ScreenLine;

class BirdObjectManager
{
public:
	static BirdObjectManager *getInstance();

	 std::list<BirdObject *> *getList();
	 void addBirdToList(BirdObject* bird);
	 void removeBirdFromList(BirdObject* bird);
	 static void updateBirds(GLFWwindow* window,ScreenLine* line1, ScreenLine* line2 );
	 static int GetSize();
	 static void Reset();

	 std::list<BirdObject *>  m_lBirds;

private:
	BirdObjectManager();
	void privUpdateBirds(GLFWwindow* window, ScreenLine* line1, ScreenLine* line2);
	void privReset();
	static bool instanceFlag;
	static BirdObjectManager *single;
};
#endif