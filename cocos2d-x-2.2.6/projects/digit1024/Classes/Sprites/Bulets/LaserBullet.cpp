/*
 * LaserBullet.cpp
 *
 *  Created on: 23-07-2013
 *      Author: michal
 */

#include "LaserBullet.h"
#include "GameLevelScene.h"
#include "Sprites/Objects/Box.h"
#include "Sprites/Enemies/Abstractenemy.h"
#include "Sprites/Enemies/StaticLaserCannon.h"

#include "Common/Resources.h"

LaserBullet::LaserBullet() :
		BasicBullet()
{
	parent = NULL;
	this->currentState = 0;
	direction = GameDirectionUnknown;
	type = GAME_TYPE_BULLET;
	lastMark = NULL;

}

LaserBullet::~LaserBullet()
{
	// TODO Auto-generated destructor stub
}

void LaserBullet::makeMove()
{
	CCPoint vector = GAMEUTILS->getTiledVectorFromDirection(direction);

	moveSequence = CCSequence::createWithTwoActions(CCMoveBy::create(speed, GAMEUTILS->getSceneVector(vector) ),

			CCCallFunc::create(this, callfunc_selector(LaserBullet::continueMove))
	);
	setRotation(getRotationAngle());
	runAction(moveSequence);

}

void LaserBullet::continueMove()
{
	LaserMark* m = LaserMark::create(lastMark, parent);
	CCPoint oposite = GAMEUTILS->getTiledVectorFromDirection(GAMEUTILS->getOpositeDirection(direction));
	m->setPosition(GAMEUTILS->getScenePoint(GAMEUTILS->ccpTiledAdd( getTileMapPosition() ,oposite)));

	GAMEUTILS->addObject(m);
	lastMark = m;
	makeMove();
}

void LaserBullet::getKill()
{
	if (currentState >= 0)
	{
		((StaticLaserCannon*)this->parent)->bullet = NULL;
		if (lastMark)
		{
			this->lastMark->rollIn();
			this->lastMark->parent = parent;


		}
		else
		{
			if(parent->getState()!=-1)this->parent->setState(0);

		}
	}
	currentState = -1;
}

LaserBullet* LaserBullet::create(GameSprite* parent)
{
	LaserBullet *pobSprite = new LaserBullet();
	pobSprite->currentState = 0;
	pobSprite->parent = parent;
	CCSpriteFrame *frame =
			CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(
					"laser.png");
	if (pobSprite && pobSprite->initWithSpriteFrame(frame))
	{
		pobSprite->autorelease();
		return pobSprite;
	}

	CC_SAFE_DELETE(pobSprite);
	return NULL;
}
