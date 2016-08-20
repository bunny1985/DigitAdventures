/*
 * Cannon.h
 *
 *  Created on: 23-07-2013
 *      Author: michal
 */

#ifndef CANNON_H_
#define CANNON_H_
#include "Sprites/Enemies/Abstractenemy.h"

class Cannon: public AbstractEnemy
{

public:
	Cannon();
	virtual ~Cannon();


	SPRITECREATION("cannon.png" , Cannon );
	virtual void hit(GameDirection hitDirection, GameSprite *object);
	virtual void update();
	virtual void setDirection(GameDirection direction);
	virtual GameDirection pickDirection(){return GameDirectionUnknown;};
protected:



};

#endif /* CANNON_H_ */
