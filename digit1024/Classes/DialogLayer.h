/*
 * DialogLayer.h
 *
 *  Created on: 22 wrz 2014
 *      Author: Michal
 */

#ifndef DIALOGLAYER_H_
#define DIALOGLAYER_H_
#include "cocos2d.h"

USING_NS_CC;



class DialogLayer : public CCLayer
{
public:

	CREATE_FUNC(DialogLayer);
    virtual bool init();
    DialogLayer();
	virtual ~DialogLayer();
	void setImage(const char* imageName);
	void setText(const char* text);
	

private: 
	CCSize visibleSize;
	CCSize dialogSize;
	CCPoint dialogPoint;
	void BackCallBack(CCObject* pSender);
    
};



#endif /* DIALOGLAYER_H_ */
