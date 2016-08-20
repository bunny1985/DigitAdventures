

#include "FallingStar.h"
#include "GameLevelScene.h"
#include "Collectable.h"
#include "SimpleAudioEngine.h"
#include "Common\RESPATH.h"

FallingStar::FallingStar(){
	properities |= PENTERABLE;
	properities &= (~PPUSHABLE);

	runAction( CCRepeatForever::create(
		CCSequence::createWithTwoActions(CCRotateBy::create(1.0, 60.0),
		CCRotateBy::create(1.0, -60.0))));
	GAMEUTILS->TotalScrews++;
}

void FallingStar::hit(GameDirection hitDirection, GameSprite* object){

    if(getState()==-1)return;
	if (getState() == 5)return;
	
		if (object->getType() == GAME_TYPE_ROBBO)
		{
			((Robbo*) object)->screws++;
			GAMEUTILS->updateColletcable(0, ((Robbo*) object)->screws, ((Robbo*) object)->shoots, ((Robbo*) object)->keys);
				//CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/screw"SOUND_EXT);
			getKill();
			setState(5);
			
		}
		


}
bool FallingStar::canBeMoved(GameDirection direction) {
	if (direction == GameDirectionUp) {
		return false;
	}
	if (getState() == rockStateRoling) return false;
	if (getState() == BoxStateMoving) return false;

	CCPoint point =
		GAMEUTILS->ccpTiledAdd(getTileMapPosition(), GAMEUTILS->getTiledVectorFromDirection(direction));
	GameSprite* obj = GAMEUTILS->objectAt(point, this);
	if ((getState() == rockStateFalling) && obj&& obj->properities & PSHOOTABLE){
		return true;
	}
	if (GAMEUTILS->isPointReserved(point))return false;
	properities |= (PPUSHABLE);
	bool r= Box::canBeMoved(direction);

	properities &= (~PPUSHABLE);
	return r;
}

	void FallingStar::getKill()
	{
		runAction(CCSequence::createWithTwoActions(CCSpawn::createWithTwoActions(
			CCScaleTo::create(0.3, 2), CCFadeOut::create(0.3))
			, CCCallFunc::create(this,
			callfunc_selector(Collectable::onGetKill))));
	}
	void FallingStar::onGetKill(){
		setState(-1);
	}
