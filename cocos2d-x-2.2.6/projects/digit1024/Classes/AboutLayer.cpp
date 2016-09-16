/*
 * AboutLayer.cpp
 *
 *  Created on: 26 wrz 2013
 *      Author: michal
 */

#include "AboutLayer.h"
#include "Common/Enums.h"
#include "Common/Resources.h"
AboutLayer::AboutLayer() {
	// TODO Auto-generated constructor stub

}

cocos2d::CCScene* AboutLayer::scene() {


	CCScene *scene = CCScene::create();
	AboutLayer*layer = AboutLayer::create();
	scene->addChild(layer);
	return scene;
}

bool AboutLayer::init() {


	CCSize visibleSize = CCDirector::sharedDirector()->getWinSize();
	CCSprite* background = CCSprite::create("backgroundSettings.png");
	addChild(background);

	background->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2));

	char*  text = "Digit Adventures by: Michal Banas\n "
		"BMIdeas 2013-2014\n"
		"Used Materials:\n"
		"Graphics:"
		"Backgropund in Menu Scene and planet in intro: Aetherna - Space Cartoon Background: http://opengameart.org/content/space-cartoon-background \n"
		"Icons in Menu: Icon Set;http://opengameart.org/content/icon-set \n"
		"Star, Key , some trees teleport: Danc's Miraculously Flexible Game Prototyping Tiles\" art by Daniel Cook (Lostgarden.com) http://lunar.lostgarden.com \n"
		"Music:\n"
		"All Music cames from by Kevin MacLeod\n"
		"http://incompetech.com\n"
		"Tracks: \n"
		"Chipper Doodle v2\n"
		"Deliberate Thought\n"
		"Kick Shock\n"
		"Move Forward\n"
		"New Friendly\n"
		"Pinball Spring 160\n"
		"Happy Bee\n"
		"Pixel Peeker Polka - faster\n"
		"Show Your Moves\n"
		"Sounds from Jes�s Lastra Retro Game Souns FX\n"
		"This Matrials was released unde CC v3 License\n"
		"Link to full license\n"
		"http://creativecommons.org/licenses/by-nc-nd/3.0/"
		"\n \n \n "
		"Thank You for buying"

		;


	CCLabelBMFont* textLabel = CCLabelBMFont::create(text, GAME_MENU_FONT_FILE, 1000, kCCTextAlignmentLeft);
	textLabel->setPosition(ccp(640, visibleSize.height / 2  - textLabel->getContentSize().height+300));
	addChild(textLabel);
	textLabel->runAction(CCMoveTo::create(30, (ccp(640, visibleSize.height ))));

	/*

	CCLabelTTF *labelttf = CCLabelTTF::create("Aetherna - Space Cartoon Background;http://opengameart.org/content/space-cartoon-background", "arial", 18);
	labelttf->setPosition(ccp(650 + (label->getContentSize().width / 2), 400));
	addChild(labelttf);

	labelttf = CCLabelTTF::create("nikotolonen - Icon Set;http://opengameart.org/content/icon-set", "arial", 18);
	labelttf->setPosition(ccp(650 + (label->getContentSize().width / 2), 380));
	addChild(labelttf);


	labelttf = CCLabelTTF::create("\"Danc's Miraculously Flexible Game Prototyping Tiles\" art by Daniel Cook (Lostgarden.com) http://lunar.lostgarden.com ", "arial", 18);
	labelttf->setPosition(ccp(650 + (label->getContentSize().width / 2), 360));
	addChild(labelttf);

	*/



    CCMenuItemLabel *back = CCMenuItemLabel::create(
    			CCLabelBMFont::create("<<back", GAME_MENU_FONTHD_FILE), this,
    			menu_selector(AboutLayer::backCallcBack));
    CCMenu *menu  = CCMenu::create(back , NULL);

    menu->setPosition(100 , 100);

    addChild(menu);



	return true;
}

void AboutLayer::backCallcBack(CCObject * pSender) {
CCDirector::sharedDirector()->popScene();
}

AboutLayer::~AboutLayer() {
	// TODO Auto-generated destructor stub
}

