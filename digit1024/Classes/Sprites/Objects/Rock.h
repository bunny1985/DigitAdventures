/*
 * Rock.h
 *
 *  Created on: Mar 26, 2014
 *      Author: Michal
 */

#ifndef ROCK_H_
#define ROCK_H_
#include "Common\Resources.h"
#include "Box.h"

class Rock :public Box {
public:
	enum rockStates {
		rockStateIdle, rockStateMoving , rockStateRoling, rockStateFalling
	};
	Rock();
	virtual ~Rock();
	SPRITECREATION("rock.png" , Rock);
	virtual bool canBeMoved(GameDirection direction);
	virtual void update();
	void startFalling(float dt);
	void makeMove(GameDirection direction);
	void stopFalling();
	void startRolling(GameDirection direction);
	void stopRolling();
	bool pushed(GameDirection direction);
	
	
};

#endif /* ROCK_H_ */
