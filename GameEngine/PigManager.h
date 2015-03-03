#ifndef PIG_OBJ_MANAGER_H
#define PIG_OBJ_MANAGER_H


#include <list>
#include "PigObject.h"
#include "SmallPigObject.h"
#include "MediumPigObj.h"

class PigManager
{
public:
	static PigManager *getInstance();

	 std::list<PigObject *> *getList();
	 void addPigToList(PigObject* pig);
	 void removePigFromList(PigObject* pig);

	 std::list<PigObject *>  pig_list;

private:
	PigManager();
	static bool instanceFlag;
	static PigManager *single;
	bool victory;
};
#endif