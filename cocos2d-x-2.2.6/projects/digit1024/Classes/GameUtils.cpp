/*
 * GameUtils.cpp
 *
 *  Created on: 19-08-2013
 *      Author: michal
 */

#include "GameUtils.h"

#include "SimpleAudioEngine.h"
#include "Common/Resources.h"
#include "Common/RESPATH.h"


#if WINDOWS
double round(double fValue)
{
	return fValue < 0 ? ceil(fValue - 0.5)
		: floor(fValue + 0.5);
}
#endif

GameUtils::GameUtils()
{
	// TODO Auto-generated constructor stub

}


void GameUtils::addPenidingObjects(){
	CCObject* tmpobj;
	CCARRAY_FOREACH(&objectsWaitingForAddition, tmpobj){
		objects.addObject(tmpobj);
		((GameSprite*) tmpobj)->resumeSchedulerAndActions();
	}

	objectsWaitingForAddition.removeAllObjects();
}
int GameUtils::getAvaliableLevels(){
	return 100;
}

void GameUtils::addObject(GameSprite* object)
{
	objectsWaitingForAddition.addObject(object);
	object->pauseSchedulerAndActions();

}
void GameUtils::updateObjectsMap(){
	objectsMap.clear();
	CCObject *obj;
	CCARRAY_FOREACH(&objects, obj)
	{
		GameSprite* gameobj = static_cast<GameSprite*>(obj);
		if (objectsMap.count(ComparablePoint(gameobj->getTileMapPosition())) > 0 ){
			//exists
			objectsMap[ComparablePoint(gameobj->getTileMapPosition())].push_back(gameobj);
		}
		else{
			objectsMap[ComparablePoint(gameobj->getTileMapPosition())] =  std::vector<GameSprite*>();
			objectsMap[ComparablePoint(gameobj->getTileMapPosition())].push_back(gameobj);
		//	not exists

		}

		//objectsMap[ComparablePoint(gameobj->getTileMapPosition())] = gameobj;



	}
}


void GameUtils::removeObject(GameSprite* object)
{
	objects.removeObject(object);
	updateObjectsMap();
}

GameUtils::~GameUtils()
{
	objects.removeAllObjects();
	objectsWaitingForAddition.removeAllObjects();
	// TODO Auto-generated destructor stub
}

GameSprite* GameUtils::objectAt(CCPoint tilePoint, GameSprite* caller)
{
	if (objectsMap.count(ComparablePoint(tilePoint)) == 0){
		return NULL;
	}
	else{
		std::vector<GameSprite*> v = objectsMap[ComparablePoint(tilePoint)];
		for (std::vector<GameSprite*>::iterator it = v.begin(); it != v.end(); ++it) {
			GameSprite* sprite = *it;
			if (sprite != caller){
				return sprite;
			}
		}
		return NULL;
	}







	CCObject *obj;
	CCARRAY_FOREACH(&objects , obj)
	{
		GameSprite* gameobj = static_cast<GameSprite*>(obj);
		if (gameobj->getTileMapPosition().x == tilePoint.x
				&& gameobj->getTileMapPosition().y == tilePoint.y
				&& gameobj != caller)
		{
			return gameobj;
		}
	}
	return NULL;
}

CCPoint GameUtils::getScenePoint(CCPoint tiledPoint)
{
	double px, py;
	px = tiledPoint.x * map->getTileSize().width
			+ (map->getTileSize().width * 0.5);

	py = (map->getTileSize().height * map->getMapSize().height)

	- (tiledPoint.y * map->getTileSize().height)
			- (0.5 * map->getTileSize().height);
#ifdef UTILSLOG
	CCLOG("tiled point to scene point %i,%i to %i,%i", (int)tiledPoint.x, (int)tiledPoint.y, (int )px, (int )py);
#endif
	return ccp(px,py);
}

CCPoint GameUtils::getSceneVector(CCPoint tiledVector)
{
	return ccp(tiledVector.x * map->getTileSize().width , tiledVector.y * map->getTileSize().height);
}

