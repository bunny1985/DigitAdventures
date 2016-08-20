/*
 * Bomb.h
 *
 *  Created on: 21-07-2013
 *      Author: michal
 */

#ifndef BOMB_H_
#define BOMB_H_
#include "Sprites/Objects/Box.h"
class Bomb: public Box
{
	enum BombStates
	{
		BombStateIdle, BombStateMoving, BombStateDestroing
	};
public:
	Bomb();
	virtual ~Bomb();
	void onGetKill();
	virtual void getKill();SPRITECREATION("bomb.png" , Bomb)
	;
};

#endif /* BOMB_H_ */
