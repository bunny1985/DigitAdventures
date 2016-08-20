/*
 * Box.cpp
 *
 *  Created on: 17-07-2013
 *      Author: michal
 */

#include "Sprites/Objects/Box.h"
#include "Common/Resources.h"
#include "GameLevelScene.h"
#include "SimpleAudioEngine.h"
#include "Common/RESPATH.h"
Box::Box() :
		GameSprite()
{
	type = GAME_TYPE_BOX;
	currentState = BoxStateIdle;
	properities |= PPUSHABLE;
	properities |= PPRESERVEPOINT;
	speed = 0.07;

}
bool Box::pushed(GameDirection d){
	bool r = GameSprite::pushed(d);
	if (r){
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(respatchFix("Sounds/szur" SOUND_EXT).c_str());
	}
	return r;
}

Box::~Box()
{
	// TODO Auto-generated destructor stub
}

