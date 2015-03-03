#include "CloudTrailManager.h"


bool CloudTrailManager::instanceFlag;

CloudTrailManager *CloudTrailManager::single;

void CloudTrailManager::spawnCloud(float centerX, float centerY)
{


	CloudTrail_Obj *cloud = new CloudTrail_Obj(centerX, centerY);
	if(currentList == LIST1)
	{
		list_1.push_front(cloud);
	}
	else
	{
		list_2.push_front(cloud);
	}
}

void CloudTrailManager::resetLists()
{
	eraseList(&list_1);
	eraseList(&list_2);
}

void CloudTrailManager::eraseList( std::list<CloudTrail_Obj *> *cloudList)
{
		std::list< CloudTrail_Obj *>::iterator it=cloudList->begin();
				while( it!=cloudList->end() )
				{
					CloudTrail_Obj *pCloud = *it++;
					cloudList->remove(pCloud);
						delete pCloud;
				}
}

void CloudTrailManager::changeCurrentList()
{
	if(currentList == LIST1)
	{
		currentList = LIST2;
		if(list_2.size() > 0)
			eraseList(&list_2);
	}
	else
	{
		currentList = LIST1;
		if(list_1.size() > 0)
			eraseList(&list_1);
	}
}


std::list<CloudTrail_Obj *> CloudTrailManager::getCurrentList()
{
	if(currentList == LIST1)
		return list_1;
	else
		return list_2;
}


CloudTrailManager::CloudTrailManager()
{
	currentList = LIST1;
}


CloudTrailManager* CloudTrailManager::getInstance()
{
	if(! instanceFlag)
	{
		single = new CloudTrailManager();
		instanceFlag = true;
		return single;
	}
	else
	{
		return single;
	}
}
