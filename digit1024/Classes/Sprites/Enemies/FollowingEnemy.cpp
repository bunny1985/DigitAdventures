#include "FollowingEnemy.h"
#include "Common/Resources.h"
#include "GameLevelScene.h"

GameDirection FollowingEnemy::pickDirection(){
	Robbo*  robbo = GAMEUTILS->robboSprite;
	CCPoint  substrPoint = ccpSub(getTileMapPosition() ,robbo->getTileMapPosition());
	CCPoint vector = ccp(0, 0);
	if (substrPoint.x > 0){
		vector.x = -1;
	}
	else
	{
		vector.x = 1;
	}
	if (substrPoint.y > 0){
		vector.y = 1;
	}
	else
	{
		vector.y = -1;
	}



	// Teraz spróbujemy zwróciæ oœ która pierwsza
	if (abs(substrPoint.x) > abs(substrPoint.y)){
		GameDirection d = GAMEUTILS->getGameDirectionFromVector(ccp(vector.x, 0));
		if (canBeMoved(d)){
			return d;
		}
		else{
			return GAMEUTILS->getGameDirectionFromVector(ccp(0, vector.y));
		}
		
	}else{
		GameDirection d = GAMEUTILS->getGameDirectionFromVector(ccp(0, vector.y));
		if (canBeMoved(d)){
			return d;
		}
		else{
			return GAMEUTILS->getGameDirectionFromVector(ccp(vector.x, 0));
		}
	}

	GameDirection d =  GAMEUTILS->getGameDirectionFromVector(vector);
	if (canBeMoved(d))return d;


	
	return GameDirectionUnknown;
	setState(EnemyStateIdle);

}

void FollowingEnemy::setDirection(GameDirection direction){
	AbstractEnemy::setDirection(direction);
	runAction(CCRotateTo::create(0.3, (int) direction * 90));
}