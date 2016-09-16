/*
 * NextLevelLayer.h
 *
 *  Created on: 9 paź 2014
 *      Author: Michal
 */

#ifndef NEXTLEVELLAYER_H_
#define NEXTLEVELLAYER_H_
#include "cocos2d.h"

USING_NS_CC;

class NextLevelLayer: public CCLayer
{
public:
	CREATE_FUNC(NextLevelLayer)

		CCSize visibleSize;
    NextLevelLayer();
	bool init();
	void initParticle();




	void menuFacebook(CCObject* pSender);
	void menuRepeat(CCObject* pSender);
	void menuNext(CCObject* pSender);


    virtual ~NextLevelLayer();
};

#endif /* NEXTLEVELLAYER_H_ */
