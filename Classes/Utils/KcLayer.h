//
//  KcLayer.h
//  kc
//
//  Created by 上野　彰三 on 2014/01/17.
//
//

#ifndef __kc__KcLayer__
#define __kc__KcLayer__

#include "cocos2d.h"


class KcLayer : public cocos2d::Layer
{
public:
	virtual void onSecTimer()	{};
	void updateLabelBMFont(cocos2d::Node* parent,int tag,const char* val);
protected:
	// Helper
	void initControl(cocos2d::Node* pNode,bool bTop,bool bVisible);
    KcLayer();
    virtual ~KcLayer();
    
	virtual bool init();
	virtual void onExit();
	virtual bool onKCTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) = 0;
	virtual void onKCTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) = 0;
	virtual void onKCTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) = 0;
	virtual void onKCTouchCancelled(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) = 0;

	CC_SYNTHESIZE_RETAIN(cocos2d::EventListenerTouchOneByOne*, m_listener, Listener);

};

#endif /* defined(__kc__KcLayer__) */
