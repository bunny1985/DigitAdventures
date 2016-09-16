/*
 * Cannon.cpp
 *
 *  Created on: 23-07-2013
 *      Author: michal
 */

#include "Sprites/Enemies/Cannon.h"
#include "Sprites/Bulets/BasicBullet.h"
#include "Common/Enums.h"
#include "GameLevelScene.h"
#include "SimpleAudioEngine.h"
#include "Common/RESPATH.h"

Cannon::Cannon() :
		AbstractEnemy()
{
	properities=0;

	enemeyproperities|=PESHOOTING;
	shotingDirection = GameDirectionUp;
}

Cannon::~Cannon()
{
	// TODO Auto-generated destructor stub
}


void Cannon::update()
{
	shoot();

}

void Cannon::hit(GameDirection hitDirection, GameSprite* object) {
}

void Cannon::setDirection(GameDirection direction) {

	this->direction = direction;
	//this->setRotation(0.3f);
	//this->runAction(CCRotateTo::create(0,3, 90));
	this->setRotation((int)direction*90);
	//exit(0);
}
