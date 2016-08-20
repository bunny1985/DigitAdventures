/*
 * FallingBomb.h
 *
 *  Created on: 29 sie 2014
 *      Author: Michal
 */

#ifndef FALLINGBOMB_H_
#define FALLINGBOMB_H_
#include "Rock.h"
class FallingBomb: public Rock
{
    public:
    FallingBomb();
    SPRITECREATION("FallingBomb.png" , FallingBomb);
    void stopFalling();
    void getKill();
    void onGetKill();
    void startFalling(float delay);
    virtual void update();
    bool canBeMoved(GameDirection direction);
};

#endif /* FALLINGBOMB_H_ */
