#include "GameLevelScene.h"
#include "Common/Resources.h"

#include "GameMenuLayer.h"
#include "SimpleAudioEngine.h"
#include "ObjectsFactory.h"

#include "Sprites/Objects/Box.h"
#include "Sprites/Objects/Bomb.h"
#include "Common\TileMapResources.h"
#include "CCShake.h"
#include "DialogLayer.h"
#include "NextLevelLayer.h"
#include "Common\RESPATH.h"
#include "Common/PaymentService.h"

USING_NS_CC;

CCScene* GameLevelScene::scene()
{



	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
	CCLOG("loading Scene added");
	CCScene *scene = CCScene::create();
	GameLevelScene *layer = GameLevelScene::create();
	layer->hud = GameMenuLayer::create();
	CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("ground.png");
	layer->bgLayer = CCLayer::create();
	ccTexParams tp = { GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT };
	texture->setTexParameters(&tp);
	CCSprite* sprite = CCSprite::createWithTexture(texture, CCRectMake(0, 0, 1680, 768));
	sprite->setPosition(ccp(1280 / 2, 768 / 2));
	layer->bgLayer->addChild(sprite);
	scene->addChild(layer->bgLayer);
	layer->bgLayer->setZOrder(-1);
	scene->addChild(layer);
	scene->addChild(layer->instance->hud, 120);
	layer->hud->setScale(0.0);

	/*layer->hud->runAction(CCSequence::create(CCScaleTo::create(0.3, 1.0), CCCallFunc::create(layer,
		callfunc_selector(GameLevelScene::ShowStarting)), NULL));
		*/
	PaymentService p;

	//if(p.hasBadge()){
	    layer->hud->runAction(CCSequence::create(CCScaleTo::create(0.3, 1.0), CCCallFunc::create(layer,
	                        callfunc_selector(GameLevelScene::ShowStarting)), NULL));
	//}else{
	 //   layer->hud->runAction(CCSequence::create(CCScaleTo::create(0.3, 1.0), CCCallFunc::create(layer,
	//                callfunc_selector(GameLevelScene::showWaiting)), NULL));
	//}


	//, CCCallFunc::create(layer,	callfunc_selector(GameLevelScene::ShowStarting))
	return scene;

}
void GameLevelScene::updateColletcable(){
	updateColletcable(robboSprite->lives, robboSprite->screws, robboSprite->shoots, robboSprite->keys);
}

bool GameLevelScene::init()
{
    waitingMenuSprite  = NULL;
	current_state = current_state = LevelScenePaused;
	counter = 3;
	allstarscollected = false;
	//storing last level
	int l = CCUserDefault::sharedUserDefault()->getIntegerForKey(SETTINGSMAXLEVEL , 0 );
	if(GameLevelScene::level>l){
		CCUserDefault::sharedUserDefault()->setIntegerForKey(SETTINGSMAXLEVEL, GameLevelScene::level);
	}
	CCUserDefault::sharedUserDefault()->setIntegerForKey(SETTINGSLASTLEVEL  , GameLevelScene::level);


	this->setTouchEnabled(false);
	this->instance = this;
	current_state = (int) LevelSceneLoading;
	TotalScrews = 0;
	setVisible(true);
	//////////////////////////////
	// 1. super init first
	if (!CCLayer::init())
	{
		return false;
	}


	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	// create menu, it's an autorelease object
	if (!batchNode)
	{
		batchNode = CCSpriteBatchNode::create("robbo.png");
	}


	/////////////////////////////
	// 3. add your codes below...
	map =
			CCTMXTiledMap::create(
					CCString::createWithFormat("TileGameResources/map%i.tmx",
							level)->getCString());


	this->addChild(map);


	initObjects();
	CCLog("all Objects Created");
	this->scheduleUpdate();


	updateOrder.push_back(GAME_TYPE_WALL);
	updateOrder.push_back(GAME_TYPE_ROBBO);
	updateOrder.push_back(GAME_TYPE_Magnet);
	//updateOrder.push_back(GAME_TYPE_BOX);
	updateOrder.push_back(GAME_TYPE_BULLET);


	//updateOrder.push_back(GAME_TYPE_GROUND);
	updateOrder.push_back(GAME_TYPE_TELEPORT);
	updateOrder.push_back(GAME_TYPE_QUESTIONMARK);
	updateOrder.push_back(GAME_TYPE_BOMB);
	updateOrder.push_back(GAME_TYPE_Door);

	updateOrder.push_back(GAME_TYPE_FORCE_FIELD);
	updateOrder.push_back(GAME_TYPE_ENTERABLEGROUND);
	updateOrder.push_back(GAME_TYPE_ROCK);
	updateOrder.push_back(GAME_TYPE_SWITCH);
	updateOrder.push_back(GAME_TYPE_ENEMY);




	return true;

}

