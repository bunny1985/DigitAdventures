/*
 * AbstractStateObserver.h
 *
 *  Created on: 24-08-2013
 *      Author: michal
 */

#ifndef ABSTRACTSTATEOBSERVER_H_
#define ABSTRACTSTATEOBSERVER_H_
#include "Sprites/GameSprite.h"

class GameSprite;
class GameObjectEvent
{

public:
	GameSprite* caller;
	const char* message;
	GameObjectEvent(GameSprite* caller);
	//TODO  - pomysł jest też taki żeby state trzymać nei w incie a w klasi e któ¶a bedzie tryzmać inta. wtedy bedzie można przeciążyć = i == do inta i zostanie mocniejsze typowanie
};

class AbstractStateObserver
{
public:
	AbstractStateObserver()
	{
	}
	;
	virtual ~AbstractStateObserver()
	{
	}
	;
	virtual void notify(GameObjectEvent)
	{
	}
	;
};

#endif /* ABSTRACTSTATEOBSERVER_H_ */
