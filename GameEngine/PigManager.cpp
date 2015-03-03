#include "PigManager.h"


bool PigManager::instanceFlag;

PigManager *PigManager::single;


PigManager::PigManager()
{
}

 std::list<PigObject *> *PigManager::getList()
 {
	 return &pig_list;
 }
void PigManager::addPigToList(PigObject* pig)
{
	if(pig_list.size() == 0)
	{
		pig_list.push_front(pig);

	}
	else
		pig_list.push_back(pig);
}
void PigManager::removePigFromList(PigObject* pig)
{
	pig_list.remove(pig);
	//std::list< PigObject*>::iterator Pigs = pig_list.begin();
	if(pig_list.size() == 0)
		victory = true;	
}

PigManager* PigManager::getInstance()
{
	if(! instanceFlag)
	{
		single = new PigManager();
		instanceFlag = true;
		return single;
	}
	else
	{
		return single;
	}
}