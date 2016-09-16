/*
 * MenuScene.cpp
 *
 *  Created on: 28-07-2013
 *      Author: michal
 */

#include "MenuScene.h"
#include "Common/Resources.h"
#include "SimpleAudioEngine.h"
#include "GameLevelScene.h"
#include "OptionsLayer.h"
#include "SelecLevelLayer.h"
#include "AboutLayer.h"
#include "CCShake.h"
#include "Common/RESPATH.h"
#include "Common/PaymentService.h"
#include "CCShake.h"

CCScene* MenuScene::scene()
{

	CCScene *scene = CCScene::create();
	MenuScene *layer = MenuScene::create();
	scene->addChild(layer);


	return scene;
}
void MenuScene::showPresnests(){



	CCLabelBMFont* label = CCLabelBMFont::create("presents", GAME_MENU_FONTHD_FILE);
	addChild(label);
	label->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2));
	CCCallFunc* callback = CCCallFunc::create(this, callfunc_selector(MenuScene::showTitle));
	label->runAction(CCSequence::create(CCFadeIn::create(0.5),  CCShake::actionWithDuration(2, 0, 0), CCFadeOut::create(1.0), callback, NULL));
	CCSprite* background = CCSprite::create("space.png");
	addChild(background);
	background->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2));
	background->runAction(CCFadeIn::create(2.5));

}
void MenuScene::showTitle(){
	CCLabelBMFont* label = CCLabelBMFont::create("DIGIT ADVENTURES", GAME_MENU_FONTHD_FILE);
	label->setScale(2.0f);
	addChild(label);
	label->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2));
	CCCallFunc* callback = CCCallFunc::create(this, callfunc_selector(MenuScene::showMenu));
	CCPoint p = ccp(visibleSize.width / 2, visibleSize.height + label->getContentSize().height );
	label->runAction(CCSequence::create(CCFadeIn::create(0.5), CCShake::actionWithDuration(2, 0, 0), callback  , CCMoveTo::create(1.5, p),  NULL));



	setVolume();
	//CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("SuperFriendly.wav", true);

	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(respatchFix("Sounds/music/Super Friendly" SOUND_EXT).c_str() , true);
}
void MenuScene::showRobbo(){
	CCSprite* robbo = CCSprite::createWithSpriteFrameName("robbo.png");
	robbo->setScale(0);
	robbo->setPosition(ccp(300, 550));
	CCPoint dest = ccp(370, 380);
	addChild(robbo);
	CCSpawn* robboAnim = CCSpawn::create(CCScaleTo::create(0.5, 1), CCEaseBackIn::create(CCMoveTo::create(0.5, dest) ), NULL);
	robbo->runAction(robboAnim);

}

 void MenuScene::keyBackClicked(){
    exit(0);
}
void MenuScene::keyMenuClicked(){

    this->menutogglesideMenu(this);
}


