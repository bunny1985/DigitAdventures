/*
 * OneDirectionEnemy.h
 *
 *  Created on: 19-07-2013
 *      Author: michal
 */

#ifndef ONEDIRECTIONENEMY_H_
#define ONEDIRECTIONENEMY_H_
#include "Sprites/GameSprite.h"

class AbstractEnemy: public GameSprite
{
public:
	enum EnemyStates
	{
		EnemyStateIdle, EnemyStateMoving, EnemyStateDying, EnemyStateShooting
	};
	AbstractEnemy();
	virtual ~AbstractEnemy();
	virtual bool pushed(GameDirection direction); //nic się nie dzieje
	virtual bool canBeMoved(GameDirection direction); // nie możechodzić po niczym
	virtual void shoot();
	virtual void changeShootingDirectionRandom();
	virtual void changeShootingDirection();
	virtual void startMoving();
	virtual void makeMove(GameDirection direction);
	virtual void endMove();
	virtual void stopMoving();
	virtual void fixPosition();
	virtual void update();
	virtual void hit(GameDirection hitDirection, GameSprite* object);
	virtual void setDirection(GameDirection direction);
	virtual float getChangeMoveDirFrequency() const;
	virtual void setChangeMoveDirFrequency(float changeMoveDirFrequency);
	virtual float getChangeShootDirFrequecny() const;
	virtual void setChangeShootDirFrequecny(float changeShootDirFrequecny);
	virtual int getShootDirTurn() const;
	virtual void setShootDirTurn(int shootDirTurn);
	virtual float getShootFrequency() const;
	virtual void setShootFrequency(float shootFrequency);
	virtual GameDirection getShotingDirection() const;
	virtual void setShotingDirection(GameDirection shotingDirection);

protected:
	virtual GameDirection pickDirection() = 0;
	virtual void touchTest(); // implemented
	GameDirection lastDirection;
	CCPoint lastPosition;
	int enemeyproperities;
	float shootFrequency;
	float changeMoveDirFrequency;
	float changeShootDirFrequecny;
	GameDirection shotingDirection;
	int  shootDirTurn;
	bool isShootPosssible(CCPoint point);
};

#endif /* ONEDIRECTIONENEMY_H_ */

