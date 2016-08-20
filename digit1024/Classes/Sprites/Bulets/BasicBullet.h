/*
 * BasicBullet.h
 *
 *  Created on: 21-07-2013
 *      Author: michal
 */

#ifndef BASICBULLET_H_
#define BASICBULLET_H_
#include "Sprites/Bulets/AbstractBullet.h"
#include "Sprites/GameSprite.h"

class BasicBullet: public AbstractBullet
{
public:
	BasicBullet();
	virtual ~BasicBullet();

	SPRITECREATION("bulet.png" , BasicBullet );
};

#endif /* BASICBULLET_H_ */
