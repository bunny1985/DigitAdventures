/*
 * LaserBullet.h
 *
 *  Created on: 23-07-2013
 *      Author: michal
 */

#ifndef LASERBULLET_H_
#define LASERBULLET_H_
#include "Sprites/Bulets/BasicBullet.h"
#include "Sprites/Bulets/LaserMark.h"

class LaserBullet: public BasicBullet
{
public:
	LaserBullet();
	virtual ~LaserBullet();
	virtual void makeMove();
	virtual void continueMove();

	virtual void getKill();
	static LaserBullet* create(GameSprite* parent);
	LaserMark* lastMark;
protected:
	
	GameSprite* parent;
	GameSprite* descendand;
};

#endif /* LASERBULLET_H_ */
