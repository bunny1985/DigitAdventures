/*
 * Ground.cpp
 *
 *  Created on: 21-07-2013
 *      Author: michal
 */

#include "Sprites/Objects/Ground.h"
#include "Common/Resources.h"

Ground::Ground() :
		GameSprite()
{
	currentState = 0;
	speed = 0;
	type = GAME_TYPE_GROUND;
	properities |= PSHOOTABLE;
	direction = GameDirectionUnknown;
}

Ground::~Ground()
{
	// TODO Auto-generated destructor stub
}