GameDirection GameUtils::getGameDirectionFromVector(CCPoint vector)
{
	if (vector.x > 0)
		return GameDirectionRigh;
	if (vector.x < 0)
		return GameDirectionLeft;
	if (vector.y > 0)
		return GameDirectionUp;
	if (vector.y < 0)
		return GameDirectiondDown;
	return GameDirectionUnknown;
}

bool GameUtils::isWallPresent(CCPoint tilePoint)
{
	if (tilePoint.x < 0 || tilePoint.y < 0)
		return true;
	CCTMXLayer *walls = map->layerNamed("walls");
	unsigned int gid = walls->tileGIDAt(tilePoint);

	if (gid)
	{
		CCDictionary *properites = map->propertiesForGID(gid);
		if (properites)
		{
			CCString *collision = (CCString*) properites->objectForKey("wall");
			if (collision)
			{
				return true;
			}
		}
	}
	return false;

}

CCPoint GameUtils::getTiledVectorFromDirection(GameDirection direction)
{
	switch (direction)
	{
	case GameDirectionLeft:
		return ccp( -1, 0);
		break;
		case GameDirectionRigh:
		return ccp( 1,0);
		break;
		case GameDirectionUp:
		return ccp(0, 1);
		break;
		case GameDirectiondDown:
		return ccp(0,-1);
		break;
		default:
		return ccp(0,0);
		break;
	}
}

CCPoint GameUtils::getTiledPoint(CCPoint scenePoint)
{
	float px, py;
  	px = floor(scenePoint.x / map->getTileSize().width);
	float poly = (map->getMapSize().height);
	py = ceil(scenePoint.y / map->getTileSize().height);
#ifdef UTILSLOG
	CCLOG("scene point  to tiled point %i,%i to %i,%i", (int)scenePoint.x, (int)scenePoint.y, (int )px, (int )py);
#endif
	return ccp(round(px) , round(poly-py));
}

GameDirection GameUtils::validateDirection(GameDirection direction)
{
	if (direction < 0 || direction > 4)
		return GameDirectionUnknown;
	return direction;
}

CCPoint GameUtils::ccpTiledAdd(CCPoint tiledPoint, CCPoint tiledVector)
{
	return ccp(tiledPoint.x + tiledVector.x , tiledPoint.y - tiledVector.y);
}

GameDirection GameUtils::getOpositeDirection(GameDirection direction)
{
	GameDirection oposite;
	switch (direction)
	{
	case GameDirectionLeft:
		oposite = GameDirectionRigh;
		break;
	case GameDirectionRigh:
		oposite = GameDirectionLeft;
		break;
	case GameDirectionUp:
		oposite = GameDirectiondDown;
		break;
	case GameDirectiondDown:
		oposite = GameDirectionUp;
		break;
	default:
		oposite = GameDirectionUnknown;
		break;
	}
	return oposite;
}

bool GameUtils::isPointReserved(CCPoint point)
{
	CCObject *tmpobj;

	CCARRAY_FOREACH_REVERSE(&objects , tmpobj)
	{
		if (((GameSprite*) tmpobj)->getReservedPoint().x == point.x
				&& ((GameSprite*) tmpobj)->getReservedPoint().y == point.y)
		{
			return true;
		}
	}
	return false;
}

void GameUtils::setVolume() {
	float volume = CCUserDefault::sharedUserDefault()->getFloatForKey(SETTINGSOUNDSVOLUME );

	CocosDenshion::SimpleAudioEngine::sharedEngine()->setEffectsVolume(volume);
	volume = CCUserDefault::sharedUserDefault()->getFloatForKey(SETTINGSMUSICVOLUME);

	CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(volume);
}


ComparablePoint::ComparablePoint(CCPoint  point){
	x = point.x;
	y = point.y;
}
bool operator<(const ComparablePoint that, ComparablePoint point){
	if (that.x < point.x){
		return true;
	}
	else
	{
		if (that.x>point.x){
			return false;
		}
		else{
			return that.y < point.y;
		}
	}
}
bool operator>(const ComparablePoint that  , ComparablePoint point){
	return !(that < point);
}

bool operator==(const ComparablePoint that , ComparablePoint point){
	return that.x == point.x && that.y == point.y;
}
