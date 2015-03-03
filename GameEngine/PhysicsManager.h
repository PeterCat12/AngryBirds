#ifndef PHYSICSMAN_H
#define PHYSICSMAN_H

#include "Box2D.h"

class PhysicsMan
{
protected:

public:

	//General Methods
	static PhysicsMan* Instance();
	static void UpdatePhysics(b2World* world);
	static void Delete();
	~PhysicsMan();

private:
	PhysicsMan();
	static bool instanceFlag;
	static PhysicsMan *single;
	void privUpdatePhysics(b2World* world);

};
#endif