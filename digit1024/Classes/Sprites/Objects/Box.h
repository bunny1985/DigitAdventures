/*
 * Box.h
 *
 *  Created on: 17-07-2013
 *      Author: michal
 */

#ifndef BOX_H_
#define BOX_H_

#include "Sprites/GameSprite.h"

class Box: public GameSprite
{
public:
	enum BoxStates
	{
		BoxStateIdle, BoxStateMoving, BoxStateDestroing
	};

	Box();
	virtual ~Box();SPRITECREATION("box64.png" , Box)
	;
	bool pushed(GameDirection d);

protected:
	CCPoint nextPosition;
private:

};

#endif /* BOX_H_ */
