/*
 * Robbo.h
 *
 *  Created on: 16-07-2013
 *      Author: michal
 */

#ifndef ROBBO_H_
#define ROBBO_H_

#include "Sprites/GameSprite.h"
#include "Sprites/Objects/Collectable.h"
#include "Sprites/AbstractStateObserver.h"
#include <map>
#include "cocos2d.h"

class Robbo: public GameSprite
{

public:
	enum RobboStates
	{
		RobboStateIdle,
		RobboStateMoving,
		RobboStateDying,
		RobboStateDead,
		RobboStateTeleporting,
		RobboStateShooting
	};
	class MoveAnimationObserver: public AbstractStateObserver
	{
	public:
		MoveAnimationObserver();
		virtual void notify(GameObjectEvent);
		CCAnimation* getAnim(GameDirection);
	};

	SPRITECREATION ("ROBBO_stay.png", Robbo)
	;

	bool couldMove(GameDirection d);

	virtual void update();
	virtual ~Robbo();
	virtual void hit(GameDirection hitDirection, GameSprite* object);
	Robbo();
	virtual void endMove();
	virtual void stopMoving();
	virtual bool canBeMoved(GameDirection direction);
	virtual void makeMove(GameDirection direction);

	virtual void makeMove();
	virtual void getKill();
	virtual void onGetKill();
	void getColectable(Collectable* object);
	void shoot();

	bool OpenDoor();
	bool hasAllScrews();
	bool hasKey();

	int getKeys() const
	{
		return keys;
	}

	void setKeys(int keys)
	{
		this->keys = keys;
	}

	MoveAnimationObserver animationObserver;
	static int lives;
	void setDirection(GameDirection direction);
	int shoots;
	int keys;
	int screws;
protected:
	virtual CCAnimation* getAnimation(RobboStates state,
			GameDirection direction);
	std::map<int, CCAnimation*> animations;
	CCAnimate *animate;
	CCSequence *moveSequence;
	CCMoveBy *fixPosition_;
	GameDirection prevDirection;

	std::map<int, const char*> movingFramesMap;
	bool _hit;
	
	bool movesequenceStarted;
	bool _stopMoving;

private:
	void makeStep();
	bool crossedCenter(CCPoint newPosition);
	CCPoint prevPosition;

};

#endif /* ROBBO_H_ */
