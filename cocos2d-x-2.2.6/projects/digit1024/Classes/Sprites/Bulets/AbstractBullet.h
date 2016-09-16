/*
 * AbstractBullet.h
 *
 *  Created on: 21-07-2013
 *      Author: michal
 */

#ifndef ABSTRACTBULLET_H_
#define ABSTRACTBULLET_H_
#include "Sprites/GameSprite.h"

class AbstractBullet: public GameSprite
{
public:
	AbstractBullet();
	virtual ~AbstractBullet();
	virtual void hit(GameDirection hitDirection, GameSprite *object);
	virtual bool pushed(GameDirection direction);
	virtual bool canBeMoved(GameDirection direction);
	virtual void startShoot(GameDirection direction);
	virtual void makeMove();
	virtual void update();
protected:
	CCSequence* moveSequence;
};

#endif /* ABSTRACTBULLET_H_ */
