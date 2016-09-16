/*
 * OneDirectionEnemy.cpp
 *
 *  Created on: 19-07-2013
 *      Author: michal
 */

#include "Sprites/Enemies/Abstractenemy.h"
#include "Common/Resources.h"
#include "Common/Enums.h"
#include "Sprites/Bulets/BasicBullet.h"
#include "Sprites/Objects/Box.h"
#include "GameLevelScene.h"
#include  <stdlib.h>
#include "SimpleAudioEngine.h"

AbstractEnemy::AbstractEnemy() :
		GameSprite()
{
	type = GAME_TYPE_ENEMY;
	properities |= PSHOOTABLE;
	properities |= PPUSHABLE;
	properities |= PENTERABLE;
	speed = 0.20;
	shootFrequency = 0;
	shootDirTurn = 0;
	shotingDirection = GameDirectionUnknown;
	changeMoveDirFrequency = 0;
	changeShootDirFrequecny = 0;
	enemeyproperities = 0;
	lastPosition = ccp(0, 0);
}

AbstractEnemy::~AbstractEnemy()
{

}

bool AbstractEnemy::canBeMoved(GameDirection direction)
{

	CCPoint currentPos = getTileMapPosition();
	CCPoint vector = GAMEUTILS->getTiledVectorFromDirection(direction);
	CCPoint point = ccp(currentPos.x + vector.x , currentPos.y - vector.y);
	//if (GAMEUTILS->isPointReserved(point)||GAMEUTILS->isPointReserved(getTileMapPosition()))return false;
	// Jest Ściana
	if (GAMEUTILS->isWallPresent(point) )
	{
		return false;
	}

	GameSprite* object = GAMEUTILS->objectAt(point , this );
	if (object != NULL && (object->getType() != GAME_TYPE_BULLET || object->getType() != GAME_TYPE_ROBBO))
		return false;
	return true;
}
void AbstractEnemy::hit(GameDirection hitDirection, GameSprite* object){
	GameSprite::hit(hitDirection, object);
	if (object->getType() != GAME_TYPE_ROBBO){
		fixPosition();
	}

}


bool AbstractEnemy::pushed(GameDirection direction)
{
	if ((properities & PENTERABLE) > 0)
	{
		return true;
	}
	else
	{
		return false;
	}

}

void AbstractEnemy::fixPosition()
{
	if (lastPosition.x == 0 && lastPosition.y == 0)return;
	GameSprite* obj = GAMEUTILS->objectAt(getTileMapPosition(), this);
	if (obj && obj->getType() == GAME_TYPE_BULLET)return;
	if(obj|| GAMEUTILS->isPointReserved(getTileMapPosition()) )
	{


		if(obj && obj->getType()==GAME_TYPE_BULLET)return;

		stopAllActions();
		setPosition(GAMEUTILS->getScenePoint(lastPosition));

		pickDirection();
		//direction = GameDirectionUnknown;
		//makeMove(GameDirectionUnknown);
		setState(EnemyStateIdle);
		GAMEUTILS->updateObjectsMap();
	}
	else
	{
		touchTest();
	}
}

void AbstractEnemy::makeMove(GameDirection direction)
{
	lastPosition = getTileMapPosition();
	if (direction == GameDirectionUnknown)
	{

		setDirection(pickDirection());
	}
	if(canBeMoved(direction)){
		GameSprite::makeMove(this->direction);
	}
	else
	{
		//setDirection(GameDirectionUnknown);
		setState(EnemyStateIdle);


	}
}

void AbstractEnemy::endMove()
{
	makeMove(GameDirectionUnknown);
}

void AbstractEnemy::setDirection(GameDirection direction)
{
	this->direction = direction;
}

void AbstractEnemy::startMoving()
{
	if((PEMOVING & enemeyproperities) >0){
		if (direction == GameDirectionUnknown){
			setDirection(pickDirection());
		}
		makeMove(direction);
	}
}

