/*
 * SelecLevelLayer.h
 *
 *  Created on: 21 wrz 2013
 *      Author: michal
 */

#ifndef SELECLEVELLAYER_H_
#define SELECLEVELLAYER_H_
#include "cocos2d.h"
#include "Common/Enums.h"
USING_NS_CC;







class SelecLevelLayer: public cocos2d::CCLayer
	{
public:

	virtual bool init();


	static cocos2d::CCScene* scene();CREATE_FUNC(SelecLevelLayer)
	;
	int getLevelsQuantity(){
		return 100;
	}
	void AddLevelSprite(int levelnumber, bool isActive);


	void backCallBack(CCObject * pSender);

	SelecLevelLayer();
	virtual ~SelecLevelLayer();


	bool ccTouchBegan(CCTouch *touch, CCEvent * pEvent);
	void ccTouchEnded(CCTouch *touch, CCEvent * pEvent);
	void ccTouchCancelled(CCTouch *touch, CCEvent * pEvent);
	void ccTouchMoved(CCTouch *touch, CCEvent * pEvent);


	private:
		int levelSprites;
		CCNode* levelsContainer;
		int posTouchBegin;
		void ScaleStars();

};

#endif /* SELECLEVELLAYER_H_ */
