/*
 * Ground.h
 *
 *  Created on: 21-07-2013
 *      Author: michal
 */

#ifndef GROUND_H_
#define GROUND_H_
#include "Sprites/GameSprite.h"
class Ground: public GameSprite
{
public:
	Ground();
	virtual ~Ground();SPRITECREATION("ground.png" , Ground)
	;

};

#endif /* GROUND_H_ */
