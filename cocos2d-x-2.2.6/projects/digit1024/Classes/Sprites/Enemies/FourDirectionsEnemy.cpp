/*
 * FourDirectionEnemy.cpp
 *
 *  Created on: 20-07-2013
 *      Author: michal
 */

#include "Sprites/Enemies/FourDirectionsEnemy.h"
#include "Common/Resources.h"

FourDirectionsEnemy::FourDirectionsEnemy()
: AbstractEnemy()
{

	type = GAME_TYPE_ENEMY;
	direction = GameDirectionUnknown;
	lastDirection = GameDirectionUnknown;
	turn = 1;
	enemeyproperities|=PEMOVING;


}

FourDirectionsEnemy::~FourDirectionsEnemy()
{
	// TODO Auto-generated destructor stub
}

GameDirection FourDirectionsEnemy::pickDirection()
{

	int d = (int) direction;
	// spróbujmy skręcić z godnie z turn;
	d += turn;
	d += 4;
	d %= 4;
	//jaksię udało to spoko
	if (canBeMoved((GameDirection) d))
	{
		lastDirection = direction;
		direction = (GameDirection) d;
		runAction(CCRotateTo::create(0.3, (int) direction * 90));
		return direction;
	}
	// a jak nie to idźmy dalej
	if (canBeMoved(direction))
	{
		lastDirection = direction;
		return direction;
	}
	//ale jeśli nie to spróbujmy skęcić w drugą stronę
	d -= (2 * turn);
	d += 4;
	d %= 4;
	//jaksię udało to spoko
	if (canBeMoved((GameDirection) d))
	{
		lastDirection = direction;
		direction = (GameDirection) d;
		runAction(CCRotateTo::create(0.3, (int) direction * 90));
		
		return direction;
	}
	//w ostateczności zawrócimy
	d += (3 * turn);
	d += 4;
	d %= 4;
	//jaksię udało to spoko
	if (canBeMoved((GameDirection) d))
	{
		lastDirection = direction;
		direction = (GameDirection) d;
		runAction(CCRotateTo::create(0.3, (int) direction * 90)); 
		return direction;
	}
	// jak nas przyblokowało to pamiętamy last direction i zwracamy unknown
	
	return GameDirectionUnknown;

}
void FourDirectionsEnemy::applyProperties(CCDictionary* dictionary){
	GameSprite::applyProperties(dictionary);
	turn = dictionary->valueForKey("turn")->intValue();
	if (turn > 0){
		turn = 1;
	}
	else{
		turn = -1;
	}

	
}

void FourDirectionsEnemy::setTurn(int turn)
{
	if (turn >= 0)
	{
		this->turn = 1;

	}
	else
	{
		this->turn = -1;
	}

}

FourDirectionsEnemy* FourDirectionsEnemy::create()
{

	FourDirectionsEnemy *pobSprite = new FourDirectionsEnemy();

	pobSprite->currentState = EnemyStateIdle;
	CCSpriteFrame *frame =
			CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(
					"enemy1.png");
	if (pobSprite && pobSprite->initWithSpriteFrame(frame))
	{
		pobSprite->autorelease();
		return pobSprite;
	}
	CC_SAFE_DELETE(pobSprite);
	return NULL;
}

void FourDirectionsEnemy::startMoving() {
	GameDirection d  = pickDirection();
	if (d != GameDirectionUnknown){
		direction = d;
	}
	AbstractEnemy::startMoving();
	
	// runAction(
		//		CCRepeatForever::create(CCSequence::create(CCRotateBy::create(0.3, 15) ,CCRotateBy::create(0.3, -15) , NULL ))
		//);
}

