/*
 * GameMenuLayer.cpp
 *
 *  Created on: 23-07-2013
 *      Author: michal
 */

#include "GameMenuLayer.h"
#include "GameLevelScene.h"
#include "Common/Resources.h"
#include "cmath"
#include "MenuScene.h"
#include "SimpleAudioEngine.h"
#include "Common/RESPATH.h"
#include "Common/PaymentService.h"
#include "Common/SkipLevelService.h"
#include "GameOverScene.h"


#define GAMELOG ////

void GameMenuLayer::menuSkipCallback(CCObject* pSender){
    SkipLevelService service;
    bool skiped =service.skipLevel();
    if(skiped){
        if (GameLevelScene::level <= 27){
                GameLevelScene::level++;
                GAMEUTILS->reloadLevel();
                return;
            }
            GameLevelScene::level = 1;
            CCDirector::sharedDirector()->replaceScene(GameOverScene::scene());
    }
    GAMEUTILS->resumeGame();
}

bool GameMenuLayer::init() {
	shootpressed = false;
	isKeyReleased = true;
	CCLayer::init();
    this->setTouchEnabled(true);
    setKeypadEnabled(true);
    setTouchPriority(kCCMenuHandlerPriority + 10);
    setTouchMode(kCCTouchesOneByOne);


#ifdef KEYBOARD_SUPPORT
	this->setKeyboardEnabled(false);
	this->setKeyboardEnabled(true);
#endif

	CCLog("INICJOWANIE WARSTWY MENU");


	addTopMenuItem("key.png", "0", 0.1f, &keysLabel);
	CCLog("dodano pozycję menu klucz");
	addTopMenuItem("screw.png", "0", 0.25f, &screwsLabel);
	CCLog("dodano pozycję menu śróbkę");

	CCLog("dodano pozycje menu życia");
	addTopMenuItem("ammo.png", "0", 0.50f, &ammoLabel);
	CCLog("dodano pozycje menu  amunicję");
	setupPad();
	setupSkipMenu();
	setupGameMenu();

	CCSize visibleSize = CCDirector::sharedDirector()->getWinSize();
	loadingLabel = CCLabelBMFont::create("Loading", GAME_MENU_FONTHD_FILE);
	loadingLabel->setPosition(ccp(visibleSize.width/2 ,visibleSize.height/2));
	addChild(loadingLabel);


	CCMenuItemImage *skipbutton = CCMenuItemImage::create("giveUp.png", "giveUp.png", "giveUp.png", this, menu_selector(GameMenuLayer::menutoggleSkipMenu));
	CCMenuItemImage *resetbutton = CCMenuItemImage::create("settingss.png", "settingss.png", "settingss.png", this, menu_selector(GameMenuLayer::menuPauseMenuCallback));
	CCMenuItemImage *pauseMenu = CCMenuItemImage::create("replays.png", "replays.png", "replays.png", this, menu_selector(GameMenuLayer::menuResetCallback));


	CCSprite*  ribbon   = CCSprite::createWithSpriteFrameName("ribbon.png");
	ribbon->setPosition(ccp(ribbon->getContentSize().width/2  , visibleSize.height - (ribbon->getContentSize().height/2) ));

	addChild(ribbon);
	menu = CCMenu::create(skipbutton , resetbutton,pauseMenu , NULL);
	menu->alignItemsHorizontally();
	menu->setPosition(
			ccp( visibleSize.width - (pauseMenu->getContentSize().width*2) , keysLabel->getPosition().y ));
	addChild(menu);


	toggleLoading();

	//this->schedule( schedule_selector(GameMenuLayer::update), 0.1 );
	this->schedule(schedule_selector(GameMenuLayer::update), 0.05f);


	return true;

}
void GameMenuLayer::keyBackClicked(){
    menuMainMenuCallback(this);
}
void GameMenuLayer::keyMenuClicked(){
    this->menuPauseMenuCallback(this);
}


