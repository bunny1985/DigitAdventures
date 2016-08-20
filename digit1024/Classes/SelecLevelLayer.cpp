/*
 * SelecLevelLayer.cpp
 *
 *  Created on: 21 wrz 2013
 *      Author: michal
 */

#include "SelecLevelLayer.h"
#include "Common/Resources.h"
#include "GameLevelScene.h"
#include <cmath>


SelecLevelLayer::SelecLevelLayer() {
	// TODO Auto-generated constructor stub
	levelSprites = 0;

}

cocos2d::CCScene* SelecLevelLayer::scene() {


	CCScene *scene = CCScene::create();
	SelecLevelLayer *layer = SelecLevelLayer::create();
	scene->addChild(layer);
	return scene;
}



bool SelecLevelLayer::init() {



    if (!CCLayer::init())
	{
		return false;
	}
	setTouchEnabled(true);
	setTouchMode(kCCTouchesOneByOne);

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	CCSize visibleSize = CCDirector::sharedDirector()->getWinSize();
	CCSprite* background = CCSprite::create("backgroundSettings.png");
	addChild(background);
	background->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2));

	CCLabelBMFont* label = CCLabelBMFont::create("SELECT LEVEL:", GAME_MENU_FONTHD_FILE);
	label->setPosition(250, visibleSize.height - label->getContentSize().height);
	addChild(label);

	levelsContainer = CCNode::create();
	addChild(levelsContainer);
	for (int x = 1; x < 29; x++){
		AddLevelSprite(x, x <= CCUserDefault::sharedUserDefault()->getIntegerForKey(SETTINGSMAXLEVEL, 1));
	}
	ScaleStars();



	CCMenuItemLabel *back = CCMenuItemLabel::create(
		CCLabelBMFont::create("<<back", GAME_MENU_FONTHD_FILE), this,
		menu_selector(SelecLevelLayer::backCallBack));
	CCMenu *menu = CCMenu::create(back, NULL);

	menu->setPosition(100, 100);
	addChild(menu);

	return true;
}

void SelecLevelLayer::AddLevelSprite(int levelnumber, bool isActive){

	CCNode* container = CCNode::create();


	container->setTag(levelnumber);

	CCSprite* level = CCSprite::create((isActive ? "screw.png" : "screwinactive.png"));



	CCLabelBMFont* levelLabel = CCLabelBMFont::create(CCString::createWithFormat("%i", levelnumber)->getCString(), GAME_MENU_FONTHD_FILE);

	container->addChild(level);
	container->addChild(levelLabel);


	level->runAction(
		CCRepeatForever::create(
		CCSequence::createWithTwoActions(
		CCRotateTo::create(1, 10)
		, CCRotateTo::create(1, -10)
		)
		)
		);
	container->setPosition(ccp(150 + ((levelSprites % 7) * 150), 500 - ((levelSprites / 7) * 150)));
	levelsContainer->addChild(container);
	levelSprites++;
}

void SelecLevelLayer::backCallBack(CCObject * pSender) {
	CCDirector::sharedDirector()->popScene();
}





SelecLevelLayer::~SelecLevelLayer() {
	// TODO Auto-generated destructor stub
}


bool SelecLevelLayer::ccTouchBegan(CCTouch *touch, CCEvent * pEvent){

	return true;
}
void SelecLevelLayer::ccTouchEnded(CCTouch *touch, CCEvent * pEvent){
	if (std::abs(touch->getStartLocation().y - touch->getLocation().y) < 100){
		int y = levelsContainer->getPositionY();
		int x = levelsContainer->getPositionX();
		CCObject* obj;
		CCARRAY_FOREACH(levelsContainer->getChildren(), obj){

			CCNode* node = (CCNode*) obj;
			int posy = y + node->getPositionY();
			int posx = x + node->getPositionX();
			if (std::abs(touch->getLocation().y - posy) < 120 && std::abs(touch->getLocation().x - posx) < 120){
				if (CCUserDefault::sharedUserDefault()->getIntegerForKey(SETTINGSMAXLEVEL, 1) >= node->getTag()){
					GameLevelScene::level = node->getTag();
					CCDirector::sharedDirector()->replaceScene(CCTransitionFadeBL::create(0.3f, GameLevelScene::scene()));
					return;
				}
			}


		}
	}

}
void SelecLevelLayer::ccTouchCancelled(CCTouch *touch, CCEvent * pEvent){}

void SelecLevelLayer::ccTouchMoved(CCTouch *touch, CCEvent * pEvent){

	levelsContainer->setPositionY(levelsContainer->getPositionY() + touch->getDelta().y);
	ScaleStars();


}
void SelecLevelLayer::ScaleStars(){
	int y = levelsContainer->getPositionY();
	CCObject* obj;
	CCARRAY_FOREACH(levelsContainer->getChildren(), obj){
		CCNode* node = (CCNode*) obj;
		if (y + node->getPositionY() > 600) {

			node->setScale(1.0 / std::abs((600 - (y + node->getPositionY()))));

		}
		else if (y + node->getPositionY() < 100){
			node->setScale(1.0 / std::abs((100 - (y + node->getPositionY()))));
		}
		else{
			node->setScale(1.0);
		}

	}
}
