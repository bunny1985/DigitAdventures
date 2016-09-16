/*
 * MenuScene.h
 *
 *  Created on: 28-07-2013
 *      Author: michal
 */

#ifndef MENUSCENE_H_
#define MENUSCENE_H_
#include "cocos2d.h"
#include "Common/Enums.h"
USING_NS_CC;

class MenuScene: public CCLayer
{
public:
	CREATE_FUNC(MenuScene)
	;
	static bool intro;
	CCNode* sidemenupointer;;
	virtual bool init();
	static cocos2d::CCScene* scene();
	void showPresnests();
	void showTitle();
	void showMenu();
	void showRobbo();
	virtual void keyBackClicked();
	    virtual void keyMenuClicked();
	CCMenuItemImage*  mute;
	CCSize visibleSize;
	CCSpriteBatchNode* batchNode;
	void menuStartCallback(CCObject* pSender);
	void menuQuitCallback(CCObject* pSender);
	void menuSelectLevel(CCObject* pSender);
	void menuSettingsCallback(CCObject* pSender);
	void menuAboutCallback(CCObject* pSender);
	void menutogglesideMenu(CCObject* pSender);
	void menuMoreApps(CCObject* pSender);
	void menuInstruction(CCObject* pSender);
	void menuFacebook(CCObject* pSender);
	void menuRate(CCObject* pSender);
	void menuMute(CCObject* pSender);
	void setVolume();
	void initParticle();

};

#endif /* MENUSCENE_H_ */
