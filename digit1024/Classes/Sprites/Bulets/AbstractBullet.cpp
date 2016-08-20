/*
 * AbstractBullet.cpp
 *
 *  Created on: 21-07-2013
 *      Author: michal
 */

#include "Sprites/Bulets/AbstractBullet.h"
#include "Common/Resources.h"
#include "GameLevelScene.h"
#include "cocos2d.h"

AbstractBullet::AbstractBullet() :
		GameSprite()
{
	speed = 0.17;
	type = GAME_TYPE_BULLET;
}

AbstractBullet::~AbstractBullet()
{
	// TODO Auto-generated destructor stub
}

void AbstractBullet::hit(GameDirection hitDirection, GameSprite* object)
{
	if (!object)return;
	if (currentState == -1)
		return;
	if (object->getType() == GAME_TYPE_ROBBO
		|| object->getType() == GAME_TYPE_QUESTIONMARK || object->getType() == GAME_TYPE_BULLET)
	{
		object->getKill();
	}
	else if (object->getType() == GAME_TYPE_ENEMY)
	{
		object->hit(direction, this);
		
	}
	getKill();
}

bool AbstractBullet::pushed(GameDirection)
{
	return false;
}

bool AbstractBullet::canBeMoved(GameDirection direction)
{
	if (GAMEUTILS->isWallPresent(getTileMapPosition()))return false;
	return true;
}
void AbstractBullet::startShoot(GameDirection direction)
{
	this->direction = direction;
	makeMove();

}

void AbstractBullet::makeMove()
{
	if (!canBeMoved(direction))
		return;
	CCPoint vector = GAMEUTILS->getTiledVectorFromDirection(direction);

	moveSequence = CCSequence::createWithTwoActions(
			CCMoveBy::create(speed, GAMEUTILS->getSceneVector(vector) ),
	CCCallFunc::create(this, callfunc_selector(AbstractBullet::makeMove))
	);
	setRotation(getRotationAngle());
	runAction(moveSequence);

}

void AbstractBullet::update()
{
	if (currentState == -1)
		return;

	GameSprite* obj = GAMEUTILS->objectAt(getTileMapPosition() , this);
	if (obj)
	{
		//this->hit(direction, obj);
		obj->hit(direction, this);

		getKill();

	}
	if (!canBeMoved(direction))
	{

		getKill();

	}
}
