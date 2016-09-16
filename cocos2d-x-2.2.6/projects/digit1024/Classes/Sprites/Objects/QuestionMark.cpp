/*
 * QuestionMark.cpp
 *
 *  Created on: 24-07-2013
 *      Author: michal
 */

#include "Sprites/Objects/QuestionMark.h"
#include "Common/Enums.h"
#include "Common/Resources.h"
#include "GameLevelScene.h"
#include "ObjectsFactory.h"

QuestionMark::QuestionMark() :
		Box()
{
	currentState = 0;
	direction = GameDirectionUnknown;
	type = GAME_TYPE_QUESTIONMARK;
	speed = 0;

}

QuestionMark::~QuestionMark()
{

}

void QuestionMark::getKill()
{

	if (currentState == (-1))
		return;
	stopAllActions();

	ObjectsFactory o;
	CCDictionary d;
	d.setObject(CCString::createWithFormat("%i", (int) getPositionX() - 32),
			"x");
	d.setObject(CCString::createWithFormat("%i", (int) getPositionY() - 32),
			"y");
	GameSprite* sprite = o.createObject(&d);

	if (sprite)
	{

		GAMEUTILS->addObject(sprite);

	}
	currentState = (-1);
}

void QuestionMark::hit(GameDirection hitDirection, GameSprite* object)
{
	if (object->getType() == GAME_TYPE_BULLET)
	{
		getKill();
	}
}

QuestionMark* QuestionMark::create()
{
	QuestionMark *pobSprite = new QuestionMark();

	pobSprite->currentState = 0;
	CCSpriteFrame *frame =
			CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(
					"questionmark.png");
	if (pobSprite && pobSprite->initWithSpriteFrame(frame))
	{
		pobSprite->autorelease();
		return pobSprite;
	}
	CC_SAFE_DELETE(pobSprite);
	return NULL;
}