#ifdef KEYBOARD_SUPPORT
void GameMenuLayer::keyPressed(int keyCode) {
	//if (GAMEUTILS->current_state ==2 ||GAMEUTILS->current_state ==0 )return;
	if(keyCode==KEY_D|| keyCode==KEY_Right )
	{
		lastDirection = GameDirectionRigh;
		isKeyReleased = false;
		GAMEUTILS->robboSprite->makeMove(lastDirection);
	}
	else if(keyCode==KEY_A|| keyCode==KEY_Left)
	{
		lastDirection = GameDirectionLeft;
		GAMEUTILS->robboSprite->makeMove(lastDirection);
		isKeyReleased = false;
	}
	else if(keyCode==KEY_W || keyCode==KEY_Up)
	{
		lastDirection = GameDirectionUp;
		GAMEUTILS->robboSprite->makeMove(lastDirection);
		isKeyReleased = false;
	}
	else if(keyCode==KEY_S || keyCode==KEY_Down)
	{
		lastDirection = GameDirectiondDown;
		GAMEUTILS->robboSprite->makeMove(lastDirection);
		isKeyReleased = false;
	}
	else if(keyCode==KEY_Space ||keyCode==KEY_RightShift)
	{
		if (!shootpressed){
			shootpressed = true;
			GAMEUTILS->robboSprite->shoot();
		}

	}

	CCLOG("Key with keycode %i pressed", keyCode);
}

void GameMenuLayer::keyReleased(int keyCode) {
	if (keyCode == KEY_W || keyCode == KEY_A || keyCode == KEY_S
			|| keyCode == KEY_D || keyCode == KEY_Left || keyCode == KEY_Right
			|| keyCode == KEY_Up || keyCode == KEY_Down) {

		GAMEUTILS->robboSprite->stopMoving();
		isKeyReleased = true;
	}
	if (keyCode == KEY_Space || keyCode == KEY_RightShift){
		shootpressed = false;
	}

	CCLOG("Key with keycode %i released", keyCode);
}
#endif

void GameMenuLayer::menuPauseMenuCallback(CCObject* pSender) {
	CCLog("MenuRequest");
	CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseAllEffects();
	GAMEUTILS->pauseGame();
	menuSprite->setVisible(true);
	menuSprite->runAction(CCFadeIn::create(0.5));

}

void GameMenuLayer::menuResetCallback(CCObject* pSender) {
	CCLog("RESET REQUEST");
	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();
	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
	GAMEUTILS->reloadLevel();
}

bool GameMenuLayer::ccTouchBegan(CCTouch* touch, CCEvent* pEvent) {


	//if (GAMEUTILS->current_state ==2 ||GAMEUTILS->current_state ==0 )return false;
	CCPoint vector = ccpSub(pad->getPosition(), touch->getLocation());
	bool isPadTouched = !(std::abs((int) (vector.x))
			> pad->getContentSize().width * 2
			|| std::abs((int) (vector.y)) > pad->getContentSize().height * 2);

	if (isPadTouched) {
		isKeyReleased = false;
		lastDirection = getDirectionFromPadTouch(touch);
		GAMEUTILS->robboSprite->makeMove(lastDirection);
		return true;
	}
	vector = ccpSub(firebutton->getPosition(), touch->getLocation());
	bool isFireTouched = !(std::abs((int) (vector.x))
			> firebutton->getContentSize().width * 2
			|| std::abs((int) (vector.y))
					> firebutton->getContentSize().height * 2);
	if (isFireTouched) {
		GAMEUTILS->robboSprite->shoot();
	}

	return false;
}

void GameMenuLayer::ccTouchEnded(CCTouch* touch, CCEvent* pEvent) {
	GAMEUTILS->robboSprite->stopMoving();

	CCPoint vector = ccpSub(pad->getPosition(), touch->getLocation());
	bool isPadTouched = !(std::abs((int) (vector.x))
			> pad->getContentSize().width * 2
			|| std::abs((int) (vector.y)) > pad->getContentSize().height * 2);

	if (isPadTouched) {
		isKeyReleased = true;
	}
}

void GameMenuLayer::ccTouchCancelled(CCTouch* touch, CCEvent* pEvent) {
	GAMEUTILS->robboSprite->stopMoving();

}

void GameMenuLayer::ccTouchMoved(CCTouch* touch, CCEvent* pEvent) {

	//if (GAMEUTILS->current_state == 2 || GAMEUTILS->current_state == 0)return;
	CCPoint vector = ccpSub(pad->getPosition(), touch->getLocation());
	bool isPadTouched = !(std::abs((int) (vector.x))
			> pad->getContentSize().width * 2
			|| std::abs((int) (vector.y)) > pad->getContentSize().height * 2);

	if (isPadTouched) {
		if (getDirectionFromPadTouch(touch) != lastDirection || GAMEUTILS->robboSprite->getState() == 0)
		{
			lastDirection = getDirectionFromPadTouch(touch);
			GAMEUTILS->robboSprite->makeMove(lastDirection);
		}


	}

}

