/*
 * AboutLayer.h
 *
 *  Created on: 26 wrz 2013
 *      Author: michal
 */

#ifndef ABOUTLAYER_H_
#define ABOUTLAYER_H_

#include "cocos2d.h"
#include "Common/Enums.h"
USING_NS_CC;
class AboutLayer :public CCLayer
{
public:
	static cocos2d::CCScene* scene();
	CREATE_FUNC(AboutLayer);
	AboutLayer();
	virtual bool init();
	void backCallcBack(CCObject * pSender);
	virtual ~AboutLayer();
};

#endif /* ABOUTLAYER_H_ */
