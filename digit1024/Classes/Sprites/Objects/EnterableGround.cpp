/*
 * EnterableGround.cpp
 *
 *  Created on: Mar 25, 2014
 *      Author: Michal
 */

#include "EnterableGround.h"
#include "Common/Resources.h"
EnterableGround::EnterableGround() {
	currentState = 0;
	speed = 0;
	type = GAME_TYPE_ENTERABLEGROUND;
	properities |= PPUSHABLE;
	properities |= PENTERABLE;
	properities &= ~PSHOOTABLE;
	direction = GameDirectionUnknown;
}
bool EnterableGround::pushed(GameDirection direction){
	runAction(CCSequence::createWithTwoActions(
			CCFadeOut::create(0.3),
			CCCallFunc::create(this, callfunc_selector(EnterableGround::getKill))
	));

	return true;
}


EnterableGround::~EnterableGround() {
	// TODO Auto-generated destructor stub
}

bool EnterableGround::canBeMoved(GameDirection direction) {
	return true;
}
