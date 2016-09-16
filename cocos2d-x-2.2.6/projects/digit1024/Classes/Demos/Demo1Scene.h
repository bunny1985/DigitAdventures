/*
 * Demo1Scene.h
 *
 *  Created on: 1 paź 2014
 *      Author: Michal
 */

#ifndef DEMO1SCENE_H_
#define DEMO1SCENE_H_


#include "cocos2d.h"
#include "Common/Enums.h"
#include "SimpleAudioEngine.h"


USING_NS_CC;

class Demo1Scene : public CCLayer
{
public:
    Demo1Scene();
	CREATE_FUNC(Demo1Scene);
	virtual bool init();
	static cocos2d::CCScene* scene();
    virtual ~Demo1Scene();
};

#endif /* DEMO1SCENE_H_ */