void MenuScene::showMenu(){
	CCSprite* planet = CCSprite::create("planet.png");
	addChild(planet);
	planet->setPosition(ccp(visibleSize.width / 2, (-visibleSize.height/2) - planet->getContentSize().height / 2));
	planet->runAction(CCMoveTo::create(1.5 , ccp(visibleSize.width / 2, planet->getContentSize().height /2)));
	CCSprite* ship = CCSprite::createWithSpriteFrameName("robboShip.png");
	ship->setPosition(ccp(-visibleSize.width / 2, visibleSize.height / 2 + 100));
	ship->setScale(0.1);
	CCSpawn* flightAnim1 = CCSpawn::create(CCScaleTo::create(1.5, 0.1), CCMoveTo::create(3, ccp(2000, 1000)) , NULL);
	CCSpawn* flightAnim2 = CCSpawn::create(CCScaleTo::create(1.5, 0.2), CCMoveTo::create(3, ccp(300, 650) ) ,  NULL);

	CCSpawn* flightAnim3 = CCSpawn::create(CCScaleTo::create(2, 0.0),  CCMoveTo::create(2, ccp(600, 600)), NULL);
	CCCallFunc* callback = CCCallFunc::create(this, callfunc_selector(MenuScene::showRobbo));
	ship->runAction(CCSequence::create(flightAnim1, flightAnim2, callback , CCShake::actionWithDuration(2, 0, 0), flightAnim3, NULL));
	addChild(ship);




	CCSprite* SideMenu = CCSprite::create("SideMenu.png");
	addChild(SideMenu);
	SideMenu->setZOrder(100);
	SideMenu->setPosition(ccp(-SideMenu->getContentSize().width / 2, visibleSize.height / 2));

	CCMenuItemLabel *sideMenuSetting = CCMenuItemLabel::create(
		CCLabelBMFont::create("VOLUME", GAME_MENU_FONTHD_FILE), this,
		menu_selector(MenuScene::menuSettingsCallback));
	sideMenuSetting->setAnchorPoint(ccp(0, 0));
	CCMenuItemLabel *sideMenuAbout = CCMenuItemLabel::create(
		CCLabelBMFont::create("ABOUT", GAME_MENU_FONTHD_FILE), this,
		menu_selector(MenuScene::menuAboutCallback));
	sideMenuAbout->setAnchorPoint(ccp(0, 0));
	sideMenuAbout->setPositionY(-100);

	CCMenuItemLabel *sideMenuMoreGames = CCMenuItemLabel::create(
		CCLabelBMFont::create("MORE APPS", GAME_MENU_FONTHD_FILE), this,
		menu_selector(MenuScene::menuMoreApps));



	sideMenuMoreGames->setAnchorPoint(ccp(0, 0));
	sideMenuMoreGames->setPositionY(-200);

    CCMenuItemLabel *sideMenuRateIt = CCMenuItemLabel::create(
        CCLabelBMFont::create("RATE IT!", GAME_MENU_FONTHD_FILE), this,
        menu_selector(MenuScene::menuRate));
    sideMenuRateIt->setAnchorPoint(ccp(0, 0));
    sideMenuRateIt->setPositionY(-400);





	CCMenuItemLabel *sideMenuInstructions = CCMenuItemLabel::create(
		CCLabelBMFont::create("INSTRUCTIONS", GAME_MENU_FONTHD_FILE), this,
		menu_selector(MenuScene::menuInstruction));
	sideMenuInstructions->setAnchorPoint(ccp(0, 0));
	sideMenuInstructions->setPositionY(-300);



#ifdef ENABLESOUNDSETTINGS

	CCMenu* SideMenuItems = CCMenu::create(sideMenuSetting , sideMenuAbout,sideMenuMoreGames ,sideMenuInstructions, sideMenuRateIt , NULL);
#else
	CCMenu* SideMenuItems = CCMenu::create( sideMenuAbout, sideMenuMoreGames, sideMenuInstructions, NULL);
#endif
	//CCMenu* SideMenuItems = CCMenu::create(sideMenuSetting, sideMenuAbout, sideMenuMoreGames, sideMenuInstructions, NULL);
	SideMenuItems->setPositionY(650);
	SideMenuItems->setPositionX(20);
	//SideMenuItems->setPosition(ccp(0,SideMenu->getContentSize().height));
	SideMenu->addChild(SideMenuItems);
	sidemenupointer = SideMenu;

	CCMenuItemLabel *start = CCMenuItemLabel::create(
		CCLabelBMFont::create("START", GAME_MENU_FONTHD_FILE), this,
		menu_selector(MenuScene::menuStartCallback));
	CCMenuItemLabel *levels = CCMenuItemLabel::create(
		CCLabelBMFont::create("SELECT LEVEL", GAME_MENU_FONTHD_FILE), this,
		menu_selector(MenuScene::menuSelectLevel));

	CCMenuItemImage *mute = CCMenuItemImage::create("unmute.png", "unmute.png", "mute.png", this,
	        menu_selector(MenuScene::menuMute));
	float Soundsvolume = CCUserDefault::sharedUserDefault()->getFloatForKey(SETTINGSOUNDSVOLUME , 1.0f);
	    float Musicvolume = CCUserDefault::sharedUserDefault()->getFloatForKey(SETTINGSMUSICVOLUME , 1.0f);
	if(Soundsvolume <0.001f && Musicvolume< 0.001f){
	            mute->setNormalImage(CCSprite::create("mute.png"));
	};

	this->mute = mute;
	CCMenuItemImage *settings = CCMenuItemImage::create("settings.png", "settings.png", "settings.png", this,
		menu_selector(MenuScene::menutogglesideMenu));

	CCMenuItemImage *about = CCMenuItemImage::create("info.png", "info.png", this,
		menu_selector(MenuScene::menutogglesideMenu));
	CCMenuItemImage *quit = CCMenuItemImage::create("exit.png", "exit.png", this,
		menu_selector(MenuScene::menuQuitCallback));
	CCMenuItemImage *facebook = CCMenuItemImage::create("facebook.png", "facebook.png", this,
		menu_selector(MenuScene::menuFacebook));

	CCMenu* menu = CCMenu::create(start, levels, NULL);
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	menu->setPosition(ccp((s.width / 1.5), s.height / 1.5));
	menu->alignItemsVertically();
	planet->addChild(menu);
	menu->setOpacity(0);
	menu->runAction(CCSequence::create(CCShake::actionWithDuration(2, 0), CCFadeIn::create(1) , NULL ));
#ifdef WP8
	CCMenu* additionalMenu = CCMenu::create( settings,  facebook , NULL);
#else
	CCMenu* additionalMenu = CCMenu::create( mute, settings, facebook, NULL);
#endif
	//CCMenu* additionalMenu = CCMenu::create(quit, about ,NULL);
	additionalMenu->setPosition(ccp(0, 0));
	facebook->setPosition(ccp((s.width - settings->getContentSize().width) - 400, settings->getContentSize().height));
	settings->setPosition(ccp((s.width - settings->getContentSize().width) - 200, settings->getContentSize().height));
	quit->setPosition(ccp((s.width - settings->getContentSize().width), settings->getContentSize().height));
	mute->setPosition(ccp((s.width - settings->getContentSize().width), settings->getContentSize().height));
#ifdef WP8
	facebook->setPosition(ccp((s.width - settings->getContentSize().width) - 200, settings->getContentSize().height));
	settings->setPosition(ccp((s.width - settings->getContentSize().width) , settings->getContentSize().height));
#endif
	addChild(additionalMenu);
	this->setKeypadEnabled(true);
	initParticle();

}