void AbstractEnemy::stopMoving()
{
	endMove();
}

void AbstractEnemy::update()
{

	if (enemeyproperities & PEMOVING)
	{
		fixPosition();
		if (currentState == EnemyStateIdle || direction== GameDirectionUnknown){
			stopAllActions();
			startMoving();
		}
	}

	if (enemeyproperities & PESHOOTING)
	{
		changeShootingDirection();
		shoot();
	}
}

void AbstractEnemy::shoot()
{


	if (float(std::rand() % 100) <= shootFrequency)
	{

		CCPoint v = GAMEUTILS->getTiledVectorFromDirection(shotingDirection);
		v = GAMEUTILS->ccpTiledAdd( getTileMapPosition(), v );

		BasicBullet *bullet = BasicBullet::create();
		bullet->setPosition(GAMEUTILS->getScenePoint(v));
		bullet->startShoot(shotingDirection);
		if (!isShootPosssible(v))return;
		CCLog("SHOOTING ENEMY. Able to shoot");
		GAMEUTILS->addObject(bullet);
	/*	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(
				"Sounds/shoot" SOUND_EXT);*/
	}
}
bool AbstractEnemy::isShootPosssible(CCPoint point){
	if (GAMEUTILS->isWallPresent(point)) return false;
	GameSprite* tmpobj = GAMEUTILS->objectAt(point, this);
	if (!tmpobj || tmpobj->getType() != GAME_TYPE_BULLET){
		return true;
	}
	return false;

}



void AbstractEnemy::changeShootingDirectionRandom()
{
	if (enemeyproperities & PECHNGSHOOTDIR)
	{
		if (std::rand() % 100 <= changeShootDirFrequecny)
		{
			shotingDirection = (GameDirection) (std::rand() % 4);
		}
	}
}

void AbstractEnemy::changeShootingDirection()
{
	if ((enemeyproperities & PECHNGSHOOTDIRRANDOM))
	{
		changeShootingDirectionRandom();
	}
	else
	{
		shotingDirection = (GameDirection)(((int)shotingDirection  + shootDirTurn)%4);
	}
}

void AbstractEnemy::touchTest()
{
	for (int x = 0; x < 4; x++)
	{
		CCPoint vector = GAMEUTILS->getTiledVectorFromDirection((GameDirection)x);
		GameSprite* object =GAMEUTILS->objectAt(getTileMapPosition(), this);
		if(object)continue;
		object =GAMEUTILS->objectAt(GAMEUTILS->ccpTiledAdd(getTileMapPosition() , vector) , this);
		if(object){
		if(object->getType()==GAME_TYPE_ROBBO){
			static_cast<Robbo*>(object)->getKill();
		}}

	}
}

float AbstractEnemy::getChangeMoveDirFrequency() const
{
	return changeMoveDirFrequency;
}

void AbstractEnemy::setChangeMoveDirFrequency(float changeMoveDirFrequency)
{
	this->changeMoveDirFrequency = changeMoveDirFrequency;
}

float AbstractEnemy::getChangeShootDirFrequecny() const
{
	return changeShootDirFrequecny;
}

void AbstractEnemy::setChangeShootDirFrequecny(float changeShootDirFrequecny)
{
	this->changeShootDirFrequecny = changeShootDirFrequecny;
}

int AbstractEnemy::getShootDirTurn() const
{
	return shootDirTurn;
}

void AbstractEnemy::setShootDirTurn(int shootDirTurn)
{
	this->shootDirTurn = shootDirTurn;
}

float AbstractEnemy::getShootFrequency() const
{
	return shootFrequency;
}

void AbstractEnemy::setShootFrequency(float shootFrequency)
{
	this->shootFrequency = shootFrequency;
}

GameDirection AbstractEnemy::getShotingDirection() const
{
	return shotingDirection;
}

void AbstractEnemy::setShotingDirection(GameDirection shotingDirection)
{
	this->shotingDirection = shotingDirection;
}
