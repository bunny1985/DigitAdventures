/*
 * Teleport.h
 *
 *  Created on: 19-07-2013
 *      Author: michal
 */

#ifndef TELEPORT_H_
#define TELEPORT_H_
#include "Sprites/GameSprite.h"
#include <cocos2d.h>

class Teleport: public GameSprite
{
public:
	enum BoxStates
	{
		TeleportStateIdle, TeleportStateTeleporting
	};
	SPRITECREATION("teleport.png" , Teleport)
	;
	Teleport();
	virtual ~Teleport();
	//virtual bool pushed(GameDirection direction);
	virtual void hit(GameDirection hitDirection, GameSprite *object);
	
	int element;
	int sequence;
	void applyProperties(CCDictionary* d);
	void setTeleportPoints(CCPoint pointHitLeft, CCPoint pointHitRight,
			CCPoint pointHitUp, CCPoint pointHitDown);
	bool pushed(GameDirection direction){ return false; }
protected:
	CCPoint _pointHitLeft, _pointHitRight, _pointHitUp, _pointHitDown;
private:

};

#endif /* TELEPORT_H_ */
