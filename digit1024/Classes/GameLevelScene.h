#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "GameUtils.h"
#include "Common/Enums.h"
#include "Sprites/GameSprite.h"
#include "Sprites/Robbo.h"
#include "GameMenuLayer.h"
#include <ctime>

USING_NS_CC;
using namespace cocos2d;

class GameLevelScene: public cocos2d::CCLayer, public GameUtils
{
public:

	enum LevelSceneState
	{
		LevelScenePaused,
		LevelSceneReady,
		LevelSceneRuning,
		LevelSceneStoping,
		LevelSceneLoading,
		LevelSceneSDhowingTutorial
	};

	GameLevelScene();
	virtual bool init();
	void ShowStarting();
	void showWaiting();
	virtual void initObjects();
	virtual void initMusic();

	CREATE_FUNC(GameLevelScene)
	;
	void showDialog(const char* message, const char* image);
	void removeObject(GameSprite*);
	void showExplosion(CCPoint tilePoint);
	void removeExplosion();
	void showKill(CCPoint tilePoint);
	void updateColletcable(int lives, int screws, int ammo ,int keys);
	void updateColletcable();
	void reloadLevel(bool nextLevel = false);
	void addObject(GameSprite* object);
	// implement the "static node()" method manually

	GameMenuLayer* hud;
	Robbo* robboSprite;
	int TotalScrews;
	static int level;
	CCPoint viewPoint;
	static cocos2d::CCScene* scene();

	static GameLevelScene* instance;
	static CCSpriteBatchNode *batchNode;
	int current_state;

	void pauseGame();
	void resumeGame();
	void update(float dt);
	void addPenidingObjects();
	std::clock_t  begin_time;

protected:

private:
	CCSprite* waitingMenuSprite;
	void onBuyBadge(CCObject* sender);
	void onWaitingClosed();
	CCString* background_music;
	CCLayer* bgLayer;
	int counter;
	CCLabelBMFont* counterLabel;

	bool allstarscollected;
	void centerView(CCPoint p);
	void updateGame();
	std::vector<int> updateOrder;
};

#endif // __HELLOWORLD_SCENE_H__
#define GAMEUTILS   GameLevelScene::instance
