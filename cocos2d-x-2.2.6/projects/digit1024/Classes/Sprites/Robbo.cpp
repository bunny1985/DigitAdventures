/*
 * Robbo.cpp
 *
 *  Created on: 16-07-2013
 *      Author: michal
 */

#include "Sprites/Robbo.h"
#include "Common/Resources.h"
#include "GameLevelScene.h"
#include "SimpleAudioEngine.h"
#include "Sprites/Bulets/BasicBullet.h"
#include "Sprites/Objects/Collectable.h"

#include "Common/RESPATH.h"

Robbo::~Robbo()
{
	delete animate;
}

void Robbo::makeMove(GameDirection direction)
{

	if (GAMEUTILS->current_state != 2){//2 = running
		return;
	}


	direction = GAMEUTILS->validateDirection(direction);
	if (direction != GameDirectionUnknown)
	{
		this->direction = direction;
	}
	if(movesequenceStarted) return;

	releasePoint();
	// Jeżeli nastepuje zmiana strony to tylko się odwróć
	if( direction != prevDirection)
	{
		movesequenceStarted = true;
		prevDirection = direction;
		moveSequence =
		CCSequence::createWithTwoActions(
				CCDelayTime::create(speed/5),
				CCCallFunc::create(this, callfunc_selector(Robbo::makeMove))
		);

	}
	else
	{ // inaczej spróbuj wykonac rucfh

		//sprawdzamy czy istniałaby możliwość ruychu - niezależnie od stanu; jesli nie to return
		if (!this->couldMove(direction))
		{

			setState(ObjectStateIdle);
			_stopMoving = false;
			movesequenceStarted = false;
			return;
		}
		setState(RobboStateMoving);
		GameSprite* object = GAMEUTILS->objectAt(getTileMapNextPosition() ,this);
		if (object != NULL)
		{
			CCLOG("OBJECT DETECTED");
			object->hit(this->direction, this);
			if(! object->pushed(this->direction))
			{
				stopMoving();
				return;
			}
		}
		this->reservedPoint = getTileMapNextPosition();
		moveSequence =
		CCSequence::createWithTwoActions(
				CCMoveBy::create( speed,
						GAMEUTILS->getSceneVector(GAMEUTILS->getTiledVectorFromDirection(direction))),
				CCCallFunc::create(this, callfunc_selector(Robbo::makeMove))
		);

		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(respatchFix("Sounds/walk" SOUND_EXT).c_str());

	}
	this->currentState = RobboStateMoving;
	movesequenceStarted =true;
	runAction(moveSequence);
	_stopMoving =false;
}

void Robbo::getKill()
{
	if (currentState == (-1))
		return;
	currentState = -1;

	lives--;

	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(respatchFix(
			"Sounds/end" SOUND_EXT).c_str());
	//GAMEUTILS->objects.removeObject(this);
//	GAMEUTILS->removeObject(this);


	runAction(CCFadeOut::create(0.5));
	runAction(
			CCSequence::createWithTwoActions(CCScaleTo::create(0.5f , 3),
					CCCallFunc::create(this,
					callfunc_selector(Robbo::onGetKill))));
	GAMEUTILS->updateColletcable(lives, screws , shoots, keys);

}

int Robbo::lives = 0;

void Robbo::shoot()
{
	GameSprite* obj = GAMEUTILS->objectAt(getTileMapNextPosition(), this);
	if (obj && obj->getType() == GAME_TYPE_BULLET){
		return;
	}

	if (shoots > 0)
	{
		shoots--;
		BasicBullet* bulet = BasicBullet::create();

		currentState = RobboStateShooting;
		bulet->setPosition(GAMEUTILS->getScenePoint(getTileMapNextPosition()));
		bulet->startShoot(direction);
		GAMEUTILS->addObject(bulet);
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(respatchFix(
				"Sounds/shoot"SOUND_EXT).c_str());
		currentState = RobboStateIdle;
	}

	GAMEUTILS->updateColletcable(lives, screws , shoots, keys);

}

bool Robbo::OpenDoor()
{
	if (keys > 0)
	{
		keys--;
		GAMEUTILS->updateColletcable(lives, screws , shoots, keys);
		return true;
	}
	else
	{
		stopMoving();
		stopAllActions();
		fixPosition();
		return false;
	}
}

bool Robbo::hasKey()
{
	return keys > 0;
}

void Robbo::getColectable(Collectable* object)
{
	switch (object->getCollectableType())
	{
	case GAME_TYPE_CollectableTYPE_KEY:
		keys++;
		break;
	case GAME_TYPE_CollectableTYPE_AMMO:
		shoots += object->getCollectableQuantity();
		break;
	case GAME_TYPE_CollectableTYPE_SCREW:
		screws++;
		break;
	default:
		break;
	}
	GAMEUTILS->updateColletcable(lives, screws , shoots, keys);
}

void Robbo::onGetKill()
{
	//TODO Wcześniej następował reload sceny, ale w obecnej chwili to ma być zamienione na

	GAMEUTILS->reloadLevel();
}

