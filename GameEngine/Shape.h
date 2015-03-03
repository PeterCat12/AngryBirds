#ifndef SHAPE_H
#define SHAPE_H

#include "BoxSprite.h"
#include "CircleSprite.h"

class BoxSprite;
class CircleSprite;

class Shape
{
public:
	CircleSprite *circle;
	BoxSprite *box;


	Shape(CircleSprite *circle){
		this->circle = circle;
	}
	Shape(BoxSprite *box){
		this->box = box;
	}

};


#endif