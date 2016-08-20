/*
 * GameSprite.cpp
 *
 *  Created on: 16-07-2013
 *      Author: michal
 */

#include "Sprites/GameSprite.h"
#include "GameLevelScene.h"
#include "Sprites/AbstractStateObserver.h"
#include "Common/Resources.h"

GameDirection GameSprite::getMoveDirection()
{
	return direction;
}

void GameSprite::applyProperties(CCDictionary* dictionary){

}

float GameSprite::getSpeed()
{
	return speed;
}

int GameSprite::getState()
{
	return currentState;
}

CCPoint GameSprite::getTileMapPosition()
{
	return GAMEUTILS->getTiledPoint(this->getPosition());

}

CCPoint GameSprite::getTileMapNextPosition()
{
	if (currentState == 0)
		return getTileMapPosition();
	CCPoint p = getTileMapPosition();
	direction = GAMEUTILS->validateDirection(direction);
	if (direction == GameDirectionUnknown)
	{

		return p;
	}
	return GAMEUTILS->ccpTiledAdd(getTileMapPosition() , GAMEUTILS->getTiledVectorFromDirection(direction));
}

GameSprite::~GameSprite()
{
}

/**
 * obiekt aby móc być przepchanym musi być bezczynny , oraz pole na które ma byc popchniety ma byc puste
 */
bool GameSprite::canBeMoved(GameDirection direction)
{

	if ((properities & PPUSHABLE))
	{
		CCPoint currentPos = getTileMapPosition();
		CCPoint vector = GAMEUTILS->getTiledVectorFromDirection(direction);
		CCPoint point = ccp(currentPos.x + vector.x , currentPos.y - vector.y);
		// Jest Ściana
		if (GAMEUTILS->isWallPresent(point) ) return false;
		GameSprite* object = GAMEUTILS->objectAt(point,this );
		// Nie ma innego obiektu
		if (object != NULL)
		{
			return false;
		}
		return true;
	}
	else
	{
		return false;
	}
	return false;
}

/**
 * Funkcja Wywoływana przy updejcie planszy. Słowem bardzo często
 */
void GameSprite::update()
{

}

/**
 * przesuwanie obiektu jeśli nastapiło najechanie jednego obiek tu na drugi
 */
void GameSprite::fixPosition()
{
	GameSprite* obj = GAMEUTILS->objectAt(getTileMapPosition(), this);
	if(obj)
	{
		GameDirection d= GAMEUTILS->getOpositeDirection(direction);
		direction = d;
		setPosition(GAMEUTILS->getScenePoint(getTileMapNextPosition()));
		direction= GAMEUTILS->getOpositeDirection(direction);
	}
}

/**
 * Domyślna implementacja. Zmienić stan, zatrzymać wszelkie akcjie i pokazać dymek
 */
void GameSprite::getKill()
{

	stopAllActions();
	setState(-1);
}

bool GameSprite::isDestroyed()
{
	return currentState == -1;
}

GameSprite::GameSprite()
{
	direction = GameDirectionUnknown;
	speed = 0.17;
	type = -1;
	currentState = 0;
	properities = 0; // nie ma ustawionych ustawień;

}
/**
 * jeśli może być ruszony i uda sie ruszyć to ok.
 */
bool GameSprite::pushed(GameDirection direction)
{
	if ((properities & PENTERABLE) > 0)
		return true;
	if (!canBeMoved(direction))
		return false;
	makeMove(direction);

	return true;
}

bool GameSprite::entered(GameDirection direction)
{
	return properities & PENTERABLE;
}

bool GameSprite::collected(GameDirection direction)
{
	return properities & PCOLLECTABLE;
}

bool GameSprite::getShoot(GameDirection direction)
{
	return properities & PSHOOTABLE;
}

float GameSprite::getRotationAngle()
{
	switch (direction)
	{
	case GameDirectionUp:
		return 0.0;
		break;
	case GameDirectiondDown:
		return 180.0;
		break;
	case GameDirectionLeft:
		return 270.0;
		break;
	case GameDirectionRigh:
		return 90.0;
		break;
	default:
		return 0.0;
		break;
	}
	return 0.0;
}

void GameSprite::makeMove(GameDirection enumGameDirection)
{
	if (!canBeMoved(enumGameDirection)){
		setState(0);
		return;
	}

	currentState = ObjectStateMoving;


	reservePoint();
	runAction(CCSequence::createWithTwoActions(CCMoveBy::create(getSpeed(),
	GAMEUTILS->getSceneVector(GAMEUTILS->getTiledVectorFromDirection(enumGameDirection))),
	CCCallFunc::create(this, callfunc_selector(GameSprite::endMove)) ));
}

void GameSprite::endMove()
{
	releasePoint();
	setState(ObjectStateIdle);
}

void GameSprite::setState(int newState)
{
	for (std::vector<AbstractStateObserver*>::iterator it =
			stateObservers.begin(); it != stateObservers.end(); ++it)
	{
		(*it)->notify(GameObjectEvent(this));
	}
	currentState = newState;

}

void GameSprite::stopMoving()
{
	releasePoint();
	setState(ObjectStateIdle);
}

void GameSprite::releasePoint()
{
	reservedPoint = ccp(0,0);
}

GameSprite* GameSprite::postCreate(const char* framename)
{
	CCSpriteFrame *frame =
			CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(
					framename);
	if (this->initWithSpriteFrame(frame))
	{
		this->autorelease();
		return this;
	}
	return NULL;
}

void GameSprite::hit(GameDirection hitDirection, GameSprite* object)
{

 	if (object->getType() == GAME_TYPE_BULLET && ((properities & PSHOOTABLE) > 0) )
	{
		getKill();
	}

}

const CCPoint&
GameSprite::getReservedPoint() const
{
	return reservedPoint;
}

void GameSprite::reservePoint()
{
	if ((properities & PPRESERVEPOINT) > 0)
	{
		this->reservedPoint = getTileMapNextPosition();
	}
}
