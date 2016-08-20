/*
 * StaticLaserCannon.h
 *
 *  Created on: 23-07-2013
 *      Author: michal
 */

#ifndef STATICLASERCANNON_H_
#define STATICLASERCANNON_H_
#include "Sprites/Enemies/StaticSimpleCannon.h"
#include "Sprites/Bulets/LaserBullet.h"

class StaticLaserCannon: public StaticSimpleCannon
{
public:
	StaticLaserCannon();
	virtual ~StaticLaserCannon();
	virtual void getKill();
	virtual void shoot();
	LaserBullet *bullet;

	SPRITECREATION("cannon-Laser.png" , StaticLaserCannon);
};

class StaticLaserCannon_UP : public StaticLaserCannon
{
public:
	StaticLaserCannon_UP() :StaticLaserCannon(){
		setDirection(GameDirectionUp);
		shotingDirection = GameDirectionUp;

	}
	SPRITECREATION("cannon-Laser.png", StaticLaserCannon_UP);
};
class StaticLaserCannon_DOWN : public StaticLaserCannon
{
public:
	StaticLaserCannon_DOWN() :StaticLaserCannon(){
		setDirection(GameDirectiondDown);
		shotingDirection = GameDirectiondDown;

	}
	SPRITECREATION("cannon-Laser.png", StaticLaserCannon_DOWN);
};
class StaticLaserCannon_LEFT : public StaticLaserCannon
{
public:
	StaticLaserCannon_LEFT() :StaticLaserCannon(){
		setDirection(GameDirectionLeft);
		shotingDirection = GameDirectionLeft;

	}
	SPRITECREATION("cannon-Laser.png", StaticLaserCannon_LEFT);
};
class StaticLaserCannon_RIGHT : public StaticLaserCannon
{
public:
	StaticLaserCannon_RIGHT() :StaticLaserCannon(){
		setDirection(GameDirectionRigh);
		shotingDirection = GameDirectionRigh;

	}
	SPRITECREATION("cannon-Laser.png", StaticLaserCannon_RIGHT);
};

class StaticLaserCannonRotating : public StaticLaserCannon
{
public:
	StaticLaserCannonRotating() :StaticLaserCannon(){
		setDirection(GameDirectionRigh);
		shotingDirection = GameDirectionRigh;

	}
	SPRITECREATION("cannon-Laser.png", StaticLaserCannonRotating);
	void shoot();
};

#endif /* STATICLASERCANNON_H_ */
