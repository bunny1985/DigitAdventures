/*
 * StaticSimpleCannon.cpp
 *
 *  Created on: 23-07-2013
 *      Author: michal
 */

#include "Sprites/Enemies/StaticSimpleCannon.h"
#include "Common/Resources.h"
#include <cstdlib>
StaticSimpleCannon::StaticSimpleCannon() :
		Cannon()
{
}

StaticSimpleCannon::~StaticSimpleCannon()
{
	// TODO Auto-generated destructor stub
}

void StaticSimpleCannonRotating::shoot(){
	if (float(std::rand() % 100) <= shootFrequency){
		direction = (GameDirection) (std::rand() % 4);
		shotingDirection = direction;
		int angle = (int) direction * 90;
		runAction(CCRotateTo::create(0.3, angle));
	}
	AbstractEnemy::shoot();
}