void GameMenuLayer::setupPad() {
	CCSize visibleSize = CCDirector::sharedDirector()->getWinSize();
	/*
	 * Ustawianie dotyku
	 */
	touchlocked = false;

	/*
	 * Ustawianie pada
	 */
	pad = CCSprite::create("pad.png");
	pad->setPosition(
			ccp(0+visibleSize.width*0.05f +pad->getContentSize().width/2 ,0+visibleSize.height*0.05f +pad->getContentSize().height/2 ));
	addChild(pad);

	firebutton = CCSprite::create("firebutton.png");
	firebutton->setPosition(
			ccp(visibleSize.width*0.95f -firebutton->getContentSize().width/2 ,0+visibleSize.height*0.1f +firebutton->getContentSize().height/2 ));
	addChild(firebutton);

}

void GameMenuLayer::setupTopMenu() {
}
void GameMenuLayer::menutoggleSkipMenu(CCObject* sender){
    skipmenuSprite->setVisible(! skipmenuSprite->isVisible());
    if(skipmenuSprite->isVisible()){
        GAMEUTILS->resumeGame();
    }
}

void GameMenuLayer::setupSkipMenu() {
    GAMEUTILS->pauseGame();
    CCSize visibleSize = CCDirector::sharedDirector()->getWinSize();
    skipmenuSprite = CCSprite::createWithSpriteFrameName("menu.png");
    skipmenuSprite->setPosition(ccp(visibleSize.width/2 ,
            visibleSize.height/2 ));
    addChild(skipmenuSprite);
    CCLabelBMFont* labelSkip = CCLabelBMFont::create("Skip level", GAME_MENU_FONTHD_FILE);
    labelSkip->setPosition(ccp(skipmenuSprite->getContentSize().width / 2  , skipmenuSprite->getContentSize().height -50  ));
    skipmenuSprite->addChild(labelSkip);


    CCLabelBMFont* labelSkipdescription = CCLabelBMFont::create("You can skip Level if you need by buying skip points", GAME_MENU_FONT_FILE);
    labelSkipdescription->setPosition(ccp(skipmenuSprite->getContentSize().width / 2 , skipmenuSprite->getContentSize().height -110  ));
    skipmenuSprite->addChild(labelSkipdescription);
    CCLabelBMFont* labelSkipdescription3 = CCLabelBMFont::create("There are 3 skips in a package", GAME_MENU_FONT_FILE);
    labelSkipdescription3->setPosition(ccp(skipmenuSprite->getContentSize().width / 2 , skipmenuSprite->getContentSize().height -170  ));
    skipmenuSprite->addChild(labelSkipdescription3);

    //skipmenuSprite->addChild(labelSkipdescription);
    SkipLevelService skiplevelService;

    CCLabelBMFont* labelSkipdescription2 = CCLabelBMFont::create(CCString::createWithFormat("Currently you have %i skips", skiplevelService.getNumberOfSkips())->getCString(), GAME_MENU_FONT_FILE);
    labelSkipdescription2->setPosition(ccp((visibleSize.width/2) - (labelSkipdescription2->getContentSize().width /2) , skipmenuSprite->getContentSize().height -230  ));
    skipmenuSprite->addChild(labelSkipdescription2);


    CCLabelBMFont* labelSkipdescription4 = CCLabelBMFont::create("Continue?", GAME_MENU_FONTHD_FILE);
    labelSkipdescription4->setPosition(ccp((visibleSize.width/2) - (labelSkipdescription2->getContentSize().width /2) , skipmenuSprite->getContentSize().height -320  ));
    skipmenuSprite->addChild(labelSkipdescription4);



    int marrgin = 20;
    CCMenuItemImage *ok = CCMenuItemImage::create("ok.png", "ok.png", this,
    menu_selector(GameMenuLayer::menuSkipCallback));
    CCMenuItemImage *no = CCMenuItemImage::create("no.png", "no.png", this,
    menu_selector(GameMenuLayer::menutoggleSkipMenu));
    CCMenu* menu = CCMenu::create(no, ok, NULL);

    menu->setPosition(ccp(menu->getContentSize().width / 2 - (2 * marrgin), 100));
    menu->alignItemsHorizontally();
    skipmenuSprite->addChild(menu);
    skipmenuSprite->setVisible(false);


}


