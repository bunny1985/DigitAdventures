/*
 * Doors.cpp
 *
 *  Created on: 22-07-2013
 *      Author: michal
 */

#include "Sprites/Objects/Doors.h"
#include "Common/Resources.h"
#include "Sprites/Robbo.h"
#include "SimpleAudioEngine.h"
#include "GameLevelScene.h"
#include "Common/RESPATH.h"
Doors::Doors() :
		Ground()
{
	direction = GameDirectionUnknown;
	speed = 0;
	currentState = 0;
	type = GAME_TYPE_Door;
	properities = 0;
	properities |= PPUSHABLE;
	//properities & (~PSHOOTABLE);
}

Doors::~Doors()
{
	// TODO Auto-generated destructor stub
}

void Doors::hit(GameDirection hitDirection, GameSprite* object)
{
	CCLOG("DOORS PUSHED");
	if (object->getType() == GAME_TYPE_ROBBO)
	{
		if (((Robbo*) object)->OpenDoor())
		{
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(respatchFix(
					"Sounds/door" SOUND_EXT).c_str());
			getKill();
		}
		else
		{
			object->fixPosition();
		}
	}
	
	
}

bool Doors::pushed(GameDirection direction)
{
	Robbo* r = GAMEUTILS->robboSprite;
	CCLOG("PUSHED");
	if (r->getKeys() == 0)
	{ 
		r->fixPosition(); 
	}
	return(r->getKeys()>0);
}

bool Doors::canBeMoved(GameDirection direction)
{
	return true;
}
