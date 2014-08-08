//
//  KcSprite.h
//  koumeChan
//
//  Created by 上野　彰三 on 2014/04/02.
//
//

#ifndef __koumeChan__KcSprite__
#define __koumeChan__KcSprite__

#include "cocos2d.h"
#include "SSPlayer.h"


class KcSprite : public SSPlayer
{
public:
	virtual void onSecTimer()	{};
protected:
	// Helper
    KcSprite();
    virtual ~KcSprite();
    
	virtual bool init();
	virtual void onExit();
	virtual bool onKCTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) = 0;
	virtual void onKCTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) = 0;
	virtual void onKCTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) = 0;
	virtual void onKCTouchCancelled(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) = 0;
	
	CC_SYNTHESIZE_RETAIN(cocos2d::EventListenerTouchOneByOne*, m_listener, Listener);
	void registerTouchEvent();
};
#endif /* defined(__koumeChan__KcSprite__) */
