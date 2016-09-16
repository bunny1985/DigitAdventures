/*
 * FallingBomb.cpp
 *
 *  Created on: 29 sie 2014
 *      Author: Michal
 */

#include "FallingBomb.h"
#include "GameLevelScene.h"
#include "SimpleAudioEngine.h"
#include "Common/RESPATH.h"



FallingBomb::FallingBomb(){
    properities = properities|PSHOOTABLE;
}

void FallingBomb::stopFalling(){

    if (!canBeMoved(GameDirectiondDown)) {
        setState((int) rockStateIdle);
        stopAllActions();
        this->onGetKill();
    }else{
        startFalling(0.0);
    }


}

void FallingBomb::getKill()
{
    if (currentState == (-1) || currentState == 5)
        return;
    this->setState(5);
    stopAllActions();
    runAction(CCSequence::createWithTwoActions(CCScaleTo::create(0.15 , 0),
        CCCallFunc::create(this,
        callfunc_selector(FallingBomb::onGetKill))));

    }
void FallingBomb::startFalling(float delay) {
    direction = GameDirectiondDown;
    reservePoint();
    setState((int) rockStateFalling);
    CCPoint nextPoint = GAMEUTILS->ccpTiledAdd(getTileMapPosition(), ccp(0,-1));

    runAction(
            CCSequence::create(
                    CCSpawn::createWithTwoActions(
                            CCMoveTo::create(getSpeed(),
                                    GAMEUTILS->getScenePoint( nextPoint) ),CCRotateBy::create(getSpeed() , 180 ) )
                                    , CCCallFunc::create(this, callfunc_selector(FallingBomb::stopFalling)), NULL
                                    )
                                    );

}


void FallingBomb::onGetKill(){
    GAMEUTILS->showExplosion(getTileMapPosition());
    for (int x = -1; x <= 1; x++)
    {
        for (int y = -1; y <= 1; y++)
        {
            GameSprite* sprite;
            CCPoint p = GAMEUTILS->ccpTiledAdd(getTileMapPosition(), ccp(x, y));
            sprite = GAMEUTILS->objectAt(p, this);
            if (sprite)
            {
                sprite->getKill();
            }
        }
    }
    setState(-1);


	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(respatchFix(
        "Sounds/bomb" SOUND_EXT).c_str());
}


void FallingBomb::update() {
    if (getState() != (int) rockStateIdle) {
        return;
    }

    GameSprite* obj =
            GAMEUTILS->objectAt(GAMEUTILS->ccpTiledAdd(getTileMapPosition(), GAMEUTILS->getTiledVectorFromDirection(GameDirectiondDown)), this);

    if (canBeMoved(GameDirectiondDown)) {

        if (!obj) {
            startFalling(0.2);
            return;
        }
        if (obj->getType() != GAME_TYPE_ROBBO) {
            startFalling(0.2);
        }
        return;
    }
    //na dole jest obiekt
    if (obj) {
        if (obj->properities & PFALLABLE) {
            //i jest on typu spadającego
            if (canBeMoved(GameDirectionLeft)) {
                CCPoint nextPoint =
                        GAMEUTILS->ccpTiledAdd(getTileMapPosition(), GAMEUTILS->getTiledVectorFromDirection(GameDirectionLeft));
                CCPoint position = getTileMapPosition();
                    setPosition(GAMEUTILS->getScenePoint( nextPoint));
                    if(!canBeMoved(GameDirectiondDown)){
                        setPosition(GAMEUTILS->getScenePoint(position));

                    }else{
                        setPosition(GAMEUTILS->getScenePoint(position));
                        startRolling(GameDirectionLeft);
                        return;
                    }
            }
            if (canBeMoved(GameDirectionRigh)) {
                CCPoint nextPoint =
                        GAMEUTILS->ccpTiledAdd(getTileMapPosition(), GAMEUTILS->getTiledVectorFromDirection(GameDirectionRigh));
                CCPoint position = getTileMapPosition();
                    setPosition(GAMEUTILS->getScenePoint( nextPoint));
                    if(!canBeMoved(GameDirectiondDown)){
                        setPosition(GAMEUTILS->getScenePoint(position));

                    }else{
                        setPosition(GAMEUTILS->getScenePoint(position));
                        startRolling(GameDirectionRigh);
                        return;
                    }
            }
        }
    }
    if (getState() != rockStateIdle) {
        stopFalling();
    }
    setState((int) rockStateIdle);
}

bool FallingBomb::canBeMoved(GameDirection direction) {
    if (direction == GameDirectionUp) {
        return false;
    }
    if (getState() == rockStateRoling ) return false;
    if (getState() == BoxStateMoving ) return false;

    CCPoint point =
            GAMEUTILS->ccpTiledAdd(getTileMapPosition(), GAMEUTILS->getTiledVectorFromDirection(direction));

    if (GAMEUTILS->isPointReserved(point))return false;

    return Box::canBeMoved(direction);
}
