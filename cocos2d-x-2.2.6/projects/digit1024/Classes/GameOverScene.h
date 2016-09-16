/*
 * OptionsLayer.h
 *
 *  Created on: 21 wrz 2013
 *      Author: michal
 */

#ifndef GAMEOVERSCENE_H_
#define GAMEOVERSCENE_H_
#include "cocos2d.h"
#include "Common/Enums.h"
USING_NS_CC;





class GameOverScene : public CCLayer{
public:

	CREATE_FUNC(GameOverScene)
	;
	GameOverScene();
	virtual ~GameOverScene();
	static cocos2d::CCScene* scene();
	virtual bool init();
	void backCallcBack(CCObject * pSender);
	void initParticle();
	void ShowSpaceShip();
	CCSize visibleSize;
	void robboFlyAway();
	void showCredits();
	void showMenuScene();
	CCSprite* robbo;
};

#endif /* OPTIONSLAYER_H_ */
