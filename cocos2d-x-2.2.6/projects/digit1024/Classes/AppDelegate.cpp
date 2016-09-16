#include "AppDelegate.h"
#include "MenuScene.h"
#include "GameOverScene.h"
#include "SimpleAudioEngine.h"

#include "SimpleAudioEngine.h"
#include "Common/RESPATH.h"



#ifndef  _APP_DELEGATE_CPP_
#define  _APP_DELEGATE_CPP_
USING_NS_CC;
#ifndef WINDOWS
 #define SOUND_EXT ".ogg"
#endif
AppDelegate::AppDelegate()
{

}



bool AppDelegate::applicationDidFinishLaunching()
{
	// initialize director
	CCDirector* pDirector = CCDirector::sharedDirector();
	CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

	pDirector->setOpenGLView(pEGLView);

	// turn on display FPS
	pDirector->setDisplayStats(false);

	// set FPS. the default value is 1.0/60 if you don't call this
	pDirector->setAnimationInterval(1.0 / 60);
	//set design size for iPad retina
	CCSize designSize = CCSize(1280, 768);
	CCSize screenSize = pEGLView->getFrameSize();
	CCEGLView::sharedOpenGLView()->setDesignResolutionSize(designSize.width,
			designSize.height, kResolutionExactFit);
	//pDirector->setContentScaleFactor(screenSize.height / designSize.height);
	loadResources();
	// create a scene. it's an autorelease object
#ifdef TESTCASES
	CCScene *pScene = GameLevelScene::scene();
#else
	CCScene *pScene = MenuScene::scene();
#endif

	// run
	pDirector->runWithScene(pScene);

	return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
	CCDirector::sharedDirector()->stopAnimation();

	// if you use SimpleAudioEngine, it must be pause
	CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
	CCDirector::sharedDirector()->startAnimation();

	// if you use SimpleAudioEngine, it must resume here
	CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}

void AppDelegate::loadResources()
{
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(
			"robbo.plist");

	//preload All SOUNDS
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(respatchFix("Sounds/321go" SOUND_EXT).c_str());
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(respatchFix("Sounds/ammo" SOUND_EXT).c_str());
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(respatchFix("Sounds/bomb" SOUND_EXT).c_str());
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(respatchFix("Sounds/crack" SOUND_EXT).c_str());
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(respatchFix("Sounds/door" SOUND_EXT).c_str());
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(respatchFix("Sounds/end" SOUND_EXT).c_str());


	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(respatchFix("Sounds/ice" SOUND_EXT).c_str());
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(respatchFix("Sounds/key" SOUND_EXT).c_str());

	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(respatchFix("Sounds/lelvelUp" SOUND_EXT).c_str());



	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(respatchFix("Sounds/screw" SOUND_EXT).c_str());
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(respatchFix("Sounds/shoot" SOUND_EXT).c_str());

	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(respatchFix("Sounds/szur" SOUND_EXT).c_str());
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(respatchFix("Sounds/teleport" SOUND_EXT).c_str());
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(respatchFix("Sounds/walk" SOUND_EXT).c_str());



}
#endif
