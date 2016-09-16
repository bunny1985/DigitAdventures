/*
 * Collectable.cpp
 *
 *  Created on: 19-07-2013
 *      Author: michal
 */

#include "Sprites/Objects/Collectable.h"
#include "Common/Resources.h"
#include "Sprites/Robbo.h"
#include "SimpleAudioEngine.h"
#include "Common/RESPATH.h"
Collectable::Collectable() :
		GameSprite()
{
	type = GAME_TYPE_Collectable;


	properities |= PENTERABLE;

	direction = GameDirectionUnknown;
	speed = 0;
	currentState = 0;
	colectableType = GAME_TYPE_CollectableTYPE_SCREW;
	colectableQuantity = 1;
	this->setRotation(-30.0);
	animationSequence = CCRepeatForever::create(
			CCSequence::createWithTwoActions(CCRotateBy::create(1.0, 60.0),
					CCRotateBy::create(1.0, -60.0)));
	runAction(animationSequence);
}

Collectable::~Collectable()
{
}

void Collectable::hit(GameDirection hitDirection, GameSprite* object)
{
	if (object->getType() == GAME_TYPE_ROBBO)
	{
		((Robbo*) object)->getColectable(this);
		const char* sounds[4] =
		{ "screw" SOUND_EXT, "key" SOUND_EXT, "life" SOUND_EXT, "ammo" SOUND_EXT };
		CCString* sound = CCString::createWithFormat("Sounds/%s",
				(sounds[colectableType]));

		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(
				sound->getCString());
		getKill();
	}
}

int Collectable::getCollectableType()
{
	return colectableType;
}

int Collectable::getCollectableQuantity()
{
	return colectableQuantity;
}
void Collectable::applyProperties(CCDictionary* dictionary){
    GameSprite::applyProperties(dictionary);
    colectableQuantity = dictionary->valueForKey("quantity")->intValue();
}
void Collectable::getKill()
{
	runAction(CCSequence::createWithTwoActions(CCSpawn::createWithTwoActions(
		CCScaleTo::create(0.3, 2), CCFadeOut::create(0.3))
		, CCCallFunc::create(this,
		callfunc_selector(Collectable::onGetKill))));
}
void Collectable::onGetKill(){
	setState(-1);
}

Collectable* Collectable::create(int type, int quantity)
{
	Collectable *pobSprite = new Collectable();
	const char* images[4] =
	{ "screw.png", "key.png", "life.png", "ammo.png" };
	pobSprite->currentState = 0;
	pobSprite->colectableType = type;
	pobSprite->colectableQuantity = quantity;
	CCSpriteFrame *frame =
			CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(
					images[type]);
	if (pobSprite && pobSprite->initWithSpriteFrame(frame))
	{
		pobSprite->autorelease();
		return pobSprite;
	}
	CC_SAFE_DELETE(pobSprite);
	return NULL;

}

