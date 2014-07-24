//
//  MainUILayer.h
//  koumeChan
//
//  Created by 上野　彰三 on 2014/03/12.
//
//

#ifndef __koumeChan__MainUILayer__
#define __koumeChan__MainUILayer__

#include "cocos2d.h"
#include "cocosbuilder/cocosbuilder.h"
#include "KcLayer.h"

class MainUILayer : public KcLayer , public cocosbuilder::CCBSelectorResolver ,public cocosbuilder::CCBMemberVariableAssigner
{
	
public:
	enum KTAG {
		TAG_NAME = 50,
		TAG_STAMINA ,
		TAG_CENTER,
		TAG_EAST,
		TAG_WEST,
		TAG_SOUTH,
		TAG_NORTH
	};
	enum CTAG {
		CTAG_BG = 1,
		CTAG_TEXT = 3
	};
	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::Ref* pTarget,const char* pSelectorName);
	virtual cocos2d::extension::Control::Handler onResolveCCBCCControlSelector(cocos2d::Ref* pTarget,const char* pSelectorName);
	virtual bool onAssignCCBMemberVariable(cocos2d::Ref* pTarget, const char* pMemberVariableName, cocos2d::Node* pNode);
	
	void tappedMain(cocos2d::Ref* pSender,cocos2d::extension::Control::EventType pCCControlEvent);
	void tappedDirection(cocos2d::Ref* pSender,cocos2d::extension::Control::EventType pCCControlEvent);
	void tappedTaisen(cocos2d::Ref* pSender,cocos2d::extension::Control::EventType pCCControlEvent);
	void tappedExit(cocos2d::Ref* pSender,cocos2d::extension::Control::EventType pCCControlEvent);
	
	void mainInfo(cocos2d::Ref* pSender,cocos2d::extension::Control::EventType pCCControlEvent);
	void mainStatus(cocos2d::Ref* pSender,cocos2d::extension::Control::EventType pCCControlEvent);
	void mainFriend(cocos2d::Ref* pSender,cocos2d::extension::Control::EventType pCCControlEvent);
	
	void questCenter(cocos2d::Ref* pSender,cocos2d::extension::Control::EventType pCCControlEvent);
	void questEast(cocos2d::Ref* pSender,cocos2d::extension::Control::EventType pCCControlEvent);
	void questWest(cocos2d::Ref* pSender,cocos2d::extension::Control::EventType pCCControlEvent);
	void questNorth(cocos2d::Ref* pSender,cocos2d::extension::Control::EventType pCCControlEvent);
	void questSouth(cocos2d::Ref* pSender,cocos2d::extension::Control::EventType pCCControlEvent);
	
	void taisenFree(cocos2d::Ref* pSender,cocos2d::extension::Control::EventType pCCControlEvent);
	void taisenFriend(cocos2d::Ref* pSender,cocos2d::extension::Control::EventType pCCControlEvent);
	void taisenPublic(cocos2d::Ref* pSender,cocos2d::extension::Control::EventType pCCControlEvent);
	
	
    virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual bool init();
	
	CC_SYNTHESIZE_RETAIN(cocos2d::Node*, m_topBar		, TopBar);
	CC_SYNTHESIZE_RETAIN(cocos2d::Node*, m_mainBar		, mainBar);
	CC_SYNTHESIZE_RETAIN(cocos2d::Node*, m_subMenu		, SubMenu);
	CC_SYNTHESIZE_RETAIN(cocos2d::Node*, m_questMenu	, QuestMenu);
	CC_SYNTHESIZE_RETAIN(cocos2d::Node*, m_taisenMenu	, TaisenMenu);
	CC_SYNTHESIZE_RETAIN(cocos2d::Label*, m_NameTTF  , NameTTF);
	CC_SYNTHESIZE_RETAIN(cocos2d::Label*, m_RemainTTF  , RemainTTF);
	CC_SYNTHESIZE_RETAIN(cocos2d::Label*, m_StaminaFont  , StaminaFont);
	CC_SYNTHESIZE_RETAIN(cocos2d::Label*, m_GoldFont  , GoldFont);
	CC_SYNTHESIZE_RETAIN(cocos2d::Label*, m_MoneyFont  , MoneyFont);
	
	
	CC_SYNTHESIZE_RETAIN(cocos2d::Node*, m_currentMenu, CurrentMenu);
	void changeStateNode(cocos2d::Node* node,bool bShow);
	void closeStateNode(cocos2d::Node* node);
	
public:
	MainUILayer();
	~MainUILayer();
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(MainUILayer, create);
	
	virtual bool onKCTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
	virtual void onKCTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) {};
	virtual void onKCTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) {};
	virtual void onKCTouchCancelled(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) {};
};

#endif /* defined(__koumeChan__MainUILayer__) */
