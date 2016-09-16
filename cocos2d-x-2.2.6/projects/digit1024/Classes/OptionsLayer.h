/*
 * OptionsLayer.h
 *
 *  Created on: 21 wrz 2013
 *      Author: michal
 */

#ifndef OPTIONSLAYER_H_
#define OPTIONSLAYER_H_
#include "cocos2d.h"
#include "Common/Enums.h"
USING_NS_CC;





class OptionsLayer : public CCLayer{
public:

	CREATE_FUNC(OptionsLayer)
	;
	static cocos2d::CCScene* scene();
	virtual bool init();
	CC_SYNTHESIZE_RETAIN(CCLabelBMFont* , _musicLabel , MusicVolumeLabel);
	CC_SYNTHESIZE_RETAIN(CCLabelBMFont* , _soundlabel , SoundVolumeLabel);


	void backCallcBack(CCObject * pSender);
	void openInstruction(CCObject * pSender);
	void openMoreApps(CCObject * pSender);
#ifdef KEYBOARD_SUPPORT
	virtual void keyReleased(int keyCode){};
	virtual void keyPressed(int keyCode){};
#endif

	bool ccTouchBegan(CCTouch *touch, CCEvent * pEvent);
	void ccTouchEnded(CCTouch *touch, CCEvent * pEvent);
	void ccTouchCancelled(CCTouch *touch, CCEvent * pEvent);

	void ccTouchMoved(CCTouch *touch, CCEvent * pEvent);

	OptionsLayer();
	virtual ~OptionsLayer();
private:
	CCSprite* musicVolumeSlider;
	CCSprite* soundVolumeSlider;
	CCSprite* musicPointer;
	CCSprite* soundPointer;
	CCSprite* currentSlider;
};

#endif /* OPTIONSLAYER_H_ */
