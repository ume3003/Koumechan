//
//  MainUILayer.cpp
//  koumeChan
//
//  Created by 上野　彰三 on 2014/03/12.
//
//
#include "KcLayer.h"
#include "MainUILayer.h"
#include "KoumeChan.h"
#include "KCDef.h"
#include "JsonKeyString.h"
#include "MainScene.h"
#include "DirectionQuest.h"

using namespace cocos2d;
using namespace cocosbuilder;
using namespace cocos2d::extension;

MainUILayer::MainUILayer():m_topBar(NULL),m_mainBar(NULL),m_subMenu(NULL),m_questMenu(NULL),m_taisenMenu(NULL),m_currentMenu(NULL),m_NameTTF(NULL),m_RemainTTF(NULL),m_StaminaFont(NULL),m_GoldFont(NULL),m_MoneyFont(NULL)
{
	
};

MainUILayer::~MainUILayer()
{
	CC_SAFE_RELEASE(m_topBar);
	CC_SAFE_RELEASE(m_mainBar);
	CC_SAFE_RELEASE(m_subMenu);
	CC_SAFE_RELEASE(m_questMenu);
	CC_SAFE_RELEASE(m_taisenMenu);
	
	CC_SAFE_RELEASE(m_MoneyFont);
	CC_SAFE_RELEASE(m_GoldFont);
	CC_SAFE_RELEASE(m_StaminaFont);
	CC_SAFE_RELEASE(m_RemainTTF);
	CC_SAFE_RELEASE(m_NameTTF);
};

bool MainUILayer::onAssignCCBMemberVariable(Ref* pTarget, const char* pMemberVariableName, Node* pNode)
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_topBar"	, Node*		, m_topBar);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_MainBar"	, Node*		, m_mainBar);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_subMenu"	, Node*		, m_subMenu);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_questMenu"	, Node*		, m_questMenu);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_taisenMenu", Node*		, m_taisenMenu);
	
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_NameTTF", Label*, m_NameTTF);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_RemainTTF", Label*, m_RemainTTF);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_StaminaFont", Label*, m_StaminaFont);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_GoldFont", Label*, m_GoldFont);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_MoneyFont", Label*, m_MoneyFont);
	
	
	return false;
};

SEL_MenuHandler MainUILayer::onResolveCCBCCMenuItemSelector(cocos2d::Ref *pTarget, const char *pSelectorName)
{
	return NULL;
};

Control::Handler MainUILayer::onResolveCCBCCControlSelector(cocos2d::Ref *pTarget, const char *pSelectorName)
{

    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "tappedExit"		, MainUILayer::tappedExit);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "tappedTaisen"	, MainUILayer::tappedTaisen);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "tappedDirection"	, MainUILayer::tappedDirection);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "tappedMain"		, MainUILayer::tappedMain);

	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "mainInfo"		, MainUILayer::mainInfo);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "mainStatus"		, MainUILayer::mainStatus);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "mainFriend"		, MainUILayer::mainFriend);

    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "questCenter"		, MainUILayer::questCenter);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "questEast"		, MainUILayer::questEast);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "questWest"		, MainUILayer::questWest);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "questSouth"		, MainUILayer::questSouth);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "questNorth"		, MainUILayer::questNorth);

	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "taisenFree"		, MainUILayer::taisenFree);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "taisennFriend"	, MainUILayer::taisenFriend);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "taisenPublic"	, MainUILayer::taisenPublic);
	return NULL;
};

void MainUILayer::tappedMain(cocos2d::Ref* pSender,cocos2d::extension::Control::EventType pCCControlEvent)
{
	changeStateNode(m_subMenu, true);
};

void MainUILayer::tappedDirection(cocos2d::Ref* pSender,cocos2d::extension::Control::EventType pCCControlEvent)
{
	changeStateNode(m_questMenu, true);
};

void MainUILayer::tappedTaisen(cocos2d::Ref* pSender,cocos2d::extension::Control::EventType pCCControlEvent)
{
	changeStateNode(m_taisenMenu, true);
};

