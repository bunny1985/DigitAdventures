/*
 * NextLevelLayer.cpp
 *
 *  Created on: 9 paź 2014
 *      Author: Michal
 */

#include <NextLevelLayer.h>

#include "GameoverScene.h"
#include "Common/Resources.h"
#include "GameLevelScene.h"
#include "SimpleAudioEngine.h"

NextLevelLayer::NextLevelLayer()
{
    // TODO Auto-generated constructor stub

}

NextLevelLayer::~NextLevelLayer()
{
    // TODO Auto-generated destructor stub
}

bool NextLevelLayer::init(){

	if (!CCLayer::init()){
		return false;
	}
	visibleSize = CCDirector::sharedDirector()->getWinSize();
	CCSprite* menuSprite = CCSprite::createWithSpriteFrameName("menu.png");
	menuSprite->setPosition(ccp((0),
		visibleSize.height / 2));
	menuSprite->runAction(CCMoveTo::create(0.5 ,  ccp((visibleSize.width/2),
		visibleSize.height / 2)));
	addChild(menuSprite);
	CCSize menuSize = menuSprite->getContentSize();
	CCLabelBMFont* labelPassed =  CCLabelBMFont::create("WELL DONE!!!", GAME_MENU_FONTHD_FILE);
	int marrgin = 40;
	labelPassed->setPositionX(menuSize.width / 2);
	labelPassed->setPositionY(menuSize.height - marrgin - (labelPassed->getContentSize().height/2));


	int bestTime = CCUserDefault::sharedUserDefault()->getIntegerForKey(CCString::createWithFormat("BESTTimeForLevle%i", GameLevelScene::level)->getCString(), INT_MAX);
	int besttries = CCUserDefault::sharedUserDefault()->getIntegerForKey(CCString::createWithFormat("BESTTriesForLevle%i", GameLevelScene::level)->getCString(), INT_MAX);
	int tries = CCUserDefault::sharedUserDefault()->getIntegerForKey(CCString::createWithFormat("LASTTriesForLevle%i", GameLevelScene::level)->getCString(), INT_MAX);
	int time = CCUserDefault::sharedUserDefault()->getIntegerForKey(CCString::createWithFormat("TimeForLevle%i", GameLevelScene::level)->getCString(), INT_MAX);

	CCLabelBMFont* labelBestTime = CCLabelBMFont::create("BEST TIME: " , GAME_MENU_FONT_FILE);
	CCLabelBMFont* labelBesttries = CCLabelBMFont::create("MIN TRIES: ", GAME_MENU_FONT_FILE);
	CCLabelBMFont* labelCurentTime = CCLabelBMFont::create("TIME: ", GAME_MENU_FONT_FILE);
	CCLabelBMFont* labelCurentTries = CCLabelBMFont::create("TRIES: ", GAME_MENU_FONT_FILE);

	CCLabelBMFont* labelBestTimeI = CCLabelBMFont::create(CCString::createWithFormat("%i", bestTime)->getCString(), GAME_MENU_FONT_FILE);
	CCLabelBMFont* labelBesttriesI = CCLabelBMFont::create(CCString::createWithFormat("%i", besttries)->getCString(), GAME_MENU_FONT_FILE);
	CCLabelBMFont* labelCurentTimeI = CCLabelBMFont::create(CCString::createWithFormat("%i", time)->getCString(), GAME_MENU_FONT_FILE);
	CCLabelBMFont* labelCurentTriesI = CCLabelBMFont::create(CCString::createWithFormat("%i", tries)->getCString(), GAME_MENU_FONT_FILE);



	int startY = menuSize.height - (2 * marrgin) - (labelPassed->getContentSize().height);
	labelBestTime->setPosition(ccp(labelBestTime->getContentSize().width / 2 + (marrgin), startY));
	labelBestTimeI->setPosition(ccp(menuSize.width -  labelBestTimeI->getContentSize().width / 2 - (marrgin), startY));

	startY -= (labelBestTime->getContentSize().height );
	labelBesttries->setPosition(ccp(labelBesttries->getContentSize().width / 2 + (marrgin), startY ));
	labelBesttriesI->setPosition(ccp(menuSize.width - labelBesttriesI->getContentSize().width / 2 - (marrgin), startY));
	startY -= (labelBestTime->getContentSize().height);
	labelCurentTime->setPosition(ccp(labelCurentTime->getContentSize().width / 2 + (marrgin), startY));
	labelCurentTimeI->setPosition(ccp(menuSize.width - labelCurentTimeI->getContentSize().width / 2 - (marrgin), startY));
	startY -= (labelBestTime->getContentSize().height);
	labelCurentTries->setPosition(ccp(labelCurentTries->getContentSize().width / 2 + (marrgin), startY));
	labelCurentTriesI->setPosition(ccp(menuSize.width - labelCurentTriesI->getContentSize().width / 2 - (marrgin), startY));

	menuSprite->addChild(labelBestTime);
	menuSprite->addChild(labelBestTimeI);
	menuSprite->addChild(labelBesttries);
	menuSprite->addChild(labelBesttriesI);
	menuSprite->addChild(labelCurentTime);
	menuSprite->addChild(labelCurentTimeI);
	menuSprite->addChild(labelCurentTries);
	menuSprite->addChild(labelCurentTriesI);


	CCSprite* robbo = CCSprite::createWithSpriteFrameName("robbo.png");
	robbo->setPosition(ccp(300, -500));
	robbo->setScale(0.75);
	robbo->runAction(CCMoveTo::create(1, ccp(300, 200)));
	addChild(robbo);




	menuSprite->addChild(labelPassed);



	CCMenuItemImage *reply = CCMenuItemImage::create("replay.png", "replay.png", this,
		menu_selector(NextLevelLayer::menuRepeat));
	CCMenuItemImage *next = CCMenuItemImage::create("next.png", "next.png", this,
		menu_selector(NextLevelLayer::menuNext));
	CCMenuItemImage *facebook = CCMenuItemImage::create("facebook.png", "facebook.png", this,
		menu_selector(NextLevelLayer::menuFacebook));
	CCMenu* menu = CCMenu::create(facebook, reply , next, NULL);
	menu->setPosition(ccp(menu->getContentSize().width / 2 - (2 * marrgin), 100));
	menuSprite->addChild(menu);
	menu->alignItemsHorizontally();


	initParticle();

	GAMEUTILS->hud->menu->setVisible(false);
	return true;



}
void NextLevelLayer::menuFacebook(CCObject* pSender){


#ifdef FBSHARE
    char buffer[500];
    sprintf(buffer ,"I'm playing #digitAdventures right now! https://www.facebook.com/BMIdeasApps Level %i passed! It was.. " , GameLevelScene::level );
        CCApplication::sharedApplication()->ShareOnFacebook( buffer);
#else
       // CCApplication::sharedApplication()->openURL("https://www.facebook.com/BMIdeasApps");
#endif

};

