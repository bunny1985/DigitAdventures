/*
 * Starship.cpp
 *
 *  Created on: 24-07-2013
 *      Author: michal
 */

#include "Sprites/Objects/Starship.h"
#include "Common/Resources.h"
#include "GameLevelScene.h"

Starship::Starship() :
		Box()
{
	currentState = 0;
	type = GAME_TYPE_STRARSHIP;
	direction = GameDirectionUnknown;
}

Starship::~Starship()
{
	// TODO Auto-generated destructor stub
}

void Starship::getKill()
{

}

bool Starship::pushed(GameDirection direction)
{

	if (GAMEUTILS->robboSprite->hasAllScrews()){
		nextLevel();
		return false;
	}
	
	return GameSprite::pushed(direction);

}

void Starship::nextLevel()
{
	if (currentState != -1)
	{
		
		//GAMEUTILS->removeObject(this);
		
		GAMEUTILS->robboSprite->currentState = -1;
		GAMEUTILS->reloadLevel(true);
		setState(-1);
	}
}

bool Starship::canBeMoved(GameDirection direction)
{
	CCLOG("STARSHIP CAN MOVE?");
	if (GAMEUTILS->robboSprite->hasAllScrews())return true;
	return GameSprite::canBeMoved(direction);
}
