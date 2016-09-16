/*
 * TwoDirectionsEnemy.h
 *
 *  Created on: 19-07-2013
 *      Author: michal
 */

#ifndef LAVA_H_
#define LAVA_H_

#include "Sprites/Enemies/Abstractenemy.h"


class Lava : public AbstractEnemy
{
public:
	Lava();
	SPRITECREATION("lava.png", Lava);
	virtual GameDirection pickDirection();;
	virtual void touchTest();
	bool canBeMoved(GameDirection direction){ return true; };
	virtual void startMoving();
	void fixPosition(){};
	void makeMove(GameDirection direction);
	void hit(GameDirection hitDirection, GameSprite* object);
	void update();
	void grow(float d);
	int lavaId;
	
	static int maxId;

};

#endif /* TWODIRECTIONSENEMY_H_ */
