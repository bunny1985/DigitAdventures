/*
 * FourDirectionEnemy.h
 *
 *  Created on: 20-07-2013
 *      Author: michal
 */

#ifndef MAGNET_H_
#define MAGNET_H_
#include "Sprites/Enemies/AbstractEnemy.h"

class MagnetEnemy : public AbstractEnemy
{
public:
	SPRITECREATION("magnet.png", MagnetEnemy);
	GameDirection pickDirection();
	void setDirection(GameDirection direction);
	void update();
	MagnetEnemy();
	
	GameSprite* postCreate(const char* framename);
private:
	CCSprite* field;
	int fieldCount;

	
};
class MagnetEnemy_Up : public MagnetEnemy{
public:
	SPRITECREATION("magnet.png", MagnetEnemy_Up);
	MagnetEnemy_Up(): MagnetEnemy(){
		setDirection(GameDirectionUp);
	}
};
class MagnetEnemy_Down : public MagnetEnemy{
public:
	SPRITECREATION("magnet.png", MagnetEnemy_Down);
	MagnetEnemy_Down() : MagnetEnemy(){
		setDirection(GameDirectiondDown);
	}
};
class MagnetEnemy_Left : public MagnetEnemy{
public:
	SPRITECREATION("magnet.png", MagnetEnemy_Left);
	MagnetEnemy_Left() : MagnetEnemy(){
		setDirection(GameDirectionLeft);
	}
};
class MagnetEnemy_Right : public MagnetEnemy{
public:
	SPRITECREATION("magnet.png", MagnetEnemy_Right);
	MagnetEnemy_Right() : MagnetEnemy(){
		setDirection(GameDirectionRigh);
	}
};

#endif /* FOLLOWINGENEMY_H_ */
