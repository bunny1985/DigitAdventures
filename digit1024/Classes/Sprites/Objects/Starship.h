/*
 * Starship.h
 *
 *  Created on: 24-07-2013
 *      Author: michal
 */

#ifndef STARSHIP_H_
#define STARSHIP_H_
#include "Sprites/Objects/Box.h"
class Starship: public Box
{
public:
	Starship();
	virtual ~Starship();SPRITECREATION("starship.png" , Starship )
	;
	virtual void getKill();
	virtual bool pushed(GameDirection direction);
	virtual void nextLevel();
	virtual bool canBeMoved(GameDirection direction);
};

#endif /* STARSHIP_H_ */