void GameLevelScene::centerView(CCPoint position)
{
	float x = 0;
	float y = 0;

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCPoint centerOfView = ccp(winSize.width/2, winSize.height/2);
	x = robboSprite->getPositionX();
	y = robboSprite->getPositionY();
	//ustawianie Y
	//if (robboSprite->getPositionY()
	//		> map->getContentSize().height - winSize.height / 2)
	//{
	//	y = map->getContentSize().height - winSize.height / 2;
	//}
	//else if (robboSprite->getPositionY() < winSize.height / 2)
	//{
	//	y = winSize.height / 2;
	//}
	//Ustawianie x
	//if (robboSprite->getPositionX() < winSize.width / 2)
	//{
	//	x = winSize.width / 2;
	//}
	//else if (robboSprite->getPositionX()
	//		> map->getContentSize().width - winSize.width / 2)
	//{
	//	x = map->getContentSize().width - winSize.width / 2;
	//}

	CCPoint viewPoint = ccpSub(centerOfView, ccp(x,y));
	this->viewPoint = ccp(x,y);
	viewPoint = ccp(viewPoint.x *this->getScale(), viewPoint.y*this->getScale());
	//CCPoint viewPoint = ccpSub(centerOfView, robboSprite->getPosition());
	this->setPosition(viewPoint);
	//this->bgLayer->setPosition(viewPoint*2);

}

void GameLevelScene::pauseGame() {
	current_state = LevelScenePaused;
	this->pauseSchedulerAndActions();
	CCObject* tmpobj;
	CCARRAY_FOREACH(&objects , tmpobj) {
		if (((GameSprite*) tmpobj)->getType() != GAME_TYPE_ROBBO) {
			((GameSprite*) tmpobj)->pauseSchedulerAndActions();

		}
	}
}
void GameLevelScene::update(float dt){
	updateObjectsMap();
	updateGame();

}

void GameLevelScene::updateGame()
{

	CCObject* tmpobj;
	if(robboSprite->getState()==-1){
		pauseGame();
		return;
	}
	centerView(robboSprite->getPosition());



	CCARRAY_FOREACH_REVERSE(&objects , tmpobj)
	{
		if (((GameSprite*) tmpobj)->isDestroyed())
		{
			//showKill(((GameSprite*) tmpobj)->getTileMapPosition());

			removeObject((GameSprite*) tmpobj);

		}

	}
	updateObjectsMap();
	for (unsigned int i = 0;i  < updateOrder.size(); i++) {

		int type = updateOrder[i];
		CCARRAY_FOREACH_REVERSE(&objects, tmpobj)
		{

			if (((GameSprite*) tmpobj)->getType() != type) continue;
			((GameSprite*) tmpobj)->update();
			GameSprite* sprite = ((GameSprite*) tmpobj);

			GameSprite* hitedObject = GAMEUTILS->objectAt(sprite->getTileMapPosition(), sprite);
			if (hitedObject && hitedObject->getType() == GAME_TYPE_ENEMY){

				sprite->hit(sprite->getMoveDirection(), hitedObject);
			}

		}
	}
	addPenidingObjects();

}
void GameLevelScene::addPenidingObjects(){
	CCObject* obj;
	CCARRAY_FOREACH(&objectsWaitingForAddition, obj){
		addChild((GameSprite*)obj);
	}
	GameUtils::addPenidingObjects();
}


