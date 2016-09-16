/*
 * LaserMark.h
 *
 *  Created on: 23-07-2013
 *      Author: michal
 */

#ifndef LASERMARK_H_
#define LASERMARK_H_
#include "Sprites/GameSprite.h"

class LaserMark: public GameSprite
{
public:
	LaserMark();
	virtual ~LaserMark();
	virtual bool canBeMoved(GameDirection d);
	virtual bool pushed(GameDirection d);
	virtual void getKill();
	virtual void rollIn();
	virtual void update();
	virtual void onKill();
	void hit(GameDirection hitDirection, GameSprite* object){}
	
	static LaserMark* create(LaserMark* prevMark, GameSprite* parent);

	LaserMark* prevMark;
	LaserMark* nextMark;
	GameSprite* parent;
};

#endif /* LASERMARK_H_ */
