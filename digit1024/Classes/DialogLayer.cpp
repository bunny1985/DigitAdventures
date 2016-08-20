/*
 * DialogLayer.cpp
 *
 *  Created on: 22 wrz 2014
 *      Author: Michal
 */

#include <DialogLayer.h>
#include "Common\Resources.h"
#include "GameLevelScene.h"



DialogLayer::DialogLayer()
{
    // TODO Auto-generated constructor stub

}

bool DialogLayer::init(){
	if (!CCLayer::init()){
		return false;
	}
	//GAMEUTILS->hud->setVisible(false);
	GAMEUTILS->pauseGame();
	dialogSize = CCSize(720, 323);
	dialogPoint = ccp(275, 610);
	visibleSize  = CCDirector::sharedDirector()->getWinSize();

	CCLabelBMFont* textLabel = CCLabelBMFont::create("<<BACK", GAME_MENU_FONTHD_FILE);
	
	
	CCMenuItemLabel *backMemnuItem = CCMenuItemLabel::create(textLabel, this, menu_selector(DialogLayer::BackCallBack));
	
	CCMenu* MenuItems = CCMenu::create(backMemnuItem, NULL);
	MenuItems->setPosition(ccp(1280/2, 100));
	addChild(MenuItems);


	return true;
	
}
void DialogLayer::BackCallBack(CCObject* pSender){
	GAMEUTILS->resumeGame();
	this->removeFromParentAndCleanup(true);
}
void DialogLayer::setImage(const char* fileName){
	CCSprite* image = CCSprite::create(fileName);
	addChild(image);
	image->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2));
	image->setZOrder(-1);
}
void DialogLayer::setText(const char* text){

	CCLabelBMFont* textLabel =  CCLabelBMFont::create(text, GAME_MENU_FONT_FILE, dialogSize.width, kCCTextAlignmentLeft);
	
	textLabel->setPosition(ccp(dialogPoint.x + textLabel->getContentSize().width / 2, dialogPoint.y - textLabel->getContentSize().height / 2));
	addChild(textLabel);

}








DialogLayer::~DialogLayer()
{
    // TODO Auto-generated destructor stub
}