void MenuScene::menuRate(CCObject* pSender){
//http://appworld.blackberry.com/webstore/content/59945546/?lang=en&countrycode=PL

    if (CCApplication::sharedApplication()->getTargetPlatform() == kTargetAndroid){
          //      CCApplication::sharedApplication()->openURL("https://play.google.com/store/apps/details?id=pl.yum.bunny1985.digitAdventures");
            }else if (CCApplication::sharedApplication()->getTargetPlatform() == kTargetBlackBerry){
            //    CCApplication::sharedApplication()->openURL("http://appworld.blackberry.com/webstore/content/59945546/");
        }
            else{
              //  CCApplication::sharedApplication()->openURL("http://bmideas.yum.pl/");
            }
}
void MenuScene::menuMute(CCObject* pSender){
    float Soundsvolume = CCUserDefault::sharedUserDefault()->getFloatForKey(SETTINGSOUNDSVOLUME , 1.0f);
    float Musicvolume = CCUserDefault::sharedUserDefault()->getFloatForKey(SETTINGSMUSICVOLUME , 1.0f);
        if(Soundsvolume <0.001f && Musicvolume< 0.001f){
            //pogłasniamy

            mute->setNormalImage(CCSprite::create("unmute.png"));

            //wczytajmy jak było
            Soundsvolume = CCUserDefault::sharedUserDefault()->getFloatForKey("STOREDVOLUMESOUND" , 1.0f);
            Musicvolume = CCUserDefault::sharedUserDefault()->getFloatForKey("STOREDVOLUMEMUSIC" , 1.0f);

            CCUserDefault::sharedUserDefault()->setFloatForKey( SETTINGSOUNDSVOLUME , Soundsvolume);
            CCUserDefault::sharedUserDefault()->setFloatForKey( SETTINGSMUSICVOLUME , Musicvolume);



        }else{
            //Wyciszamy
            mute->setNormalImage(CCSprite::create("mute.png"));
            //zapamietajmy jak było
            CCUserDefault::sharedUserDefault()->setFloatForKey( "STOREDVOLUMESOUND" , Soundsvolume);
            CCUserDefault::sharedUserDefault()->setFloatForKey( "STOREDVOLUMEMUSIC" , Musicvolume);

            CCUserDefault::sharedUserDefault()->setFloatForKey(SETTINGSOUNDSVOLUME , 0.0f);
            CCUserDefault::sharedUserDefault()->setFloatForKey(SETTINGSMUSICVOLUME , 0.0f);

        }
        setVolume();

}




void MenuScene::menuFacebook(CCObject* pSender){
	if (CCApplication::sharedApplication()->getTargetPlatform() == kTargetAndroid){
		//CCApplication::sharedApplication()->openURL("https://www.facebook.com/BMIdeasApps");
	}
	else if (CCApplication::sharedApplication()->getTargetPlatform() == kTargetBlackBerry){
#ifdef FBSHARE
	    //CCApplication::sharedApplication()->ShareOnFacebook("Check out #digitAdventures game! I'm playing it right now! http://appworld.blackberry.com/webstore/content/59945546/ In my opinion it's ...");
#endif

	}
	else{
		//CCApplication::sharedApplication()->openURL("https://www.facebook.com/BMIdeasApps");
	}
}

