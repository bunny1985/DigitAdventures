/*
 * FourDirectionEnemy.h
 *
 *  Created on: 20-07-2013
 *      Author: michal
 */

#ifndef FOLLOWINGENEMY_H_
#define FOLLOWINGENEMY_H_
#include "Sprites/Enemies/FourDirectionsEnemy.h"

class FollowingEnemy : public FourDirectionsEnemy
{
public:
	SPRITECREATION("enemy2.png", FollowingEnemy)
		GameDirection pickDirection();
	void setDirection(GameDirection direction);
};


#endif /* FOLLOWINGENEMY_H_ */
