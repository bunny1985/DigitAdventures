/*
 * GameMenuLayer.h
 *
 *  Created on: 23-07-2013
 *      Author: michal
 */

#ifndef GAMEMENULAYER_H_
#define GAMEMENULAYER_H_
#include "cocos2d.h"
#include "Common/Enums.h"

USING_NS_CC;

class GameMenuLayer: public CCLayer
{
public:
	CREATE_FUNC(GameMenuLayer)
	;
	virtual bool init();
	CCLabelBMFont* livesLabel;
	CCLabelBMFont* screwsLabel;
	CCLabelBMFont* ammoLabel;
	CCLabelBMFont* keysLabel;
	CCSprite* pad;
	CCMenu* menu;
	CCSprite* firebutton;
	void showDialog(const char* message, const char* image);
	void menuResetCallback(CCObject* pSender);
	void menuResumeCallback(CCObject* pSender);
	void menuMainMenuCallback(CCObject* pSender);
	void menuSettingsCallback(CCObject* pSender);
	void menuPauseMenuCallback(CCObject* pSender);
	void menuSkipCallback(CCObject* pSender);
	void menutoggleSkipMenu(CCObject* pSender);
    virtual void keyBackClicked();
    virtual void keyMenuClicked();
#ifdef KEYBOARD_SUPPORT
	virtual void keyReleased(int keyCode);
	virtual void keyPressed(int keyCode);
#endif


	bool ccTouchBegan(CCTouch *touch, CCEvent * pEvent);

	void ccTouchEnded(CCTouch *touch, CCEvent * pEvent);
	void ccTouchCancelled(CCTouch *touch, CCEvent * pEvent);
	void ccTouchMoved(CCTouch *touch, CCEvent * pEvent);
    // default implements are used to call script callback if exist
    virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent);
	void resetPosition();
	void setupSkipMenu();
	void toggleLoading();
	void update(float dt);
private:
	GameDirection lastDirection;
	void setupPad();
	CCLabelBMFont* loadingLabel;
	/*
	 * Ustawianie Menu górnego
	 *
	 */
	void setupTopMenu();
	void addTopMenuItem(const char* spriteImage, const char* text,
			float widthpercent, CCLabelBMFont** label);


	/*
	 * Ustawianie Menu górnego
	 *
	 */
	CCSprite* skipmenuSprite;
	CCSprite* menuSprite;
	void setupGameMenu();

	GameDirection getDirectionFromPadTouch(CCTouch* touch);
	volatile bool touchlocked;
	bool isKeyReleased;
	bool shootpressed;
};

#endif /* GAMEMENULAYER_H_ */