void GameLevelScene::initObjects()
{

    const CCString* scalestring = (map->getProperties()->valueForKey("Scale"));
    CCLog(scalestring->getCString());
    if(scalestring && scalestring->floatValue()!=0.0){
        setScale(scalestring->floatValue());
    }

	TileMapResources tiledmapdata;


	CCTMXLayer* layer = map->layerNamed("ObjectTiles");
	CCArray* propertiesObjects = map->objectGroupNamed("objects")->getObjects();
	CCSize layerSize = map->getMapSize();
		layer->setVisible(false);


	for (int x = 0; x < layerSize.width; x++){
		for (int y = 0; y < layerSize.height; y++){

			int objectGid = layer->tileGIDAt(ccp(x, y))- 73 ;
			if (tiledmapdata.factoriesDictionary.count(objectGid)){
				GameSprite* object = tiledmapdata.factoriesDictionary[objectGid]->Create(NULL);
				if (object->getType() == GAME_TYPE_ROBBO){
					robboSprite = (Robbo*) object;

				}
				addObject(object);
				object->setPosition(GAMEUTILS->getScenePoint(ccp(x, y)));
				if (object->getType() == GAME_TYPE_Collectable && ((Collectable*) object)->getCollectableType() == GAME_TYPE_CollectableTYPE_SCREW){
					TotalScrews++;
				}
				CCObject* tmpObj = NULL;
				CCARRAY_FOREACH(propertiesObjects, tmpObj){
					CCDictionary* tmpDictionary = (CCDictionary*) tmpObj;
					CCPoint tiledPoint = GAMEUTILS->getTiledPoint(ccp(tmpDictionary->valueForKey("x")->intValue() +40 , tmpDictionary->valueForKey("y")->intValue()+40 ));
					if (tiledPoint.x  == object->getTileMapPosition().x  && tiledPoint.y  == object->getTileMapPosition().y ){
						object->applyProperties(tmpDictionary);

					}
				}


			}

		}
	}
	addPenidingObjects();
	CCObject * obj = NULL;
	CCARRAY_FOREACH(&objectsWaitingForAddition, obj){
		((GameSprite*) obj)->startMoving();
	}





}

GameLevelScene* GameLevelScene::instance = NULL;

void GameLevelScene::removeObject(GameSprite* obj)
{
	objects.removeObject(obj);
	removeChild(obj);

}

void GameLevelScene::showDialog(const char* message, const char* image){
	DialogLayer* dialog = DialogLayer::create();
	dialog->setText(message);
	dialog->setImage(image);
	hud->addChild(dialog);
}


void GameLevelScene::showExplosion(CCPoint tilePoint)
{



	CCSprite* explosion = CCSprite::createWithSpriteFrameName("explosion.png");
	addChild(explosion);
	explosion->setPosition(GAMEUTILS->getScenePoint(tilePoint));
	explosion->setTag(123);

	CCCallFunc* callbackHud = CCCallFunc::create(this->hud, callfunc_selector(GameMenuLayer::resetPosition));
	this->hud->runAction(CCSequence::createWithTwoActions( CCShake::actionWithDuration(0.5, 5)  , callbackHud));

	CCCallFunc* callback = CCCallFunc::create(explosion, callfunc_selector(GameLevelScene::removeExplosion));

	explosion->setOpacity(0.5);
	explosion->setScale(0.0);
	CCSpawn* efect =CCSpawn::create(CCFadeOut::create(0.4), CCShake::actionWithDuration(0.5, 4)  , CCScaleTo::create(0.3 , 1) , NULL);


	explosion->runAction(CCSequence::createWithTwoActions(efect, callback));





}
void GameLevelScene::removeExplosion(){
	removeChildByTag(123);
}

void GameLevelScene::showKill(CCPoint tilePoint)
{

	//to jest zbyt kosztowne
	CCParticleSmoke *m_emitter = CCParticleSmoke::create();
	//m_emitter->retain();
	m_emitter->setPosition(GAMEUTILS->getScenePoint(tilePoint));
	m_emitter->setPositionType(kCCPositionTypeGrouped);
	m_emitter->setTotalParticles(1);
	m_emitter->setLife(0.5);
	m_emitter->setTexture(
			CCTextureCache::sharedTextureCache()->addImage("fire.png"));
	m_emitter->setDuration(0.1);
	m_emitter->setAutoRemoveOnFinish(true);
	this->addChild(m_emitter);

}

