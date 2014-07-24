//
//  PuzzleUILayer.h
//  koumeChan
//
//  Created by 上野　彰三 on 2014/03/25.
//
//

#ifndef __koumeChan__PuzzleUILayer__
#define __koumeChan__PuzzleUILayer__

#include "cocos2d.h"
#include "cocosbuilder/cocosbuilder.h"
#include "KcLayer.h"

class PuzzleUILayer : public KcLayer , public cocosbuilder::CCBSelectorResolver ,public cocosbuilder::CCBMemberVariableAssigner
{
	
public:
	enum KTAG {
	};
	enum CTAG {
	};
	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::Ref* pTarget,const char* pSelectorName);
	virtual cocos2d::extension::Control::Handler onResolveCCBCCControlSelector(cocos2d::Ref* pTarget,const char* pSelectorName);
	virtual bool onAssignCCBMemberVariable(cocos2d::Ref* pTarget, const char* pMemberVariableName, cocos2d::Node* pNode);
	
	void tappedExit(cocos2d::Ref* pSender,cocos2d::extension::Control::EventType pCCControlEvent);
	void tappedSS(cocos2d::Ref* pSender,cocos2d::extension::Control::EventType pCCControlEvent);
	void tappedItem(cocos2d::Ref* pSender,cocos2d::extension::Control::EventType pCCControlEvent);
	void tappedLB(cocos2d::Ref* pSender,cocos2d::extension::Control::EventType pCCControlEvent);
	
	void setUnitSprite();
    virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual bool init();
	
	CC_SYNTHESIZE(long ,m_Player1MaxHP,Player1MaxHP);
	CC_SYNTHESIZE(long ,m_Player2MaxHP,Player2MaxHP);
	
	CC_SYNTHESIZE_RETAIN(cocos2d::Node*		,m_Scorepanel	, ScorePanel);
	CC_SYNTHESIZE_RETAIN(cocos2d::Node*		,m_BasePanel	, BasePanel);
	CC_SYNTHESIZE_RETAIN(cocos2d::Sprite*	,m_faceSprite	, FaceSprite);
	CC_SYNTHESIZE_RETAIN(cocos2d::Label*	,m_chatText		, ChatText);
	CC_SYNTHESIZE_RETAIN(cocos2d::Label*	,m_Player1HP	, Player1HP);
	CC_SYNTHESIZE_RETAIN(cocos2d::Label*	,m_Player1Power	, Player1Power);
	CC_SYNTHESIZE_RETAIN(cocos2d::Label*	,m_Player2HP	, Player2HP);
	CC_SYNTHESIZE_RETAIN(cocos2d::Label*	,m_Player2Power	, Player2Power);
	CC_SYNTHESIZE_RETAIN(cocos2d::Layer*	,m_Player1HPBar , Player1HPBar);
	CC_SYNTHESIZE_RETAIN(cocos2d::Layer*	,m_Player2HPBar , Player2HPBar);
	CC_SYNTHESIZE_RETAIN(cocos2d::Layer*	,m_Player1PWBar , Player1PWBar);
	CC_SYNTHESIZE_RETAIN(cocos2d::Layer*	,m_Player2PWBar , Player2PWBar);
	
	CC_SYNTHESIZE_RETAIN(cocos2d::Sprite*	, m_Player1Face, Player1Face);
	CC_SYNTHESIZE_RETAIN(cocos2d::Sprite*	, m_Player2Face, Player2Face);
	
	CC_SYNTHESIZE_RETAIN(cocos2d::Sprite*   , m_unit1		, Unit1);
	CC_SYNTHESIZE_RETAIN(cocos2d::Sprite*   , m_unit2		, Unit2);
	
	CC_SYNTHESIZE_RETAIN(cocos2d::Node*, m_Player1PhaseBase, Player1PhaseBase);
	CC_SYNTHESIZE_RETAIN(cocos2d::Node*, m_Player2PhaseBase, Player2PhaseBase);
	
	CC_SYNTHESIZE_RETAIN(cocos2d::extension::ControlButton*, m_LBButton, LBButton);
	
public:
	PuzzleUILayer();
	~PuzzleUILayer();
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(PuzzleUILayer, create);
	
	virtual bool onKCTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
	virtual void onKCTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) {};
	virtual void onKCTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) {};
	virtual void onKCTouchCancelled(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) {};

	void	setChatMessage(std::string strMessage);
	void	clearCharMessage();
	
	void	changePlayer1HP(long score);
	void	changePlayer2HP(long score);
	void	changePlayer1Power(long power);
	void	changePlayer2Power(long power);
	
	void	setLBEnable(int LBLevel);
	void	showPayer1PhaseCount(int maxCount,int currentCount);
	void	showPayer2PhaseCount(int maxCount,int currentCount);

};
#endif /* defined(__koumeChan__PuzzleUILayer__) */
