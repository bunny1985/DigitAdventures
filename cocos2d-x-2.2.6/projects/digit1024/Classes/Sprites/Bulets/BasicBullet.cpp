/*
 * BasicBullet.cpp
 *
 *  Created on: 21-07-2013
 *      Author: michal
 */

#include "Sprites/Bulets/BasicBullet.h"
#include "Common/Resources.h"

BasicBullet::BasicBullet() :
		AbstractBullet()
{
	this->currentState = 0;

	direction = GameDirectionUnknown;
	type = GAME_TYPE_BULLET;
}

BasicBullet::~BasicBullet()
{

}
