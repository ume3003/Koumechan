//
//  StartLayer.h
//  koumeChan
//
//  Created by 上野　彰三 on 2014/03/11.
//
//

#ifndef __koumeChan__StartLayer__
#define __koumeChan__StartLayer__

#include "KcLayer.h"
#include "cocos2d.h"
#include "Native.h"
#include "network/HttpClient.h"
#include "cocosbuilder/cocosbuilder.h"
#include "SSPlayer.h"
#include "SSAnimationData.h"

class StartLayer : public KcLayer , public cocosbuilder::CCBSelectorResolver ,public cocosbuilder::CCBMemberVariableAssigner
{
	
public:
	enum KTAG {
		KTAG_BACKGROUND = 1,
		KTAG_TITLE,
		KTAG_USERNAME,
		KTAG_START = 200,
		KTAG_END,
		KTAG_GOOGLE
	};
	enum CTAG {
		CTAG_BG = 1,
		CTAG_TEXT = 3
	};
	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::Ref* pTarget,const char* pSelectorName);
	virtual cocos2d::extension::Control::Handler onResolveCCBCCControlSelector(cocos2d::Ref* pTarget,const char* pSelectorName);
	virtual bool onAssignCCBMemberVariable(cocos2d::Ref* pTarget, const char* pMemberVariableName, cocos2d::Node* pNode);
	void tappedStart(cocos2d::Ref* pSender,cocos2d::extension::Control::EventType pCCControlEvent);
	void tappedEnd(cocos2d::Ref* pSender,cocos2d::extension::Control::EventType pCCControlEvent);
	void tappedGGPS(cocos2d::Ref* pSender,cocos2d::extension::Control::EventType pCCControlEvent);
    virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	
	CC_SYNTHESIZE_RETAIN(SSAnimationData*, ssaData,SSData);
	CC_SYNTHESIZE_RETAIN(SSPlayer*, ssPlayer, SSPlayer);
	
public:
	StartLayer();
	~StartLayer();
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(StartLayer, create);
	
	void refreshSignInButton();
	
	virtual bool onKCTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
	virtual void onKCTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) {};
	virtual void onKCTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) {};
	virtual void onKCTouchCancelled(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) {};
	
};

#endif /* defined(__koumeChan__StartLayer__) */
