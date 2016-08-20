/*
 * TwoDirectionsEnemy.cpp
 *
 *  Created on: 19-07-2013
 *      Author: michal
 */

#include "Sprites/Enemies/TwoDirectionsEnemy.h"
#include "GameLevelScene.h"

TwoDirectionsEnemy::TwoDirectionsEnemy() :
		AbstractEnemy()
{
	
	direction = GameDirectionUnknown;
	lastDirection = direction;
	enemeyproperities|=PEMOVING;
	runAction(CCRepeatForever::create(CCSequence::create(CCSkewBy::create(0.3f ,10.0f , 0.1f )  ,CCSkewBy::create(0.3f ,-10.0f , -0.1f ), NULL )));
}

TwoDirectionsEnemy::~TwoDirectionsEnemy()
{
	// TODO Auto-generated destructor stub
}

GameDirection TwoDirectionsEnemy::pickDirection()
{
	if (direction == GameDirectionUnknown)
		direction = lastDirection;
	if (canBeMoved(direction))
	{
		lastDirection = direction;
		return direction;
	}

	GameDirection oposite = GAMEUTILS->getOpositeDirection(direction);

	if (canBeMoved(oposite))
	{
		direction = oposite; 

		runAction(CCRotateTo::create(0.15, (int) direction * 90));
		
		return oposite;
	}
	return GameDirectionUnknown;
}

void TwoDirectionsEnemy::setDirection(GameDirection direction)
{
	this->direction = direction;
}