void MainUILayer::mainInfo(cocos2d::Ref* pSender,cocos2d::extension::Control::EventType pCCControlEvent)
{
	((MainScene*)getParent())->getServerTime();
	closeStateNode(m_mainBar);
}
void MainUILayer::mainStatus(cocos2d::Ref* pSender,cocos2d::extension::Control::EventType pCCControlEvent)
{
	closeStateNode(m_mainBar);
	
}
void MainUILayer::mainFriend(cocos2d::Ref* pSender,cocos2d::extension::Control::EventType pCCControlEvent)
{
	closeStateNode(m_mainBar);
	
}
void MainUILayer::questCenter(cocos2d::Ref* pSender,cocos2d::extension::Control::EventType pCCControlEvent)
{
	KoumeChan::getInstance()->changeDirection(DirectionQuest::CENTER);
	((MainScene*)getParent())->showMajorQuestLayer();
	closeStateNode(m_questMenu);
	
}
void MainUILayer::questEast(cocos2d::Ref* pSender,cocos2d::extension::Control::EventType pCCControlEvent)
{
	KoumeChan::getInstance()->changeDirection(DirectionQuest::EAST);
	((MainScene*)getParent())->showMajorQuestLayer();
	closeStateNode(m_questMenu);
	
}
void MainUILayer::questWest(cocos2d::Ref* pSender,cocos2d::extension::Control::EventType pCCControlEvent)
{
	KoumeChan::getInstance()->changeDirection(DirectionQuest::WEST);
	((MainScene*)getParent())->showMajorQuestLayer();
	closeStateNode(m_questMenu);
	
}
void MainUILayer::questNorth(cocos2d::Ref* pSender,cocos2d::extension::Control::EventType pCCControlEvent)
{
	KoumeChan::getInstance()->changeDirection(DirectionQuest::NORTH);
	((MainScene*)getParent())->showMajorQuestLayer();
	closeStateNode(m_questMenu);
	
}
void MainUILayer::questSouth(cocos2d::Ref* pSender,cocos2d::extension::Control::EventType pCCControlEvent)
{
	KoumeChan::getInstance()->changeDirection(DirectionQuest::SOUTH);
	((MainScene*)getParent())->showMajorQuestLayer();
	closeStateNode(m_questMenu);
	
}
	
void MainUILayer::taisenFree(cocos2d::Ref* pSender,cocos2d::extension::Control::EventType pCCControlEvent)
{
	closeStateNode(m_taisenMenu);
	
}
void MainUILayer::taisenFriend(cocos2d::Ref* pSender,cocos2d::extension::Control::EventType pCCControlEvent)
{
	((MainScene*)getParent())->showFriendMatchLayer();
	closeStateNode(m_taisenMenu);
	
}
void MainUILayer::taisenPublic(cocos2d::Ref* pSender,cocos2d::extension::Control::EventType pCCControlEvent)
{
	
	closeStateNode(m_taisenMenu);
	
}
void MainUILayer::tappedExit(cocos2d::Ref *pSender, Control::EventType pCCControlEvent)
{
	KoumeChan::getInstance()->showStartScene();
};

bool MainUILayer::init()
{
	if(KcLayer::init()){
		return true;
	}
	return false;
};

void MainUILayer::onEnterTransitionDidFinish()
{
//	KoumeChan* chan = KoumeChan::getInstance();
	KcLayer::onEnterTransitionDidFinish();
	m_subMenu->setScale(0.01f);
	m_questMenu->setScale(0.01f);
	m_taisenMenu->setScale(0.01f);
	m_subMenu->setVisible(true);
	m_questMenu->setVisible(true);
	m_taisenMenu->setVisible(true);
};

void MainUILayer::onEnter()
{
	KcLayer::onEnter();
	initControl(m_topBar, true, true);
	initControl(m_mainBar, false, true);
	initControl(m_subMenu, false, false);
	initControl(m_questMenu, false, false);
	initControl(m_taisenMenu, false,false);
	KoumeChan* chan = KoumeChan::getInstance();
	GameCharacter* chara = chan->getGameCharacter();
	if(chara){
		m_NameTTF->setString(chan->getDisplayName().asString());
	
		m_StaminaFont->setString(StringUtils::format("%ld",chara->getStamina()));
		m_GoldFont->setString(StringUtils::format("%ld",chara->getGold()));
		m_MoneyFont->setString(StringUtils::format("%ld",chara->getMoney()));
	}
	
	
};
void MainUILayer::changeStateNode(cocos2d::Node *node, bool bShow)
{
	if(node){
		// なにもなし→開く
		// 開いてる→閉じる→新しいのを開く
		// 開いてる→閉じる
		Node* prev = getCurrentMenu();
		if(!prev || node->getTag() != prev->getTag()){
			setCurrentMenu(node);
			Sequence* seq = Sequence::create(ScaleTo::create(0.3f,1.0f),NULL);
			node->runAction(seq);
		}
		else{
			setCurrentMenu(NULL);
		}
		if(prev){
			Sequence* seq = Sequence::create(ScaleTo::create(0.3f,0.0f),NULL);
			prev->runAction(seq);
		}
	}
};
void MainUILayer::closeStateNode(cocos2d::Node *node)
{
	Node* prev = getCurrentMenu();
	Sequence* seq = Sequence::create(ScaleTo::create(0.3f,0.0f),NULL);
	if(prev){
		prev->runAction(seq);		
	}
	setCurrentMenu(NULL);
}
bool MainUILayer::onKCTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)
{
	Point loc2 = pTouch->getLocation();
	Rect topBarRC = m_topBar->getBoundingBox();
	Rect mainBarRC = m_mainBar->getBoundingBox();
	Rect subMenuRC = m_subMenu->getBoundingBox();
	Rect questMenuRc = m_questMenu->getBoundingBox();
	Rect taisenMenuRc = m_taisenMenu->getBoundingBox();
	
	if(mainBarRC.containsPoint(loc2) || topBarRC.containsPoint(loc2) || subMenuRC.containsPoint(loc2) || questMenuRc.containsPoint(loc2) || taisenMenuRc.containsPoint(loc2)){
		pEvent->stopPropagation();
		return true;
	}
	return false;
};


