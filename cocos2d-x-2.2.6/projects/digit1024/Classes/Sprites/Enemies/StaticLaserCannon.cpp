/*
 * StaticLaserCannon.cpp
 *
 *  Created on: 23-07-2013
 *      Author: michal
 */

#include "Sprites/Enemies/StaticLaserCannon.h"
#include "Sprites/Bulets/LaserBullet.h"
#include "GameLevelScene.h"
#include "SimpleAudioEngine.h"
#include <cstdlib>
#include "Common/RESPATH.h"

StaticLaserCannon::StaticLaserCannon() :
		StaticSimpleCannon()
{


}

void StaticLaserCannon::getKill(){
	if (bullet){
	bullet->stopAllActions();
	bullet->currentState = -1;
	if (bullet->lastMark){
		bullet->lastMark->getKill();
	}

	}
	GameSprite::getKill();
}

StaticLaserCannon::~StaticLaserCannon()
{
	// TODO Auto-generated destructor stub
}



void StaticLaserCannon::shoot() {
	if(currentState==EnemyStateShooting)return;
	if (float(std::rand() % 100) <= shootFrequency)
	{

		currentState = EnemyStateShooting;
		
		CCPoint v = GAMEUTILS->getTiledVectorFromDirection(shotingDirection);
		v = GAMEUTILS->ccpTiledAdd( getTileMapPosition(), v );
		if (!isShootPosssible(v)){
			currentState = EnemyStateIdle;
			return;
		}
		LaserBullet *bullet = LaserBullet::create(this);
		this->bullet = bullet;
		bullet->setPosition(GAMEUTILS->getScenePoint(v));
		bullet->startShoot(shotingDirection);

		GAMEUTILS->addObject(bullet);
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(respatchFix(
				"Sounds/shoot" SOUND_EXT).c_str());
	}


}
void StaticLaserCannonRotating::shoot(){
	if (currentState == EnemyStateShooting)return;
	if (float(std::rand() % 100) <= shootFrequency){
		direction = (GameDirection) (std::rand() % 4);
		shotingDirection = direction;
		int angle = (int) direction * 90;
		runAction(CCRotateTo::create(0.3, angle));
	}
	StaticLaserCannon::shoot();
}
