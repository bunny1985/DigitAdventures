/*
 * ObjectsFactory.h
 *
 *  Created on: 21-07-2013
 *      Author: michal
 */

#ifndef OBJECTSFACTORY_H_
#define OBJECTSFACTORY_H_
#include "Sprites/GameSprite.h"

class ObjectsFactory
{
public:
	ObjectsFactory();
	virtual ~ObjectsFactory();
	virtual GameSprite* createObject(CCDictionary* properties);
protected:
	GameSprite* createEnemy(CCDictionary* properties);
	void setPosition(GameSprite* obj, int x, int y);
	int validateIntRange(int minValue, int maxValue, CCString* value);
	CCString* getValue(CCDictionary* properties, const char* key);
};

#endif /* OBJECTSFACTORY_H_ */
