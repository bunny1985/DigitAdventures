/*
 * OptionsLayer.cpp
 *
 *  Created on: 21 wrz 2013
 *      Author: michal
 */

#include "GameOverScene.h"
#include "GameLevelScene.h"
#include "Common/Resources.h"
#include "SimpleAudioEngine.h"
#include "MenuScene.h"
#include "CCShake.h"
#include "Common\RESPATH.h"


GameOverScene::GameOverScene() {
	// TODO Auto-generated constructor stub

}

bool GameOverScene::init() {
	if (!CCLayer::init())
	{
		return false;
	}
	
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(respatchFix(
		"Sounds/music/Mellowtron" SOUND_EXT).c_str(), true);
	GameLevelScene::batchNode = CCSpriteBatchNode::create("robbo.png");


	CCSize winSize = CCDirector::sharedDirector()->getWinSize();


	visibleSize = CCDirector::sharedDirector()->getWinSize();
	CCSprite* background = CCSprite::create("space.png");
	background->setScaleY(2.0);
	background->runAction(CCMoveBy::create(30, ccp(0, 380)));
	addChild(background);
	background->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 4));
	initParticle();



	CCSprite* planet = CCSprite::create("planet.png");
	addChild(planet);
	//planet->setPosition(ccp(visibleSize.width / 2, (-visibleSize.height / 2) - planet->getContentSize().height / 2));
	planet->setPosition(ccp(visibleSize.width / 2, planet->getContentSize().height / 2));





	 robbo = CCSprite::createWithSpriteFrameName("robbo.png");
	
	CCPoint dest = ccp(300, 550);
	robbo->setPosition(ccp(370, 380));
	addChild(robbo);
	
	//robbo->runAction(robboAnim);

	ShowSpaceShip();



	return true;
}


void GameOverScene::ShowSpaceShip(){
	CCSprite* ship = CCSprite::createWithSpriteFrameName("robboShip.png");
	ship->setPosition(ccp(-visibleSize.width / 2, visibleSize.height / 2 + 100));
	ship->setScale(0.1);
	CCSpawn* flightAnim1 = CCSpawn::create(CCScaleTo::create(1.5, 0.1), CCMoveTo::create(3, ccp(2000, 1000)), NULL);
	CCSpawn* flightAnim2 = CCSpawn::create(CCScaleTo::create(1.5, 0.2), CCMoveTo::create(3, ccp(300, 650)), NULL);

	CCSpawn* flightAnim3 = CCSpawn::create(CCScaleTo::create(2, 0.5), CCMoveTo::create(2, ccp(2000, 600)), NULL);
	

	CCCallFunc* callback = CCCallFunc::create(this, callfunc_selector(GameOverScene::robboFlyAway));

	ship->runAction(CCSequence::create(flightAnim1, flightAnim2, callback ,  CCShake::actionWithDuration(1.5 , 0 , 0),  flightAnim3, NULL));
	addChild(ship);
}

void GameOverScene::robboFlyAway(){

	CCPoint dest = ccp(300, 650);
	robbo->runAction(CCSpawn::create(CCSpawn::create(CCScaleTo::create(1 , 0.0), CCJumpTo::create(1 , dest , 50 , 1)), NULL ));

	CCLabelBMFont* label = CCLabelBMFont::create("GAME OVER", GAME_MENU_FONTHD_FILE);
	addChild(label);
	label->setPosition(ccp(-(visibleSize.width / 2), visibleSize.height / 2));
	CCCallFunc* callback = CCCallFunc::create(this, callfunc_selector(GameOverScene::showCredits));
	label->runAction(CCSequence::create(CCShake::actionWithDuration(2,0,0), CCMoveTo::create(1, ccp(visibleSize.width / 2, visibleSize.height / 2)), CCScaleTo::create(2.0, 3, 3), CCShake::actionWithDuration(2, 0, 0),  CCMoveTo::create(1, ccp(visibleSize.width / 2, visibleSize.height * 2)), callback ,   NULL));

}



cocos2d::CCScene* GameOverScene::scene() {
	CCScene *scene = CCScene::create();
	GameOverScene *layer = GameOverScene::create();
	scene->addChild(layer);
	return scene;
}

void GameOverScene::backCallcBack(CCObject * pSender) {
	CCDirector::sharedDirector()->popScene();
}

GameOverScene::~GameOverScene() {
	// TODO Auto-generated destructor stub
}

void GameOverScene::initParticle()
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

}


void GameOverScene::showCredits(){
	char*  text = "Digit Adventures by: Michal Banas\n "
		"BMIdeas 2013-2014\n"
		"Thank you for buying \n"
		"---------------------------------\n\n\n"
		"I hope you enjoyed this game\n"
		"If so, please leave e review in a store, \n"
		"Live a message, on Facebook or just tell your friends about it \n"
		"I'm always looking for a feedback - positive and negative\n"
		"So please contact me directly\n"
		"---------------------------------\n\n\n"
		"Digit Adventures by: Michal Banas\n "
		"BMIdeas 2013-2014\n"
		"Thank you for buying \n"

		;


	CCLabelBMFont* textLabel = CCLabelBMFont::create(text, GAME_MENU_FONT_FILE, 1000, kCCTextAlignmentLeft);
	textLabel->setPosition(ccp(640,  - textLabel->getContentSize().height + 300));
	addChild(textLabel);
	CCCallFunc* callback = CCCallFunc::create(this, callfunc_selector(GameOverScene::showMenuScene));
	textLabel->runAction(CCSequence::create( CCMoveTo::create(20, (ccp(640, visibleSize.height-300)))  , CCShake::actionWithDuration(20 , 0 , 0 ) , callback , NULL));
}
void GameOverScene::showMenuScene(){
	CCDirector::sharedDirector()->replaceScene(MenuScene::scene());
	MenuScene::intro = false;
	GameLevelScene::level = 1;

}