void GameLevelScene::updateColletcable(int lives, int screws, int ammo, int keys)
{
	if (hud != NULL)
	{
		this->hud->ammoLabel->setCString(
				CCString::createWithFormat("%i", ammo)->getCString());
		this->hud->keysLabel->setCString(
				CCString::createWithFormat("%i", keys)->getCString());


		//this->hud->livesLabel->setCString(
			//	CCString::createWithFormat("%i", lives)->getCString());
		this->hud->screwsLabel->setCString(
				CCString::createWithFormat("%i/%i", screws, TotalScrews)->getCString());
		if (screws == TotalScrews && (!allstarscollected)){
			this->hud->screwsLabel->runAction(CCShake::actionWithDuration(0.5, 5));
			allstarscollected  = true;

		}
	}
	else
	{
		CCLog("No HUD!!!!");
	}
}

GameLevelScene::GameLevelScene() :
		CCLayer()
{
	current_state = 0;
	GameLevelScene::instance = this;

}
int GameLevelScene::level = 1;

CCSpriteBatchNode* GameLevelScene::batchNode = NULL;

void GameLevelScene::reloadLevel(bool nextLevel )
{
	pauseGame();
	robboSprite->setPosition(ccp(0, 0));
	current_state = 2;
	stopAllActions();

	int tries = CCUserDefault::sharedUserDefault()->getIntegerForKey(CCString::createWithFormat("TriesForLevle%i", GameLevelScene::level)->getCString() , 0);
	if (!nextLevel){
		CCUserDefault::sharedUserDefault()->setIntegerForKey(CCString::createWithFormat("TriesForLevle%i", GameLevelScene::level)->getCString(), ++tries);
		CCDirector::sharedDirector()->replaceScene(GameLevelScene::scene());
	}
	else
	{
		pauseGame();

		int besttries = CCUserDefault::sharedUserDefault()->getIntegerForKey(CCString::createWithFormat("BESTTriesForLevle%i", GameLevelScene::level)->getCString(), INT_MAX);
		int bestTime = CCUserDefault::sharedUserDefault()->getIntegerForKey(CCString::createWithFormat("BESTTimeForLevle%i", GameLevelScene::level)->getCString(), INT_MAX);


		int seconds = (int) (float(std::clock() - begin_time) / CLOCKS_PER_SEC);
		CCUserDefault::sharedUserDefault()->setIntegerForKey(CCString::createWithFormat("LASTTriesForLevle%i", GameLevelScene::level)->getCString(), tries);
		if (tries < besttries){
			CCUserDefault::sharedUserDefault()->setIntegerForKey(CCString::createWithFormat("BESTTriesForLevle%i", GameLevelScene::level)->getCString(), tries);
		}

		CCUserDefault::sharedUserDefault()->setIntegerForKey(CCString::createWithFormat("TriesForLevle%i", GameLevelScene::level)->getCString(), 0);
		CCUserDefault::sharedUserDefault()->setIntegerForKey(CCString::createWithFormat("TimeForLevle%i", GameLevelScene::level)->getCString(), seconds);

		if (seconds < bestTime){
			CCUserDefault::sharedUserDefault()->setIntegerForKey(CCString::createWithFormat("BESTTimeForLevle%i", GameLevelScene::level)->getCString(), seconds);

		}

		hud->addChild(NextLevelLayer::create());
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(respatchFix("Sounds/lelvelUp" SOUND_EXT).c_str());
		CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();

	}


}

void GameLevelScene::resumeGame()
{

	CCObject* tmpobj;
	this->resumeSchedulerAndActions();
	CCARRAY_FOREACH(&objects ,tmpobj)
	{
		((GameSprite*) tmpobj)->resumeSchedulerAndActions();
	}
	current_state = LevelSceneRuning;

}

void GameLevelScene::addObject(GameSprite* object)
{

	GameUtils::addObject(object);


}

void GameLevelScene::initMusic()
{



 	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
	background_music =
		CCString::createWithFormat(respatchFix("Sounds/music/%s"SOUND_EXT).c_str() ,
					((CCString*) map->getProperties()->objectForKey(
							"background_music"))->getCString());
	background_music->retain();
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(
			background_music->getCString(), true);
	//CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Sounds/music/"SOUND_EXT , true);

	GAMEUTILS->setVolume();

}

