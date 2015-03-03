#ifndef _OBJECT_H
#define _OBJECT_H

#include "EnumName.h"

class Object
{
public:
	virtual GameObjectName::Name getName() = 0;
	virtual void startContact() = 0;
	virtual void endContact() = 0;
private:

};

#endif