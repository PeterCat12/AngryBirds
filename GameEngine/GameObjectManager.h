#ifndef GAME_OBJECT_MANAGER_H
#define GAME_OBJECT_MANAGER_H

#include <list>
#include "GameObject.h"


class GameObjectManager
{
protected:
	std::list<IGameObject *> m_lGameObjList;

public:
	static GameObjectManager *getInstance();
	static void UpdateGameObjects();
	static void Reset();
	 std::list<IGameObject *>* getList();
	 void addGameObjectToList(IGameObject* obj);
	 void removeGameObjectFromList(IGameObject* obj);

	 static void ZeroHealth();

private:
	GameObjectManager();
	void privReset();
	void privUpdateGameObject();
	void privZeroHealth();

	static bool instanceFlag;
	static GameObjectManager *single;
};
#endif

