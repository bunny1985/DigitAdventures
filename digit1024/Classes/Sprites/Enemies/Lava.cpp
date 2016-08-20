/*
 * TwoDirectionsEnemy.cpp
 *
 *  Created on: 19-07-2013
 *      Author: michal
 */

#include "Lava.h"
#include "GameLevelScene.h"


Lava::Lava(){

	properities &= ~PSHOOTABLE; //
	properities |= PENTERABLE;
	properities |= PPUSHABLE;
	enemeyproperities |= PEMOVING;
	currentState == EnemyStateIdle;
	speed = 1;
	schedule(schedule_selector(Lava::grow ) , 0.8);
	type = GAME_TYPE_BULLET;



}
GameDirection Lava::pickDirection(){
	int d = std::rand() % 4;
	return (GameDirection) d;

}
void Lava::touchTest(){
	return;
}
void Lava::startMoving(){

}
void Lava::update(){};


void Lava::grow(float d){

	makeMove(GameDirectionUnknown);
	bool shouldCancel = true;
	for (int x = 0; x < 4; x++){
		GameDirection d = (GameDirection) x;
		CCPoint p = GAMEUTILS->ccpTiledAdd(getTileMapPosition(), GAMEUTILS->getTiledVectorFromDirection(d));
		GameSprite* obj = GAMEUTILS->objectAt(p, this);
		//TODO to powinni�my jako� inaczej rozwi�za�
		bool isLava = obj != NULL && obj->getType() == GAME_TYPE_BULLET;

		if (!GAMEUTILS->isWallPresent(p) && !isLava){
			shouldCancel = false;
		}
	}
	if (shouldCancel){

		unschedule(schedule_selector(Lava::grow));

	}
}

void Lava::makeMove(GameDirection direction)
{

	setDirection(pickDirection());
	//if (!canBeMoved(direction)) return;
	setState(EnemyStateMoving);



	if (rand() % 2){
		if (GAMEUTILS->isWallPresent(getTileMapNextPosition()))return;
		GameSprite* obj = NULL;

		obj = GAMEUTILS->objectAt(getTileMapNextPosition(), this);
		if (obj != NULL){
			int a = obj->properities&PSHOOTABLE;
			if (a == 0)return;
		}



		Lava* newLava = Lava::create();
		newLava->setPosition(GAMEUTILS->getScenePoint(getTileMapNextPosition()));
		GAMEUTILS->addObject(newLava);
		if (obj){

		}
		hit(GameDirectionUnknown , obj);
		//GAMEUTILS->addPenidingObjects();
	}
}



void Lava::hit(GameDirection hitDirection, GameSprite* object)
{
	if (!object)return;
	if (currentState == -1)
		return;
	object->getKill();
	if (object->getType() == GAME_TYPE_ROBBO
		|| object->getType() == GAME_TYPE_QUESTIONMARK || object->getType() == GAME_TYPE_BULLET)
	{
		object->getKill();
	}
	else if (object->getType() == GAME_TYPE_ENEMY)
	{
		object->hit(direction, this);

	}

}
int Lava::maxId = 0;
