#include "GameObjectManager.h"
#include "BirdObjectManager.h"

bool GameObjectManager::instanceFlag;

GameObjectManager *GameObjectManager::single;


GameObjectManager::GameObjectManager()
{
}

std::list<IGameObject *> *GameObjectManager::getList()
 {
	 return &m_lGameObjList;
 }
void GameObjectManager::addGameObjectToList(IGameObject* obj)
{
		m_lGameObjList.push_front(obj);
}
void GameObjectManager::removeGameObjectFromList(IGameObject* obj)
{
	m_lGameObjList.remove(obj);
}

GameObjectManager* GameObjectManager::getInstance()
{
	if(! instanceFlag)
	{
		single = new GameObjectManager();
		instanceFlag = true;
		return single;
	}
	else
	{
		return single;
	}
}

void GameObjectManager::ZeroHealth()
{
	GameObjectManager::getInstance()->privZeroHealth();	
}

void GameObjectManager::privZeroHealth()
{
	std::list< IGameObject *>::iterator tmp2=m_lGameObjList.begin();
	while( tmp2!=m_lGameObjList.end() )
	{
		IGameObject *pGameObj = *tmp2++;
		pGameObj->zeroHealth();
	}
}

void GameObjectManager::UpdateGameObjects()
{
	GameObjectManager::getInstance()->privUpdateGameObject();
}

void GameObjectManager::Reset()
{
	GameObjectManager::getInstance()->privReset();
}

void GameObjectManager::privReset()
{
	std::list<IGameObject*>::iterator it = m_lGameObjList.begin();
	while( it!=m_lGameObjList.end() )
	{
		IGameObject *pGameObj = *it++;
		GameObjectManager::getInstance()->removeGameObjectFromList(pGameObj);	
		delete pGameObj;
	}
}

void GameObjectManager::privUpdateGameObject()
{
	std::list< IGameObject *>::iterator it=m_lGameObjList.begin();
	while( it!=m_lGameObjList.end() )
	{
		IGameObject *pGameObj = *it++;
		if( pGameObj->updateGame())
		{
			m_lGameObjList.remove( pGameObj );
			// Just horrible design...
			if(pGameObj->getObjectName() == GameObjectName::GameObject_RedBird ||
				pGameObj->getObjectName() == GameObjectName::GameObject_YellowBird ||
				pGameObj->getObjectName() == GameObjectName::GameObject_BlueBird  ||
				pGameObj->getObjectName() == GameObjectName::GameObject_WhiteBird ||
				pGameObj->getObjectName() == GameObjectName::GameObject_GreenBird)
			{
				//BirdObjectList->remove((BirdObject*) pGameObj);
				BirdObjectManager::getInstance()->removeBirdFromList((BirdObject*) pGameObj);
			}
			delete pGameObj;
		}
	}
}