bool Robbo::hasAllScrews()
{
	return screws >= GAMEUTILS->TotalScrews;
}

bool Robbo::couldMove(GameDirection d)
{
	int prev = currentState;
	currentState = RobboStateIdle;
	bool can = canBeMoved(d);
	currentState = prev;
	return can;
}

void Robbo::endMove()
{
	setState(ObjectStateIdle);
	_stopMoving = false;
	movesequenceStarted = false;
}

void Robbo::makeMove()
{
	movesequenceStarted = false;
	if (_stopMoving)
	{
		endMove();
	}
	else
	{

		makeMove(direction);
	}
}

void Robbo::stopMoving()
{
	_stopMoving = true;
}

bool Robbo::canBeMoved(GameDirection direction)
{

	// Jesli nie ma ściany , lub obiektu to wszystko jest po staremu - można sie poruszać
	if (GameSprite::canBeMoved(direction))
		return true;

	CCPoint currentPos = getTileMapPosition();
	CCPoint vector = GAMEUTILS->getTiledVectorFromDirection(direction);
	CCPoint point = ccp(currentPos.x + vector.x , currentPos.y - vector.y);
	//ale jesli jest obiekt to jeszcze istnieje szansca że będzie go można popchnąć , lub wejść na niego , lub zebrać
	GameSprite* object = GAMEUTILS->objectAt(point,this );
	// jesli nie ma obiektu to jest ściana wiec false;
	if (!object)
		return false;
	// obiekt można popchnąć
	if (object->properities & PPUSHABLE)
	{
		return object->canBeMoved(direction);
	}
	// jeśli da się zebrać lub wejść to luz - to idziemy
	return object->properities & (PENTERABLE | PCOLLECTABLE);
}

CCAnimation* Robbo::getAnimation(RobboStates state, GameDirection direction)
{
	CCAnimation *animation = CCAnimation::create();

	if (state == RobboStateMoving)
	{
		if (direction != GameDirectionUnknown)
		{
			for (int i = 0; i < GAME_CONSTS_ROBBO_moving_animation_length; i++)
			{

				CCString *fstring = CCString::createWithFormat(
						movingFramesMap[(int) direction], i);
				animation->addSpriteFrame(
						CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(
								fstring->getCString()));
			}
		}
	}
	else
	{

	}
	animation->setDelayPerUnit(1.0f / GAME_CONSTS_ROBBO_moving_animation_speed);
	animation->setRestoreOriginalFrame(false);

	return animation;

}

void Robbo::update()
{

}

void Robbo::hit(GameDirection hitDirection, GameSprite* object)
{
	if (object->getType() == GAME_TYPE_BULLET
			|| object->getType() == GAME_TYPE_ENEMY)
	{
		getKill();
	}

}

Robbo::Robbo() :
		GameSprite()
{
	;
	properities |= PPUSHABLE;
	properities |= PSHOOTABLE;
	properities |= PPRESERVEPOINT;
	animate = new CCAnimate();
	;
	moveSequence = NULL;

	prevDirection = GameDirectionUnknown;
	_hit = false;
	_stopMoving = false;
	shoots = 0;
	keys = 0;
	screws = 0;
	movesequenceStarted = false;
	this->speed = 0.15;
	type = GAME_TYPE_ROBBO;
	this->currentState = RobboStateIdle;
	direction = GameDirectiondDown;
	fixPosition_ = CCMoveBy::create(0.01, ccp(0,0));

	movingFramesMap[GameDirectionLeft] = GRAPHICS_ROBBO_go_left;
	movingFramesMap[GameDirectionRigh] = GRAPHICS_ROBBO_go_right;
	movingFramesMap[GameDirectionUp] = GRAPHICS_ROBBO_go_up;
	movingFramesMap[GameDirectiondDown] = GRAPHICS_ROBBO_go_down;

	animations[(int) GameDirectionLeft] = getAnimation(RobboStateMoving,
			GameDirectionLeft);
	animations[(int) GameDirectionRigh] = getAnimation(RobboStateMoving,
			GameDirectionRigh);
	animations[(int) GameDirectionUp] = getAnimation(RobboStateMoving,
			GameDirectionUp);
	animations[(int) GameDirectiondDown] = getAnimation(RobboStateMoving,
			GameDirectiondDown);


	stateObservers.push_back(&animationObserver);
}

Robbo::MoveAnimationObserver::MoveAnimationObserver()
{

}

void Robbo::MoveAnimationObserver::notify(GameObjectEvent gameObjectEvent)
{
	if (gameObjectEvent.caller->getState() != ObjectStateMoving)
		return;

	Robbo* robbo = ((Robbo*) gameObjectEvent.caller);
	if (robbo->animate->getAnimation() != NULL)
	{
		robbo->animate->stop();
	}
	robbo->animate->release();
	robbo->animate = new CCAnimate();


	robbo->animate->initWithAnimation(
			robbo->getAnimation((RobboStates) robbo->getState(),
					robbo->getMoveDirection()));
	robbo->runAction(robbo->animate);

}

void Robbo::setDirection(GameDirection direction){
	this->direction = direction;
}
