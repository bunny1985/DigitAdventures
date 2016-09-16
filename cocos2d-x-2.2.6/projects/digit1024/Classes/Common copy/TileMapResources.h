#ifndef TILEMAPRESOURCES_H_
#define TILEMAPRESOURCES_H_
#include "Common/Resources.h"
#include "Common/Enums.h"
#include "Sprites/GameSprite.h"
#include <map>




class IGameSpriteFactory{
public:
	virtual GameSprite* Create(CCDictionary* dictionary) = 0;
};

template <class __TYPE__>
class GameSpriteFactory: public IGameSpriteFactory{
public:
	 __TYPE__* Create(CCDictionary* dictionary){
		__TYPE__* obj = __TYPE__::create();
		if (dictionary){
			obj->applyProperties(dictionary);
		}
		return obj;
	}
};








class TileMapResources
{
public:
	TileMapResources();
	virtual ~TileMapResources();
	std::map<const char*, GameDirection> directortiesDictionary;
	std::map<int, IGameSpriteFactory*> factoriesDictionary;
	

};

#endif