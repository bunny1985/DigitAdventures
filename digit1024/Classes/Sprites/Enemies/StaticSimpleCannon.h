/*
 * StaticSimpleCannon.h
 *
 *  Created on: 23-07-2013
 *      Author: michal
 */

#ifndef STATICSIMPLECANNON_H_
#define STATICSIMPLECANNON_H_
#include "Sprites/Enemies/Cannon.h"

class StaticSimpleCannon: public Cannon
{
public:
	StaticSimpleCannon();
	virtual ~StaticSimpleCannon();
	SPRITECREATION("cannon.png" , StaticSimpleCannon);
};


class StaticSimpleCannon_UP : public StaticSimpleCannon
{
public:
	StaticSimpleCannon_UP() :StaticSimpleCannon(){
		setDirection(GameDirectionUp);
		shotingDirection = GameDirectionUp;
		
	}
	SPRITECREATION("cannon.png", StaticSimpleCannon_UP);
};
class StaticSimpleCannon_DOWN : public StaticSimpleCannon
{
public:
	StaticSimpleCannon_DOWN() :StaticSimpleCannon(){
		setDirection(GameDirectiondDown);
		shotingDirection = GameDirectiondDown;
	}
	SPRITECREATION("cannon.png", StaticSimpleCannon_DOWN);
};
class StaticSimpleCannon_LEFT : public StaticSimpleCannon
{
public:
	StaticSimpleCannon_LEFT() :StaticSimpleCannon(){
		setDirection(GameDirectionLeft);
		shotingDirection = GameDirectionLeft;
	}
	SPRITECREATION("cannon.png", StaticSimpleCannon_LEFT);
};
class StaticSimpleCannon_RIGHT : public StaticSimpleCannon
{
public:
	StaticSimpleCannon_RIGHT() :StaticSimpleCannon(){
		setDirection(GameDirectionRigh);
		shotingDirection = GameDirectionRigh;
	}
	SPRITECREATION("cannon.png", StaticSimpleCannon_RIGHT);
};
class StaticSimpleCannonRotating : public StaticSimpleCannon
{
public:
	SPRITECREATION("cannon.png", StaticSimpleCannonRotating);
	void shoot();
};


#endif /* STATICSIMPLECANNON_H_ */
