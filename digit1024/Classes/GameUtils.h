/*
 * GameUtils.h
 *
 *  Created on: 19-08-2013
 *      Author: michal
 */

#ifndef GAMEUTILS_H_
#define GAMEUTILS_H_
#include "cocos2d.h"

#include "Common/Enums.h"
#include "Sprites/GameSprite.h"
#include <vector>

USING_NS_CC;


class ComparablePoint{
public:
	int x;
	int y;
	ComparablePoint(CCPoint point);


};

bool operator>(const ComparablePoint that, ComparablePoint point);
bool operator<(const  ComparablePoint that, ComparablePoint point);
bool operator==(const ComparablePoint that, ComparablePoint point);



class GameUtils
{
public:

	CCPoint getScenePoint(CCPoint tiledPoint);
	CCPoint getTiledPoint(CCPoint scenePoint);
	CCPoint getSceneVector(CCPoint tiledVector);
	CCPoint getTiledVectorFromDirection(GameDirection direction);
	CCPoint ccpTiledAdd(CCPoint tiledPoint, CCPoint tiledVector);
	GameSprite* objectAt(CCPoint tilePoint, GameSprite * caller);
	bool isPointReserved(CCPoint point);
	GameDirection getGameDirectionFromVector(CCPoint vector);
	GameDirection getOpositeDirection(GameDirection direction);
	bool isWallPresent(CCPoint tilePoint);
	GameDirection validateDirection(GameDirection direction);
	void addObject(GameSprite* object);
	void removeObject(GameSprite* object);
	int getAvaliableLevels();
	GameUtils();
	virtual ~GameUtils();
	void setVolume();
	CCArray objects; ///Array of GameObjects
	void addPenidingObjects();
	std::map<ComparablePoint, std::vector<GameSprite*> > objectsMap;
	void updateObjectsMap();

protected:
	CCTMXTiledMap *map;
	CCArray objectsWaitingForAddition; ///Array of GameObjects

};




#endif /* GAMEUTILS_H_ */
