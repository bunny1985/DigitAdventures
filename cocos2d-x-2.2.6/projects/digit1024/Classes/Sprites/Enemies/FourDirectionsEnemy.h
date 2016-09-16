/*
 * FourDirectionEnemy.h
 *
 *  Created on: 20-07-2013
 *      Author: michal
 */

#ifndef FOURDIRECTIONENEMY_H_
#define FOURDIRECTIONENEMY_H_
#include "Sprites/Enemies/TwoDirectionsEnemy.h"

class FourDirectionsEnemy: public AbstractEnemy
{
public:
	FourDirectionsEnemy();
	virtual ~FourDirectionsEnemy();
	virtual GameDirection pickDirection();
	virtual void setTurn(int turn);
	virtual void startMoving();
	static FourDirectionsEnemy* create();
	void applyProperties(CCDictionary* dictionary);
protected:
	GameDirection lastDirection;
	int turn;

};

class FourDirectionsEnemy_UP : public FourDirectionsEnemy{
public:
	SPRITECREATION("enemy1.png", FourDirectionsEnemy_UP);
	FourDirectionsEnemy_UP() 
		: FourDirectionsEnemy()
	{
		direction = GameDirectionUp;
		lastDirection = direction;
	}

};
class FourDirectionsEnemy_DOWN : public FourDirectionsEnemy{
public:
	SPRITECREATION("enemy1.png", FourDirectionsEnemy_DOWN);
	FourDirectionsEnemy_DOWN() : FourDirectionsEnemy(){
		direction = GameDirectiondDown;
		lastDirection = direction;
	}

};
class FourDirectionsEnemy_LEFT : public FourDirectionsEnemy{
public:
	SPRITECREATION("enemy1.png", FourDirectionsEnemy_LEFT);
	FourDirectionsEnemy_LEFT() : FourDirectionsEnemy(){
		direction = GameDirectionLeft;
		lastDirection = direction;
	}

};
class FourDirectionsEnemy_RIGHT : public FourDirectionsEnemy{
public:
	SPRITECREATION("enemy1.png", FourDirectionsEnemy_RIGHT);
	FourDirectionsEnemy_RIGHT() : FourDirectionsEnemy(){
		direction = GameDirectionRigh;
		lastDirection = direction;
	}

};


#endif /* FOURDIRECTIONENEMY_H_ */
