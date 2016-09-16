/*
 * AbstractStateObserver.cpp
 *
 *  Created on: 24-08-2013
 *      Author: michal
 */
#include "Sprites/AbstractStateObserver.h"

GameObjectEvent::GameObjectEvent(GameSprite* caller)
{
	this->caller = caller;
	message = "Unknown Event";
}
