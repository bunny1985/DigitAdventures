/*
 * TwoDirectionsEnemy.h
 *
 *  Created on: 19-07-2013
 *      Author: michal
 */

#ifndef TWODIRECTIONSENEMY_H_
#define TWODIRECTIONSENEMY_H_

#include "Sprites/Enemies/Abstractenemy.h"

class TwoDirectionsEnemy: public AbstractEnemy
{
public:
	TwoDirectionsEnemy();
	virtual ~TwoDirectionsEnemy();
	SPRITECREATION("enemy3.png" , TwoDirectionsEnemy);
	virtual GameDirection pickDirection();
	void setDirection(GameDirection direction);

};

class TwoDirectionsEnemy_UP : public TwoDirectionsEnemy{
public:
	SPRITECREATION("enemy3.png", TwoDirectionsEnemy_UP);
	TwoDirectionsEnemy_UP(){
		direction = GameDirectionUp;
		lastDirection = direction;
	}

};
class TwoDirectionsEnemy_DOWN : public TwoDirectionsEnemy{
public:
	SPRITECREATION("enemy3.png", TwoDirectionsEnemy_DOWN);
	TwoDirectionsEnemy_DOWN(){
		direction = GameDirectiondDown;
		lastDirection = direction;
	}
};
class TwoDirectionsEnemy_LEFT : public TwoDirectionsEnemy{
public:
	SPRITECREATION("enemy3.png", TwoDirectionsEnemy_LEFT);
	TwoDirectionsEnemy_LEFT(){
		direction = GameDirectionLeft;
		lastDirection = direction;
	}
};
class TwoDirectionsEnemy_RIGHT : public TwoDirectionsEnemy{
public:
	SPRITECREATION("enemy3.png", TwoDirectionsEnemy_RIGHT);
	TwoDirectionsEnemy_RIGHT(){
		direction = GameDirectionRigh;
		lastDirection = direction;
	}
};


#endif /* TWODIRECTIONSENEMY_H_ */
