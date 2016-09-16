/*
 * EnterableGround.h
 *
 *  Created on: Mar 25, 2014
 *      Author: Michal
 */

#ifndef ENTERABLEGROUND_H_
#define ENTERABLEGROUND_H_
#include "Ground.h"

class EnterableGround  : public Ground{
public:
	EnterableGround();
	virtual ~EnterableGround();
	SPRITECREATION("enterableGround.png" , EnterableGround);
	bool pushed(GameDirection direction);
	virtual bool canBeMoved(GameDirection direction);
};

#endif /* ENTERABLEGROUND_H_ */
