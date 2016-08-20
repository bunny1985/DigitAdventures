/*
 * LaserMark.cpp
 *
 *  Created on: 23-07-2013
 *      Author: michal
 */

#include "Sprites/Bulets/LaserMark.h"
#include "Common/Enums.h"
#include "Common/Resources.h"
#include "Sprites/Enemies/Abstractenemy.h"

LaserMark::LaserMark() :
		GameSprite()
{
	currentState = 0;
	speed = 10;
	direction = GameDirectionUnknown;
	type = GAME_TYPE_BULLET;

}

LaserMark::~LaserMark()
{
	// TODO Auto-generated destructor stub
}

bool LaserMark::canBeMoved(GameDirection d)
{
	return true;
}

bool LaserMark::pushed(GameDirection d)
{
	return false;
}
void LaserMark::getKill(){
	stopAllActions();
	setState(-1);
	if (nextMark){
		nextMark->prevMark = NULL;
	}
	if (prevMark){
		prevMark->nextMark = NULL;
		prevMark->getKill();
	}
	
}

void LaserMark::rollIn()
{

	if (currentState == -1 || currentState == 1)
		return;
	currentState = 1;
	stopAllActions();
	if (parent){
	runAction(
			CCSequence::createWithTwoActions(CCFadeOut::create(1 / speed),
					CCCallFunc::create(this,
							callfunc_selector(LaserMark::onKill))));
	}
	else{
		stopAllActions();
		setState(-1);
	}
	if (prevMark){
		this->prevMark->parent = parent;
	}


}

void LaserMark::onKill()
{
	if (prevMark){
		this->prevMark->nextMark = NULL;
	}
	if (nextMark){
		this->nextMark->prevMark = NULL;
	}
	

	if (currentState != -1)
	{
		if (prevMark)
		{
			
			this->prevMark->rollIn();

		}
		else
		{
			if (parent){
				if (parent->getState() != -1)this->parent->setState(0);
			}
		}
	}
	currentState = -1;
}

void LaserMark::update()
{
//	if (parent->getState() == 0)
	//{
		//stopAllActions();
		//currentState = -1;
	//}
}

LaserMark* LaserMark::create(LaserMark* prevMark, GameSprite* parent)
{
	LaserMark *pobSprite = new LaserMark();
	pobSprite->currentState = 0;
	pobSprite->nextMark = NULL;
	if (prevMark){
		prevMark->nextMark = pobSprite;
		pobSprite->prevMark = prevMark;
	}
	else
	{
		pobSprite->prevMark = NULL;
	}
	
	pobSprite->parent = parent;
	pobSprite->direction = parent->getMoveDirection();
	pobSprite->setRotation(pobSprite->getRotationAngle());
	pobSprite->direction = GameDirectionUnknown;
	CCSpriteFrame *frame =
			CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(
					"laser_tail.png");
	if (pobSprite && pobSprite->initWithSpriteFrame(frame))
	{
		pobSprite->autorelease();
		return pobSprite;
	}

	CC_SAFE_DELETE(pobSprite);
	return NULL;
}
