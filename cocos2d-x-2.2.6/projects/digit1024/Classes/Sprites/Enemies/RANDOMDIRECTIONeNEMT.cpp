#include "RANDOMDIRECTIONeNEMT.h"

#include "GameLevelScene.h"
#include <cstdlib>

RandomDirectionEnemy::RandomDirectionEnemy()
	: TwoDirectionsEnemy()
{
	direction = GameDirectionUnknown;
	lastDirection = direction;
	enemeyproperities |= PEMOVING;
	setZOrder(getZOrder() + 1);
	runAction(CCRepeatForever::create(CCSequence::create(CCSkewBy::create(0.3f, 10.0f, 0.1f), CCSkewBy::create(0.3f, -10.0f, -0.1f), NULL)));
}
void RandomDirectionEnemy::fixPosition(){
	GameSprite* obj = GAMEUTILS->objectAt(getTileMapPosition(), this);
	if (obj && obj->getType() == GAME_TYPE_Collectable)return;

	AbstractEnemy::fixPosition();
	
}
RandomDirectionEnemy::~RandomDirectionEnemy()
{
}
bool RandomDirectionEnemy::canBeMoved(GameDirection direction){
	 CCPoint currentPos = getTileMapPosition();
	CCPoint vector = GAMEUTILS->getTiledVectorFromDirection(direction);
	CCPoint point = ccp(currentPos.x + vector.x, currentPos.y - vector.y);
	GameSprite* obj = GAMEUTILS->objectAt(point , this);
	if (obj && obj->getType() == GAME_TYPE_Collectable) return true;
	
	return TwoDirectionsEnemy::canBeMoved(direction);
}
GameDirection RandomDirectionEnemy::pickDirection(){

	if (canBeMoved(this->direction)){
		if (std::rand() % 3)
			return this->direction;
	}

	std::vector<GameDirection> availableDirections;
	for (int x = 0; x < 4; x++){
		if (canBeMoved((GameDirection) x)){
			availableDirections.push_back((GameDirection) x);
		}
	}
	if (availableDirections.empty()) return GameDirectionUnknown;

	GameDirection direction = availableDirections[(std::rand() % availableDirections.size())];
	return direction;
}