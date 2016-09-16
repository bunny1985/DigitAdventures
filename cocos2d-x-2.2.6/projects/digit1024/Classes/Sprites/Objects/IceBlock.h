/*
 * Box.h
 *
 *  Created on: 17-07-2013
 *      Author: michal
 */

#ifndef ICEBLOCK_H_
#define ICEBLOCK_H_

#include "Sprites/Objects/Box.h"
#include "Sprites/GameSprite.h"

class IceBlock: public Box
{
public:
	enum BoxStates
	{
		BoxStateIdle, BoxStateMoving, BoxStateDestroing
	};
	void makeMove(GameDirection enumGameDirection);
	IceBlock();
	virtual ~IceBlock();
	void endMove();
	void update();
	void hit(GameDirection hitDirection, GameSprite *object);
	bool canBeMoved(GameDirection direction);
	void reservePoint(){};
	void fixPosition();
	void stopMoving();
	bool pushed(GameDirection d);
	SPRITECREATION("boxSlide.png", IceBlock)
	;
protected:

private:

};



#endif /* BOX_H_ */
