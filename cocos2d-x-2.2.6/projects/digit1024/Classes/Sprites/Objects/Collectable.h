/*
 * Collectable.h
 *
 *  Created on: 19-07-2013
 *      Author: michal
 */

#ifndef COLLECTABLE_H_
#define COLLECTABLE_H_
#include "Sprites/GameSprite.h"
#include "Common/Resources.h"
#include "cocos2d.h"

class Collectable: public GameSprite
{
public:
	Collectable();
	virtual ~Collectable();
	virtual void hit(GameDirection hitDirection, GameSprite *object);
	virtual void getKill();
	virtual void onGetKill();
	int getCollectableType();
	int getCollectableQuantity();
	static Collectable* create(int type, int quantity);
	void applyProperties(CCDictionary* dictionary);
protected:
	int colectableType;
	int colectableQuantity;
	CCRepeatForever* animationSequence;

};

class CollectableStar :public Collectable{
public:
	SPRITECREATION("screw.png", CollectableStar);
	CollectableStar() : Collectable(){
		colectableType = GAME_TYPE_CollectableTYPE_SCREW;
	}
};
class CollectableKey :public Collectable {
public:
	SPRITECREATION("key.png", CollectableKey);
	CollectableKey() : Collectable(){
		colectableType = GAME_TYPE_CollectableTYPE_KEY;
	}
};
class CollectableAmmo :public Collectable{
public:
	SPRITECREATION("ammo.png", CollectableAmmo);
	CollectableAmmo() : Collectable(){
		colectableType = GAME_TYPE_CollectableTYPE_AMMO;
		colectableQuantity = 9;
	}
};


#endif /* COLLECTABLE_H_ */
