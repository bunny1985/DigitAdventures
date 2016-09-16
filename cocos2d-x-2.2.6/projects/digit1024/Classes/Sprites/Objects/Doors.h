/*
 * Doors.h
 *
 *  Created on: 22-07-2013
 *      Author: michal
 */

#ifndef DOORS_H_
#define DOORS_H_
#include "Sprites/Objects/Ground.h"

class Doors: public Ground
{
public:
	Doors();
	virtual ~Doors();
	virtual void hit(GameDirection hitDirection, GameSprite *object);
	virtual bool pushed(GameDirection direction);
	virtual void makeMove(GameDirection direction)
	{
	}
	;
	virtual bool canBeMoved(GameDirection direction);SPRITECREATION("door.png" , Doors)
	;

};

#endif /* DOORS_H_ */
