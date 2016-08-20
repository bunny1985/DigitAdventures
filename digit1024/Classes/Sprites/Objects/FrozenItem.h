

#ifndef FROZENITEM_H_
#define FROZENITEM_H_

#include "IceBlock.h"
#include "Common/Resources.h"
#include "GameLevelScene.h"
#include "Bomb.h"
#include "Collectable.h"
#include "Starship.h"
#include "Box.h"
#include "Rock.h"

template<class T>
class FrozenItem: public IceBlock{
public:
    FrozenItem(){
        
    }
	GameSprite* postCreate(const char* framename){
		GameSprite::postCreate(framename);
		T* obj = T::create();
		obj->setPosition(ccp(40, 40));
		obj->setZOrder(-1);
		addChild(obj);
		return this;
	}


    virtual void getKill(){
        T* obj = T::create();
        GAMEUTILS->addObject(obj);
        obj->setPosition(this->getPosition());
            IceBlock::getKill();
    }
};

class frozenBomb: public FrozenItem<Bomb>{
public:
    SPRITECREATION("boxSlide.png", frozenBomb)
		
};
class frozenScrew: public FrozenItem<CollectableStar>{
public:
    SPRITECREATION("boxSlide.png", frozenScrew)
		GameSprite* postCreate(const char* framename){
			GAMEUTILS->TotalScrews++;
			return FrozenItem::postCreate(framename);
		}
};
class frozenKey: public FrozenItem<CollectableKey>{
public:
    SPRITECREATION("boxSlide.png", frozenKey)
};
class frozenRock: public FrozenItem<Rock>{
public:
    SPRITECREATION("boxSlide.png", frozenRock)
};
class frozenStarship: public FrozenItem<Starship>{
public:
    SPRITECREATION("boxSlide.png", frozenStarship)
};

class frozenAmmo: public FrozenItem<CollectableAmmo>{
public:
    SPRITECREATION("boxSlide.png", frozenAmmo)
};

class frozenBox: public FrozenItem<Box>{
public:
    SPRITECREATION("boxSlide.png", frozenBox)

};
#endif