void GameLevelScene::showWaiting(){
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Sounds/music/ticking_clock"SOUND_EXT);
        CCSize visibleSize = CCDirector::sharedDirector()->getWinSize();
        waitingMenuSprite = CCSprite::createWithSpriteFrameName("menu.png");
        waitingMenuSprite->setPosition(ccp(visibleSize.width/2 ,
                visibleSize.height/2 ));
        hud->addChild(waitingMenuSprite);
        CCLabelBMFont* labelSkip = CCLabelBMFont::create("Fair play ", GAME_MENU_FONTHD_FILE);
        labelSkip->setPosition(ccp((waitingMenuSprite->getContentSize().width / 2)  , waitingMenuSprite->getContentSize().height -50  ));
        waitingMenuSprite->addChild(labelSkip);


        CCLabelBMFont* labelSkipdescription = CCLabelBMFont::create("Wait 10 seconds, or get rid of waiting", GAME_MENU_FONT_FILE);
        labelSkipdescription->setPosition(ccp(waitingMenuSprite->getContentSize().width / 2 , waitingMenuSprite->getContentSize().height -110  ));
        waitingMenuSprite->addChild(labelSkipdescription);
        CCLabelBMFont* labelSkipdescription3 = CCLabelBMFont::create("Buy \"Fair play badge\" ", GAME_MENU_FONT_FILE);
        labelSkipdescription3->setPosition(ccp(waitingMenuSprite->getContentSize().width / 2 , waitingMenuSprite->getContentSize().height -170  ));
        waitingMenuSprite->addChild(labelSkipdescription3);

        waitingMenuSprite->addChild(labelSkipdescription);





        CCLabelBMFont* labelSkipdescription4 = CCLabelBMFont::create("Buy badge?", GAME_MENU_FONTHD_FILE);
        labelSkipdescription4->setPosition(ccp((waitingMenuSprite->getContentSize().width / 2 ) , waitingMenuSprite->getContentSize().height -230  ));
        waitingMenuSprite->addChild(labelSkipdescription4);



        int marrgin = 20;
        CCMenuItemImage *ok = CCMenuItemImage::create("ok.png", "ok.png", this,
        menu_selector(GameLevelScene::onBuyBadge));

        CCMenu* menu = CCMenu::create(ok, NULL);

        menu->setPosition(ccp(750, 100));
        menu->alignItemsHorizontally();
        waitingMenuSprite->addChild(menu);

        waitingMenuSprite->runAction(
                CCSequence::createWithTwoActions(
                        CCShake::actionWithDuration(10.0 , 0.0 ) ,
                        CCCallFunc::create(this,callfunc_selector(GameLevelScene::ShowStarting)
                        )
                ));
        waitingMenuSprite->setVisible(true);

}
void GameLevelScene::onBuyBadge(CCObject* sender){
PaymentService p;
if(p.buyBadge()){
    reloadLevel(false);
}
}

void GameLevelScene::ShowStarting(){

    if(waitingMenuSprite)waitingMenuSprite->setVisible(false);
	//CCSpawn* efect = CCSpawn::create(CCShake::actionWithDuration(0.3, 5), CCScaleTo::create(0.3, 4));
	CCShake* efect = CCShake::actionWithDuration(3, 5);
	CCCallFunc* callback = CCCallFunc::create(this, callfunc_selector(GameLevelScene::ShowStarting));

	if (counter == 3){
		pauseGame();


		CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
		    background_music =
		            CCString::createWithFormat(respatchFix( "Sounds/music/%s"SOUND_EXT).c_str(),
		                    ((CCString*) map->getProperties()->objectForKey(
		                            "background_music"))->getCString());
		    background_music->retain();
		    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(background_music->getCString());



		counterLabel = CCLabelBMFont::create("3", GAME_MENU_FONTHD_FILE);
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(respatchFix("Sounds/321go" SOUND_EXT).c_str());
		hud->addChild(counterLabel);
		CCSize visibleSize = CCDirector::sharedDirector()->getWinSize();
		counterLabel->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2));
		counterLabel->runAction(efect);
		counterLabel->runAction(CCSequence::createWithTwoActions(CCScaleTo::create(0.7, 4), callback));

	}
	else if (counter != 0){
		counterLabel->setScale(1.0);
		counterLabel->setCString(CCString::createWithFormat("%i", counter)->getCString());
		counterLabel->runAction(CCSequence::createWithTwoActions(CCScaleTo::create(0.7, 4), callback));
	}
	else{
		counterLabel->removeFromParentAndCleanup(true);
		resumeGame();
		initMusic();
		begin_time = std::clock();
	}

	counter--;
	updateColletcable();


	//

	//resumeGame();
}
