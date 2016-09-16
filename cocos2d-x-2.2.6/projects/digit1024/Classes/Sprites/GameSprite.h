/*
 * GameSprite.h
 *
 *  Created on: 16-07-2013
 *      Author: michal
 */

#ifndef GAMESPRITE_H_
#define GAMESPRITE_H_
#include <cocos2d.h>
#include "Common/Enums.h"
#define SPRITECREATION(__FRAME__, __CLASS__)  static __CLASS__* create(){              \
		                                      __CLASS__* instance = new __CLASS__();   \
		                                      instance->postCreate(__FRAME__);         \
		                                      return instance;                         \
											  };									   \
											   \


USING_NS_CC;

class AbstractStateObserver;
class GameSprite: public CCSprite
{
public:

	GameSprite();
	virtual ~GameSprite();
	virtual GameDirection getMoveDirection();
	virtual float getSpeed();
	
	virtual CCPoint getTileMapPosition();
	virtual CCPoint getTileMapNextPosition();

	virtual bool canBeMoved(GameDirection direction);
	virtual bool pushed(GameDirection direction);
	virtual bool entered(GameDirection direction);
	virtual bool collected(GameDirection direction);
	virtual bool getShoot(GameDirection direction);
	virtual void getKill();

	virtual void hit(GameDirection hitDirection, GameSprite* object);
	virtual void setState(int newState);
	virtual int getState();

	virtual void applyProperties(CCDictionary* dictionary);
	virtual void start()
	{
	}
	;
	virtual void update();
	virtual void startMoving()
	{
	}
	;
	virtual void fixPosition();

	virtual int getType()
	{
		return type;
	}
	;

	virtual bool isDestroyed();
	virtual float getRotationAngle();

	virtual void makeMove(GameDirection);
	virtual void endMove();
	virtual void stopMoving();
	const CCPoint& getReservedPoint() const;
	void reservePoint();
	void releasePoint();
	
	int properities; // flagi  z ustawieniami
	int currentState;
protected:

	int type;

	GameDirection direction;

	float speed; // will be sec/speed in movement
	std::vector<AbstractStateObserver*> stateObservers;
	virtual GameSprite* postCreate(const char* framename);
	CCPoint reservedPoint;
private:

};

#endif /* GAMESPRITE_H_ */
