/*
 * OptionsLayer.cpp
 *
 *  Created on: 21 wrz 2013
 *      Author: michal
 */

#include "OptionsLayer.h"
#include "Common/Resources.h"
#include "SimpleAudioEngine.h"


OptionsLayer::OptionsLayer() {
	// TODO Auto-generated constructor stub

}

bool OptionsLayer::init() {
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
	//"extensions\sliderProgress.png"
	//	"sliderThumb.png"
	CCLabelBMFont* label = CCLabelBMFont::create("Sound Volume:", GAME_MENU_FONTHD_FILE);
	int y = visibleSize.height - label->getContentSize().height;
	label->setPosition(250, y);

	addChild(label);
	 soundVolumeSlider = CCSprite::create("extensions/sliderProgress.png");

			soundPointer = CCSprite::create("extensions/sliderThumb.png");
			
			int posx = CCUserDefault::sharedUserDefault()->getFloatForKey(SETTINGSOUNDSVOLUME, 1.0f) * 250;
			soundPointer->setPositionY(7);
			soundPointer->setPositionX(posx);

			soundVolumeSlider->addChild(soundPointer);
			y -= 100;
			soundVolumeSlider->setPosition(ccp(250, y));
			addChild(soundVolumeSlider);

			y -= 100;
			CCLabelBMFont* labelmusic = CCLabelBMFont::create("music Volume:", GAME_MENU_FONTHD_FILE);
			 
			labelmusic->setPosition(250, y);
			addChild(labelmusic);

			y -= 100;
			 musicVolumeSlider = CCSprite::create("extensions/sliderProgress.png");

			musicPointer = CCSprite::create("extensions/sliderThumb.png");
			posx = CCUserDefault::sharedUserDefault()->getFloatForKey(SETTINGSMUSICVOLUME, 0.2f)*250;

			musicPointer->setPositionY(7);
			musicPointer->setPositionX(posx);
			musicVolumeSlider->addChild(musicPointer);
			y -= 100;
			musicVolumeSlider->setPosition(ccp(250, y));
			addChild(musicVolumeSlider);


			y = visibleSize.height - label->getContentSize().height;
			CCMenuItemLabel *back = CCMenuItemLabel::create(
				CCLabelBMFont::create("<<back", GAME_MENU_FONTHD_FILE), this,
				menu_selector(OptionsLayer::backCallcBack));

			
			CCMenuItemLabel *instruction = CCMenuItemLabel::create(
				CCLabelBMFont::create("INSTRUCTION", GAME_MENU_FONTHD_FILE), this,
				menu_selector(OptionsLayer::openInstruction));
			
			
			CCMenuItemLabel *moreapps = CCMenuItemLabel::create(
				CCLabelBMFont::create("MORE BMIDEAS APPS", GAME_MENU_FONTHD_FILE), this,
				menu_selector(OptionsLayer::openMoreApps));
			moreapps->setPositionY(100);
			CCMenu *menu = CCMenu::create(instruction, NULL);
			CCMenu *menu2 = CCMenu::create( back, NULL);
			menu->setPosition(900, y-200);
			menu2->setPosition(100, 100);
			
			addChild(menu);
			addChild(menu2);

		return true;
}



cocos2d::CCScene* OptionsLayer::scene() {
	CCScene *scene = CCScene::create();
	OptionsLayer *layer = OptionsLayer::create();
	scene->addChild(layer);
	return scene;
}

void OptionsLayer::backCallcBack(CCObject * pSender) {
	CCDirector::sharedDirector()->popScene();
}

OptionsLayer::~OptionsLayer() {
	// TODO Auto-generated destructor stub
}

bool OptionsLayer::ccTouchBegan(CCTouch *touch, CCEvent * pEvent){
	int y = touch->getStartLocation().y;
	int x = touch->getStartLocation().x;
	CCSprite* sliders [] = { soundVolumeSlider, musicVolumeSlider };
	currentSlider = NULL;
	for (int i = 0; i < 2; i++){
		CCSprite* tmpSlider = sliders[i];
		
		if (abs(y - tmpSlider->getPositionY())< 50 && (abs(x - tmpSlider->getPositionX())) < 150) {
			currentSlider = tmpSlider;
		}
	}
	
	return true;
}
void OptionsLayer::ccTouchEnded(CCTouch *touch, CCEvent * pEvent){


}
void OptionsLayer::ccTouchCancelled(CCTouch *touch, CCEvent * pEvent){}

void OptionsLayer::ccTouchMoved(CCTouch *touch, CCEvent * pEvent){
	if (!currentSlider)return;
	int x = (touch->getLocation().x - (currentSlider->getPositionX() -125 ));
	CCSprite* pointer =NULL;
	CCSprite* sliders[] = { soundVolumeSlider, musicVolumeSlider };
	CCSprite* pointers[] = { soundPointer, musicPointer};
	for (int i = 0; i < 2; i++){
		CCSprite* tmpSlider = sliders[i];

		if (currentSlider==tmpSlider) {
			pointer = pointers[i];
		}
	}
	if (x>250)x = 250;
	if (x<0)x = 0;
	pointer->setPositionX(x);
	float value = x / 250.0;
	if (pointer == soundPointer){
		CCUserDefault::sharedUserDefault()->setFloatForKey(SETTINGSOUNDSVOLUME, value);\
	    CocosDenshion::SimpleAudioEngine::sharedEngine()->setEffectsVolume(value);
	}
	else{
		CCUserDefault::sharedUserDefault()->setFloatForKey(SETTINGSMUSICVOLUME, value);
		CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(value);
	}


}

void OptionsLayer::openInstruction(CCObject * pSender){
	//CCApplication::sharedApplication()->openURL("http://bmideas.yum.pl/?page_id=396");

}
void OptionsLayer::openMoreApps(CCObject * pSender) {
	if (CCApplication::sharedApplication()->getTargetPlatform() == kTargetAndroid){
	//	CCApplication::sharedApplication()->openURL("https://play.google.com/store/apps/developer?id=bunny1985");
	}

	if (CCApplication::sharedApplication()->getTargetPlatform() == kTargetBlackBerry){
		//CCApplication::sharedApplication()->openURL("http://appworld.blackberry.com/webstore/vendor/57991/?lang=en&countrycode=PL");
	}
	
}