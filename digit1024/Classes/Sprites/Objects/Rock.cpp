/*
 * Rock.cpp
 *
 *  Created on: Mar 26, 2014
 *      Author: Michal
 */

#include "Rock.h"
#include "GameLevelScene.h"
#include "SimpleAudioEngine.h"
#include "Common\RESPATH.h"

Rock::Rock() :
		Box() {
	setState(rockStateIdle);
	properities |= PFALLABLE;
	properities |= PPRESERVEPOINT;
	direction = GameDirectiondDown;
	type = GAME_TYPE_ROCK;
	speed = 0.23;


}

Rock::~Rock() {
	// TODO Auto-generated destructor stub
}

bool Rock::canBeMoved(GameDirection direction) {
	if (direction == GameDirectionUp) {
		return false;
	}
	if (getState() == rockStateRoling ) return false;
	if (getState() == BoxStateMoving ) return false;

	CCPoint point =
			GAMEUTILS->ccpTiledAdd(getTileMapPosition(), GAMEUTILS->getTiledVectorFromDirection(direction));
	GameSprite* obj = GAMEUTILS->objectAt(point, this);
	if (GAMEUTILS->isPointReserved(point))return false;

	if ((getState() == rockStateFalling ) && obj&& obj->properities & PSHOOTABLE ){
		return true;
	}
	

	return Box::canBeMoved(direction);
}

void Rock::makeMove(GameDirection direction){
	if (getState() == rockStateMoving) return;
	if (direction != GameDirectiondDown && canBeMoved(GameDirectiondDown)){
		fixPosition();
		startFalling(0);
		return;
	}
	Box::makeMove(direction);
}

bool Rock::pushed(GameDirection direction){
	if (getState() != rockStateIdle) return false;
	return Box::pushed(direction);
}
void Rock::update() {

	GameSprite* tmpobj =
		GAMEUTILS->objectAt(getTileMapPosition(), this);
	if (tmpobj&& tmpobj->properities & PSHOOTABLE && !(properities & PENTERABLE) && (getState() != (int) rockStateRoling) && (getState() != (int) rockStateMoving)) {
		tmpobj->getKill();
	}
	else{
		//fixPosition();
	}


	if (getState() != (int) rockStateIdle) {


		return;
	}

	GameSprite* obj =
			GAMEUTILS->objectAt(GAMEUTILS->ccpTiledAdd(getTileMapPosition(), GAMEUTILS->getTiledVectorFromDirection(GameDirectiondDown)), this);

	if (canBeMoved(GameDirectiondDown)) {

		if (!obj) {
			reservePoint();
			startFalling(0.1);
			return;
		}
		if (obj->getType() != GAME_TYPE_ROBBO) {
			reservePoint();
			startFalling(0.1);
		}
		return;
	}
	//na dole jest obiekt
	if (obj) {
		if (obj->properities & PFALLABLE) {
			//i jest on typu spadającego
			if (canBeMoved(GameDirectionLeft)) {
				CCPoint nextPoint =
						GAMEUTILS->ccpTiledAdd(getTileMapPosition(), GAMEUTILS->getTiledVectorFromDirection(GameDirectionLeft));
				CCPoint position = getTileMapPosition();
					setPosition(GAMEUTILS->getScenePoint( nextPoint));
					if(!canBeMoved(GameDirectiondDown)){
						setPosition(GAMEUTILS->getScenePoint(position));

					}else{
						setPosition(GAMEUTILS->getScenePoint(position));
						
						startRolling(GameDirectionLeft);
						return;
					}
			}
			if (canBeMoved(GameDirectionRigh)) {
				CCPoint nextPoint =
						GAMEUTILS->ccpTiledAdd(getTileMapPosition(), GAMEUTILS->getTiledVectorFromDirection(GameDirectionRigh));
				CCPoint position = getTileMapPosition();
					setPosition(GAMEUTILS->getScenePoint( nextPoint));
					if(!canBeMoved(GameDirectiondDown)){
						setPosition(GAMEUTILS->getScenePoint(position));

					}else{
						setPosition(GAMEUTILS->getScenePoint(position));
						startRolling(GameDirectionRigh);
						return;
					}
			}
		}
	}
	if (getState() != rockStateIdle) {
		if (obj) {
			if (obj->properities & PSHOOTABLE) {
				obj->getKill();
			}
		}
	}
	fixPosition();
	setState((int) rockStateIdle);
}

void Rock::startFalling(float delay) {
	direction = GameDirectiondDown;
	reservePoint();
	setState((int) rockStateFalling);
	CCPoint nextPoint = GAMEUTILS->ccpTiledAdd(getTileMapPosition(), ccp(0,-1));

	runAction(
			CCSequence::create(
					CCSpawn::createWithTwoActions(
							CCMoveTo::create(getSpeed(),
									GAMEUTILS->getScenePoint( nextPoint) ),CCRotateBy::create(getSpeed() , 180 ) )
									, CCCallFunc::create(this, callfunc_selector(Rock::stopFalling)), NULL
									)
									);

}


void Rock::stopFalling() {
	releasePoint();

	GameSprite* obj =
 		GAMEUTILS->objectAt(GAMEUTILS->ccpTiledAdd(getTileMapPosition(), GAMEUTILS->getTiledVectorFromDirection(GameDirectiondDown)), this);
	if (!obj){
		setState((int) rockStateIdle);
		if (GAMEUTILS->isWallPresent(GAMEUTILS->ccpTiledAdd(getTileMapPosition(), GAMEUTILS->getTiledVectorFromDirection(GameDirectiondDown)))){
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(respatchFix("Sounds/crack" SOUND_EXT).c_str());
		}
		

	return;
	}
	if ((obj->properities & PSHOOTABLE)
			&& obj->getType() != GAME_TYPE_ENTERABLEGROUND) {

		obj->getKill();
		setState((int) rockStateIdle);

	}

	if (canBeMoved(GameDirectiondDown)) {

			startFalling(0.0);

		return;
	}else{
		setState((int) rockStateIdle);
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(respatchFix("Sounds/crack" SOUND_EXT).c_str());
		return;
	}


	

}

void Rock::startRolling(GameDirection direction) {
	if (!canBeMoved(direction)) return;
	
	CCPoint nextPoint =
			GAMEUTILS->ccpTiledAdd(getTileMapPosition(), GAMEUTILS->getTiledVectorFromDirection(direction));
		setState(rockStateRoling);
		this->direction = direction;
		
		reservePoint();

	runAction(
			CCSequence::createWithTwoActions(
					CCSpawn::createWithTwoActions(
							CCMoveTo::create(getSpeed(),
									GAMEUTILS->getScenePoint( nextPoint) ),CCRotateBy::create(getSpeed() , 90 ) )
									, CCCallFunc::create(this, callfunc_selector(Rock::stopRolling))
									)

									);
	reservePoint();
}

void Rock::stopRolling() {
	setState((int) rockStateIdle);
	releasePoint();
}