bool MenuScene::init()
{
    MenuScene::intro = true;

	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(
		respatchFix("Sounds/music/Super Friendly" SOUND_EXT).c_str());
	GameLevelScene::batchNode = CCSpriteBatchNode::create("robbo.png");





	visibleSize = CCDirector::sharedDirector()->getWinSize();
	setVolume();
	if (MenuScene::intro){
		CCSprite* background = CCSprite::create("space.png");
		addChild(background);
		background->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2));

		CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(
			respatchFix("Sounds/music/Super Friendly" SOUND_EXT).c_str(), true);
		showMenu();
	}else{
		MenuScene::intro = true;



		CCSprite* logo = CCSprite::createWithSpriteFrameName("BMIdeas.png");
		addChild(logo);
		logo->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2));
		CCCallFunc* callback = CCCallFunc::create(this, callfunc_selector(MenuScene::showPresnests));
		logo->runAction(CCSequence::create(CCFadeIn::create(1), CCShake::actionWithDuration(1, 0, 0), CCFadeOut::create(2), callback, NULL));
	}
	return true;
}



void MenuScene::menuStartCallback(CCObject* pSender)
{
	if(int l  = CCUserDefault::sharedUserDefault()->getIntegerForKey(SETTINGSLASTLEVEL, 0) ){
		GameLevelScene::level = l;
	}

	CCDirector::sharedDirector()->replaceScene(
			CCTransitionFlipAngular::create(1, GameLevelScene::scene()));
}

void MenuScene::menutogglesideMenu(CCObject* pSender){
    int x = sidemenupointer->getPositionX();
    if(x < 0){
         sidemenupointer->runAction(CCMoveTo::create(0.3 , ccp(sidemenupointer->getContentSize().width/2,sidemenupointer->getPositionY() ) ));
    }else{
        sidemenupointer->runAction(CCMoveTo::create(0.3 , ccp(-sidemenupointer->getContentSize().width/2,sidemenupointer->getPositionY()) ));
    }

}
void MenuScene::menuQuitCallback(CCObject* pSender)
{

#ifdef WP8
	CCApplication::sharedApplication()->applicationDidEnterBackground();
#else
	exit(0);
#endif

}

void MenuScene::menuSettingsCallback(CCObject* pSender)
{
	CCDirector::sharedDirector()->pushScene(CCTransitionFadeBL::create(0.3f , OptionsLayer::scene()));
}

void MenuScene::menuAboutCallback(CCObject* pSender)
{
    CCLOG("About");

	CCDirector::sharedDirector()->pushScene(CCTransitionMoveInR::create(0.3f , AboutLayer::scene()));

}

void MenuScene::menuSelectLevel(CCObject* pSender) {
	CCDirector::sharedDirector()->pushScene(CCTransitionFadeBL::create(0.3f, SelecLevelLayer::scene()));
}

void MenuScene::initParticle()
{

	CCParticleSnow* m_emitter = CCParticleSnow::create();
	m_emitter->retain();
	addChild(m_emitter, 10);

	//CCPoint p = m_emitter->getPosition();
	//m_emitter->setPosition( ccp( p.x, p.y-110) );
	m_emitter->setLife(5);
	m_emitter->setLifeVar(1);

	// gravity
	m_emitter->setGravity(ccp(0,-10));

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

void MenuScene::setVolume() {

	float volume = CCUserDefault::sharedUserDefault()->getFloatForKey(SETTINGSOUNDSVOLUME , 1.0f);
	CCUserDefault::sharedUserDefault()->setFloatForKey(SETTINGSOUNDSVOLUME , volume);
	CCLOG("music volume set to %f"  ,volume);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->setEffectsVolume(volume);
	volume = CCUserDefault::sharedUserDefault()->getFloatForKey(SETTINGSMUSICVOLUME , 0.5f);
	CCUserDefault::sharedUserDefault()->setFloatForKey(SETTINGSMUSICVOLUME , volume);
	CCLOG("Sounds volume set to %f"  ,volume);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(volume);
}

void MenuScene::menuMoreApps(CCObject* pSender){


    if (CCApplication::sharedApplication()->getTargetPlatform() == kTargetAndroid){
          //  CCApplication::sharedApplication()->openURL("https://play.google.com/store/apps/developer?id=bunny1985");
        }else if (CCApplication::sharedApplication()->getTargetPlatform() == kTargetBlackBerry){
           // CCApplication::sharedApplication()->openURL("http://appworld.blackberry.com/webstore/vendor/57991/?lang=en&countrycode=PL");
  	}
		else{
			//CCApplication::sharedApplication()->openURL("http://bmideas.yum.pl/");
		}
}

void MenuScene::menuInstruction(CCObject* pSender){
    //CCApplication::sharedApplication()->openURL("http://bmideas.yum.pl/?page_id=396");
}
bool MenuScene::intro = false;
