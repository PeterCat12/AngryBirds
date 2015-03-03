#ifndef CLOUD_TRAIL_MANAGER_H
#define CLOUD_TRAIL_MANAGER_H


#include "CloudTrail.h"
#include <list>

enum List
{
	LIST1,
	LIST2
};


class CloudTrailManager
{
	//just do two STL lists for now..
public:
	static CloudTrailManager *getInstance();

	void spawnCloud(float centerX, float centerY);
	void resetLists();
	 std::list<CloudTrail_Obj *> getCurrentList();
	 void changeCurrentList();
	
	 std::list<CloudTrail_Obj *>  list_1;
	 std::list<CloudTrail_Obj *>   list_2;

private:
	CloudTrailManager();
	static bool instanceFlag;
	static CloudTrailManager *single;
	 List currentList;
	 void eraseList( std::list<CloudTrail_Obj *> *list);

};

#endif