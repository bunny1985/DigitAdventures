/*
 * Bomb.cpp
 *
 *  Created on: 21-07-2013
 *      Author: michal
 */


#include "Sprites/Objects/Bomb.h"
#include "GameLevelScene.h"
#include "Common/Resources.h"
#include "SimpleAudioEngine.h"


#include "Common/RESPATH.h"


Bomb::Bomb() :
		Box()
{

	currentState = 0;
	type = GAME_TYPE_BOMB;
	direction = GameDirectionUnknown;

	properities |= PPUSHABLE;
	properities |= PSHOOTABLE;
	properities |= PPRESERVEPOINT;
}

Bomb::~Bomb()
{
	// TODO Auto-generated destructor stub
}

void Bomb::getKill()
{
	if (currentState == (-1) || currentState == BombStateDestroing)
		return;
	this->setState(BombStateDestroing);
	stopAllActions();
	runAction(CCSequence::createWithTwoActions(CCScaleTo::create(0.15 , 0),
		CCCallFunc::create(this,
		callfunc_selector(Bomb::onGetKill))));
	}

void Bomb::onGetKill(){
	GAMEUTILS->showExplosion(getTileMapPosition());
	for (int x = -1; x <= 1; x++)
	{
		for (int y = -1; y <= 1; y++)
		{
			GameSprite* sprite;
			CCPoint p = GAMEUTILS->ccpTiledAdd(getTileMapPosition(), ccp(x, y));
			sprite = GAMEUTILS->objectAt(p, this);
			if (sprite && sprite->getType() != GAME_TYPE_BULLET)
			{
				
				sprite->getKill();
			}
		}
	}

	setState(-1);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(
		respatchFix("Sounds/bomb" SOUND_EXT).c_str());
}
