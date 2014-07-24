//
//  Modal.h
//  kc
//
//  Created by 上野　彰三 on 2014/01/14.
//
//

#ifndef __kc__Modal__
#define __kc__Modal__

#include "cocos2d.h"
#include "cocos-ext.h"

class Modal : public cocos2d::Layer
{
public:
	virtual bool init();
	virtual void onExit();
	virtual void ExitDlg();
protected:
	Modal();
	virtual ~Modal();
	virtual void removeOwn(cocos2d::Node* pBlock);
	
	virtual bool onKCTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
	virtual void onKCTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) {};
	virtual void onKCTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) {};
	virtual void onKCTouchCancelled(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) {};
	virtual cocos2d::Rect getBaseBoudingBox()		{ return getBoundingBox();};
	virtual void afterExit(cocos2d::Node* parent) {};
	
	CC_SYNTHESIZE_RETAIN(cocos2d::EventListenerTouchOneByOne*, m_listener, Listener);
};
#endif /* defined(__kc__Modal__) */
