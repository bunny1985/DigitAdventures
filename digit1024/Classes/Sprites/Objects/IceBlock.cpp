/*
 * Box.cpp
 *
 *  Created on: 17-07-2013
 *      Author: michal
 */

#include "Sprites/Objects/IceBlock.h"
#include "Common/Resources.h"
#include "GameLevelScene.h"
#include "SimpleAudioEngine.h"
#include "Common\RESPATH.h"

bool IceBlock::pushed(GameDirection d){
	bool r = GameSprite::pushed(d);
	if (r){
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(respatchFix("Sounds/ice" SOUND_EXT).c_str());
	}
	return r;
}


IceBlock::IceBlock() :
Box()
{
	speed = 0.1;
	properities &= ~PPRESERVEPOINT;
}

IceBlock::~IceBlock()
{
	// TODO Auto-generated destructor stub
}

void IceBlock::endMove()
{
	if (getState() == BoxStateIdle)return;
	type = GAME_TYPE_BULLET;
	properities &= ~PPUSHABLE;
	setState(BoxStateIdle);
	makeMove(direction);



}
bool IceBlock::canBeMoved(GameDirection direction){
	if (type == GAME_TYPE_BOX)return Box::canBeMoved(direction);
	CCPoint currentPos = getTileMapPosition();
	CCPoint vector = GAMEUTILS->getTiledVectorFromDirection(direction);
	CCPoint point = ccp(currentPos.x + vector.x, currentPos.y - vector.y);
	// Jest �ciana
	if (GAMEUTILS->isWallPresent(point)) return false;
	GameSprite* obj = GAMEUTILS->objectAt(point, this);
	if (!obj || obj->getType() == GAME_TYPE_ENEMY){
		return true;
	}
	return false;
}

void IceBlock::makeMove(GameDirection direction){
	if (getState() == BoxStateMoving) return;
	CCPoint currentPos = getTileMapPosition();
	CCPoint vector = GAMEUTILS->getTiledVectorFromDirection(direction);
	CCPoint point = ccp(currentPos.x + vector.x, currentPos.y - vector.y);
	// Jest �ciana
	if (GAMEUTILS->isWallPresent(point)){
		stopMoving();
		type = GAME_TYPE_BOX;
		properities |= PPUSHABLE;
	}
	GameSprite* obj = GAMEUTILS->objectAt(point, this);
	if (obj ){

		if ((obj->properities & PSHOOTABLE) && type == GAME_TYPE_BULLET){
			obj->getKill();
		}

		//this->hit(direction, obj);

		stopMoving();
		//fixPosition();
		type = GAME_TYPE_BOX;
		properities |= PPUSHABLE;
	}
	else{
		setState(BoxStateMoving);
		GameSprite::makeMove(direction);
		this->direction = direction;
	}



}

void IceBlock::update(){
	if (currentState == -1)
		return;
	if (type == GAME_TYPE_BOX)return;

	GameSprite* obj = GAMEUTILS->objectAt(getTileMapPosition(), this);
	if (obj&& obj->properities & PSHOOTABLE)
	{
		//this->hit(direction, obj);

		obj->getKill();


		stopMoving();
		//fixPosition();
		type = GAME_TYPE_BOX;
		properities |= PPUSHABLE;
	}

}

void IceBlock::hit(GameDirection hitDirection, GameSprite *object){
	if (!object)return;
	if (type == GAME_TYPE_BOX){
		Box::hit(hitDirection, object);
		return;
	}
	if (currentState == -1)
		return;
	if (object->getType() == GAME_TYPE_ROBBO
		|| object->getType() == GAME_TYPE_QUESTIONMARK || object->getType() == GAME_TYPE_BULLET)
	{
		object->getKill();
	}
	else if (object->properities & PSHOOTABLE)
	{

		object->getKill();


		stopMoving();
		//fixPosition();

	}

}
void IceBlock::fixPosition(){
	setPosition(GAMEUTILS->getScenePoint(getTileMapPosition()));
}
void IceBlock::stopMoving(){
	GameSprite::stopMoving();
	type = GAME_TYPE_BOX;
	properities |= PPUSHABLE;
}
