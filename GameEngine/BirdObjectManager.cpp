#include "BirdObjectManager.h"
#include "Input.h"

bool BirdObjectManager::instanceFlag;

BirdObjectManager *BirdObjectManager::single;


BirdObjectManager::BirdObjectManager()
{
}

 std::list<BirdObject *> *BirdObjectManager::getList()
 {
	 return &m_lBirds;
 }
void BirdObjectManager::addBirdToList(BirdObject* bird)
{
	if(m_lBirds.size() == 0)
	{
		m_lBirds.push_front(bird);
			//BirdObject *ptmp = (BirdObject*) pSecondBird;
	bird->state = LAUNCHER;
	bird->SwapSprite(LAUNCHER);
	}
	else
		m_lBirds.push_back(bird);
}
void BirdObjectManager::removeBirdFromList(BirdObject* bird)
{
	m_lBirds.remove(bird);
	std::list< BirdObject*>::iterator birds = m_lBirds.begin();
	if( birds != m_lBirds.end())
	{
		BirdObject *pBird = *birds++;
		pBird->state = LAUNCHER;
		pBird->SwapSprite(LAUNCHER);
		b2Vec2 pos(PixelToMeter(100.0f),PixelToMeter(215.0f));
		pBird->getBody()->SetTransform( pos, 0.0f);
		b2Vec2 clear( 0, 0);
		pBird->getBody()->ApplyLinearImpulse( clear, pBird->getBody()->GetWorldCenter(), true);
		pBird->getBody()->SetActive(false);
		pBird->getBody()->SetAngularVelocity( 0.0f );
		pBird->getBody()->SetLinearVelocity( clear );
	}
	CameraManager::getInstance()->goBackToStart = true;
}

BirdObjectManager* BirdObjectManager::getInstance()
{
	if(! instanceFlag)
	{
		single = new BirdObjectManager();
		instanceFlag = true;
		return single;
	}
	else
	{
		return single;
	}
}

void BirdObjectManager::updateBirds(GLFWwindow* window,ScreenLine* line1, ScreenLine* line2)
{
	BirdObjectManager::getInstance()->privUpdateBirds(window,line1,line2);
}

void BirdObjectManager::privUpdateBirds(GLFWwindow* window, ScreenLine* pLine, ScreenLine* pLine2)
{
	std::list< BirdObject*>::iterator birds = m_lBirds.begin();
	if( birds != m_lBirds.end())
	{
		BirdObject *pBird = *birds++;
		MouseTest(window,pBird, pLine,pLine2);
		KeyboardTest(window, pBird);
	}
	else{
		KeyboardTest(window);
	}
}

int BirdObjectManager::GetSize()
{
	return BirdObjectManager::getInstance()->getList()->size();
}

void BirdObjectManager::Reset()
{
	BirdObjectManager::getInstance()->privReset();
}

void BirdObjectManager::privReset()
{
	std::list< BirdObject*>::iterator birds =m_lBirds.begin();
	while (birds != m_lBirds.end() )
	{
		BirdObject *pBird = *birds++;
		BirdObjectManager::getInstance()->removeBirdFromList(pBird);
	}
}