void NextLevelLayer::menuRepeat(CCObject* pSender){
	GAMEUTILS->reloadLevel();
};


void NextLevelLayer::menuNext(CCObject* pSender){
	if (GameLevelScene::level <= 27){
		GameLevelScene::level++;
		GAMEUTILS->reloadLevel();
		return;
	}
	GameLevelScene::level = 1;
	CCDirector::sharedDirector()->replaceScene(GameOverScene::scene());

};




void NextLevelLayer::initParticle()
{

	CCParticleSnow* m_emitter = CCParticleSnow::create();
	m_emitter->retain();
	addChild(m_emitter, 10);

	//CCPoint p = m_emitter->getPosition();
	//m_emitter->setPosition( ccp( p.x, p.y-110) );
	m_emitter->setLife(5);
	m_emitter->setLifeVar(1);

	// gravity
	m_emitter->setGravity(ccp(0, -10));

	// speed of particles
	m_emitter->setSpeed(50);
	m_emitter->setSpeedVar(30);
	m_emitter->setEmissionRate(30);

	ccColor4F startColor = m_emitter->getStartColor();
	startColor.r = 0.9f;
	startColor.g = 0.9f;
	startColor.b = 0.9f;
	m_emitter->setStartColor(startColor);

	ccColor4F startColorVar = m_emitter->getStartColorVar();
	startColorVar.b = 0.1f;
	m_emitter->setStartColorVar(startColorVar);

	m_emitter->setTexture(
		CCTextureCache::sharedTextureCache()->addImage("screw.png"));
	m_emitter->setPositionX(visibleSize.width/2);


}