void GameMenuLayer::setupGameMenu() {
	CCSize visibleSize = CCDirector::sharedDirector()->getWinSize();
	menuSprite = CCSprite::createWithSpriteFrameName("menu.png");
	menuSprite->setPosition(ccp((visibleSize.width/2) ,
			visibleSize.height/2 ));
	addChild(menuSprite);
	;
	CCMenuItemLabel *resume = CCMenuItemLabel::create(
			CCLabelBMFont::create("RESUME", GAME_MENU_FONTHD_FILE), this,
			menu_selector(GameMenuLayer::menuResumeCallback));
	CCMenuItemLabel *reset = CCMenuItemLabel::create(
			CCLabelBMFont::create("Reset", GAME_MENU_FONTHD_FILE), this,
			menu_selector(GameMenuLayer::menuResetCallback));
	CCMenuItemLabel *mainMenu = CCMenuItemLabel::create(
			CCLabelBMFont::create("Main Menu", GAME_MENU_FONTHD_FILE), this,
			menu_selector(GameMenuLayer::menuMainMenuCallback));
	/*CCMenuItemLabel *settings = CCMenuItemLabel::create(
			CCLabelBMFont::create("Game Settings", GAME_MENU_FONTHD_FILE), this,
			menu_selector(GameMenuLayer::menuSettingsCallback));
	 */
	CCMenu* pauseMenu = CCMenu::create(resume, reset, mainMenu,  NULL);

	CCSize s = CCDirector::sharedDirector()->getWinSize();
	pauseMenu->setPosition(ccp(s.width/2, s.height/2));
	pauseMenu->setPositionX(menuSprite->getContentSize().width / 2);
	pauseMenu->setPositionY(menuSprite->getContentSize().height / 2);
	pauseMenu->alignItemsVertically();
	menuSprite->addChild(pauseMenu);
	menuSprite->setVisible(false);

}

void GameMenuLayer::addTopMenuItem(const char* spriteImage, const char* text,
		float widthpercent, CCLabelBMFont** label) {
	CCSize visibleSize = CCDirector::sharedDirector()->getWinSize();
	CCSprite* sprite = CCSprite::createWithSpriteFrame(
			CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(
					spriteImage));
	sprite->setPosition(
			ccp(( visibleSize.width* widthpercent) - sprite->getContentSize().width , visibleSize.height - sprite->getContentSize().height/2));
	(*label) = CCLabelBMFont::create(text, GAME_MENU_FONT_FILE);
	(*label)->setPosition(
			ccp( sprite->getPosition().x + sprite->getContentSize().width , visibleSize.height - (sprite->getContentSize().height/2) ));
	this->addChild((*label), 1);
	this->addChild(sprite, 1);

}

void GameMenuLayer::menuResumeCallback(CCObject* pSender) {
	CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
	CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeAllEffects();
	GAMEUTILS->resumeGame();
	menuSprite->setVisible(false);
}

void GameMenuLayer::menuMainMenuCallback(CCObject* pSender) {
	CCDirector::sharedDirector()->replaceScene(MenuScene::scene());
}

void GameMenuLayer::menuSettingsCallback(CCObject* pSender) {
}

void GameMenuLayer::toggleLoading() {
	loadingLabel->setVisible(false);
}

void GameMenuLayer::ccTouchesBegan(CCSet* pTouches, CCEvent* pEvent) {


	for (CCSetIterator it = pTouches->begin(); it != pTouches->end(); it++) {
		CCTouch* touch = dynamic_cast<CCTouch*>(*it);
		if (touch == NULL)
			break;
		this->ccTouchBegan(touch, NULL);
	}
}

void GameMenuLayer::ccTouchesMoved(CCSet* pTouches, CCEvent* pEvent) {


}
void GameMenuLayer::ccTouchesEnded(CCSet* pTouches, CCEvent* pEvent) {

}

void GameMenuLayer::ccTouchesCancelled(CCSet* pTouches, CCEvent* pEvent) {

}

void GameMenuLayer::update(float dt) {
	if(! isKeyReleased){
		GAMEUTILS->robboSprite->makeMove(lastDirection);
	}
}

GameDirection GameMenuLayer::getDirectionFromPadTouch(CCTouch* touch) {
	CCPoint vector = ccpSub(pad->getPosition(), touch->getLocation());
	int ax = std::abs((int) vector.x);
	int ay = std::abs((int) (vector.y));
	if (ax > ay) {
		if (vector.x < 0) {
			return GameDirectionRigh;
		} else {
			return GameDirectionLeft;
		}
	} else {
		if (vector.y < 0) {
			return GameDirectionUp;
		} else {
			return GameDirectiondDown;
		}

	}
	return GameDirectionUnknown;

}

void GameMenuLayer::resetPosition(){
	setPosition(ccp(0, 0));
}
