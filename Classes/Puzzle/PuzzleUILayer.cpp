//
//  PuzzleUILayer.cpp
//  koumeChan
//
//  Created by 上野　彰三 on 2014/03/25.
//
//

#include "PuzzleUILayer.h"
#include "KcLayer.h"
#include "KoumeChan.h"
#include "KCDef.h"
#include "JsonKeyString.h"
#include "PuzzleScene.h"
#include "MinorQuest.h"
#include "Emotion.h"

using namespace std;
using namespace cocos2d;
using namespace cocosbuilder;
using namespace cocos2d::extension;

PuzzleUILayer::PuzzleUILayer():m_Scorepanel(NULL),m_BasePanel(NULL),m_faceSprite(NULL),m_chatText(NULL),m_Player1Power(NULL),m_Player1HP(NULL),m_Player2Power(NULL),m_Player2HP(NULL),m_Player1HPBar(NULL),m_Player2HPBar(NULL),m_Player1PWBar(NULL),m_Player2PWBar(NULL),m_Player1Face(NULL),m_Player2Face(NULL),m_LBButton(NULL),m_Player1PhaseBase(NULL),m_Player2PhaseBase(NULL),m_unit1(NULL),m_unit2(NULL)
{
	
};

PuzzleUILayer::~PuzzleUILayer()
{
	CC_SAFE_RELEASE(m_Scorepanel);
	CC_SAFE_RELEASE(m_BasePanel);
	CC_SAFE_RELEASE(m_chatText);
	CC_SAFE_RELEASE(m_faceSprite);
	CC_SAFE_RELEASE(m_Player1Power);
	CC_SAFE_RELEASE(m_Player1HP);
	CC_SAFE_RELEASE(m_Player2Power);
	CC_SAFE_RELEASE(m_Player2HP);
	CC_SAFE_RELEASE(m_Player1PWBar);
	CC_SAFE_RELEASE(m_Player1HPBar);
	CC_SAFE_RELEASE(m_Player2PWBar);
	CC_SAFE_RELEASE(m_Player2HPBar);
	
	CC_SAFE_RELEASE(m_Player1Face);
	CC_SAFE_RELEASE(m_Player2Face);
	CC_SAFE_RELEASE(m_Player1PhaseBase);
	CC_SAFE_RELEASE(m_Player2PhaseBase);
	
	CC_SAFE_RELEASE(m_unit1);
	CC_SAFE_RELEASE(m_unit2);
	
	CC_SAFE_RELEASE(m_LBButton);
};

bool PuzzleUILayer::onAssignCCBMemberVariable(Ref* pTarget, const char* pMemberVariableName, Node* pNode)
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_ScorePanel"	, Node*		, m_Scorepanel);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_BasePanel"		, Node*		, m_BasePanel);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_chatText"		, Label*	, m_chatText);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_faceSprite"	, Sprite*	, m_faceSprite);

	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_Player2PWBar"	, Layer*	, m_Player2PWBar);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_Player2HPBar"	, Layer*	, m_Player2HPBar);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_Player1PWBar"	, Layer*	, m_Player1PWBar);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_Player1HPBar"	, Layer*	, m_Player1HPBar);
	
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_Player2Power"	, Label*	, m_Player2Power);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_Player2HP"		, Label*	, m_Player2HP);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_Player1Power"	, Label*	, m_Player1Power);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_Player1HP"		, Label*	, m_Player1HP);
	
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_Player1Face"	, Sprite*	, m_Player1Face);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_Player2Face"	, Sprite*	, m_Player2Face);

	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_Player1PhaseBase", Node*	, m_Player1PhaseBase);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_Player2PhaseBase", Node*	, m_Player2PhaseBase);
	
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_unit1", Sprite*	, m_unit1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_unit2", Sprite*	, m_unit2);
	
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_LBButton"	, extension::ControlButton*	, m_LBButton);
	return false;
};

SEL_MenuHandler PuzzleUILayer::onResolveCCBCCMenuItemSelector(cocos2d::Ref *pTarget, const char *pSelectorName)
{
	return NULL;
};

Control::Handler PuzzleUILayer::onResolveCCBCCControlSelector(cocos2d::Ref *pTarget, const char *pSelectorName)
{
	
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "tappedExit"	, PuzzleUILayer::tappedExit);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "tappedSS"	, PuzzleUILayer::tappedSS);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "tappedItem"	, PuzzleUILayer::tappedItem);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "tappedLB"	, PuzzleUILayer::tappedLB);
	return NULL;
};

void PuzzleUILayer::tappedExit(Ref* pSender,Control::EventType pCCControlEvent)
{
	PuzzleScene* scene = (PuzzleScene*)getParent();
	if(scene){
		if(scene->getPlayable()){
			KoumeChan::getInstance()->showYNDialog(scene);
		}
	}
};

void PuzzleUILayer::tappedSS(Ref* pSender,Control::EventType pCCControlEvent)
{
	MinorQuest* quest = KoumeChan::getInstance()->getMinorQuestMaster();
	log("%s",StringUtils::format("%s-%s",quest->getName().asString().c_str(),KoumeChan::getInstance()->getCurrentTimeString().c_str()).c_str());
	KoumeChan::getInstance()->takeScreenShot(StringUtils::format("%s-%s",V2C(quest->getName()),KoumeChan::getInstance()->getCurrentTimeString().c_str()));
};

void PuzzleUILayer::tappedItem(Ref* pSender,Control::EventType pCCControlEvent)
{
	PuzzleScene* scene = (PuzzleScene*)getParent();
	if(scene){
		if(scene->getPlayable()){
	//		scene->doShuffle();
		}
	}
};
void PuzzleUILayer::tappedLB(Ref* pSender,Control::EventType pCCControlEvent)
{
	PuzzleScene* scene = (PuzzleScene*)getParent();
	if(scene){
		if(scene->getPlayable()){
			m_LBButton->setVisible(false);
			scene->userAllLBCommand();
			scene->skillAttackAnimation();
		}
	}
};


void PuzzleUILayer::setChatMessage(std::string strMessage)
{
	Label* ttf = getChatText();
	if(ttf){
		ttf->setString(strMessage);
		Sequence* seq = Sequence::create(DelayTime::create(3.0f),CallFunc::create([this]{
			this->clearCharMessage();
		}
		), NULL);
		ttf->runAction(seq);
	}
}
void PuzzleUILayer::clearCharMessage()
{
	Label* ttf = getChatText();
	if(ttf){
		ttf->setString("");
	}
}

void PuzzleUILayer::setLBEnable(int LBLevel)
{
	if(LBLevel == 0){
		m_LBButton->setVisible(false);
	}
	else{
		std::string lbString = StringUtils::format("LB %d",LBLevel);
		m_LBButton->setVisible(true);
		m_LBButton->setTitleForState(lbString.c_str(), extension::Control::State::NORMAL);
	}
}

void	PuzzleUILayer::changePlayer1HP(long hitpoint)
{
	std::string str = StringUtils::format("%ld / %ld",hitpoint,getPlayer1MaxHP());
	m_Player1HP->setString(str);
	if(getPlayer1MaxHP() > 0){
		float rate = (float)hitpoint / (float)getPlayer1MaxHP();
		Sequence* seq = Sequence::create(ScaleTo::create(0.1f,MAX(0.0f,rate),1),NULL);
		m_Player1HPBar->runAction(seq);
//		m_Player1HPBar->setScaleX(MAX(0.0f,rate));
	}
};
void	PuzzleUILayer::changePlayer2HP(long hitpoint)
{
	std::string str = StringUtils::format("%ld / %ld",hitpoint,getPlayer2MaxHP());
	m_Player2HP->setString(str);
	if(getPlayer2MaxHP() > 0){
		float rate = (float)hitpoint / (float)getPlayer2MaxHP();
		Sequence* seq = Sequence::create(ScaleTo::create(0.1f,MAX(0.0f,rate),1),NULL);
		m_Player2HPBar->runAction(seq);
//		m_Player2HPBar->setScaleX(MAX(0.0f,rate));
	}
};
void	PuzzleUILayer::changePlayer1Power(long power)
{
	std::string str = StringUtils::format("%ld",power);
	if(m_Player1Power){
		m_Player1Power->setString(str);
	}
	float rate = (float)power / (float)MAXPOWER;
	if(m_Player1PWBar){
		m_Player1PWBar->setScaleX(MAX(0.0f,rate));
	}
};
void	PuzzleUILayer::changePlayer2Power(long power)
{
	std::string str = StringUtils::format("%ld",power);
	if(m_Player2Power){
		m_Player2Power->setString(str);
	}
	float rate = (float)power / (float)MAXPOWER;
	if(m_Player2PWBar){
		m_Player2PWBar->setScaleX(MAX(0.0f,rate));
	}
};

void PuzzleUILayer::showPayer1PhaseCount(int maxCount,int currentCount)
{
	if(m_Player1PhaseBase && maxCount > 0){
		Size baseSize = m_Player1PhaseBase->getContentSize();
		int width = (int)baseSize.width / maxCount;
		for(int i = 0;i < maxCount;i++){
			Sprite* sp = (Sprite*)m_Player1PhaseBase->getChildByTag(i);
			Emotion::EMOTION_TYPE type = i < currentCount ? Emotion::MARU0 : Emotion::BATSU0;
			if(sp == NULL){
				sp = Emotion::getInstance()->getSprite(type);
				sp->setPosition(Point(i * width,0));
				m_Player1PhaseBase->addChild(sp, 98, i);
			}
			else{
				sp->setSpriteFrame(Emotion::getInstance()->getSpriteFrameName(type));
			}
		}
	}
};
void PuzzleUILayer::showPayer2PhaseCount(int maxCount,int currentCount)
{
	if(m_Player2PhaseBase && maxCount > 0){
		Size baseSize = m_Player2PhaseBase->getContentSize();
		int width = (int)baseSize.width / maxCount;
		for(int i = 0;i < maxCount;i++){
			Sprite* sp = (Sprite*)m_Player2PhaseBase->getChildByTag(i);
			Emotion::EMOTION_TYPE type = i < currentCount ? Emotion::MARU0 : Emotion::BATSU0;
			if(sp == NULL){
				sp = Emotion::getInstance()->getSprite(type);
				sp->setPosition(Point(i * width,0));
				m_Player2PhaseBase->addChild(sp, 98, i);
			}
			else{
				sp->setSpriteFrame(Emotion::getInstance()->getSpriteFrameName(type));
			}
		}
	}
	
};


bool PuzzleUILayer::init()
{
	if(KcLayer::init()){
		return true;
	}
	return false;
};

void PuzzleUILayer::onEnterTransitionDidFinish()
{
	KcLayer::onEnterTransitionDidFinish();
	PuzzleScene* scene = (PuzzleScene*)getParent();
	if(scene){
		setUnitSprite();
		setPlayer1MaxHP(scene->getHitpoit(PuzzleScene::PHASE_PLAYER_1));
		setPlayer2MaxHP(scene->getHitpoit(PuzzleScene::PHASE_PLAYER_2));
		scene->updateScore();
	}
	
	clearCharMessage();
};

void PuzzleUILayer::onEnter()
{
	KcLayer::onEnter();
	initControl(m_Scorepanel, true, true);
	initControl(m_BasePanel, false, true);
};

void PuzzleUILayer::showUnitSprite(bool bShow)
{
	if(m_unit1){
		m_unit1->setVisible(bShow);
	}
	if(m_unit2){
		m_unit2->setVisible(bShow);
	}
}

void PuzzleUILayer::setUnitSprite()
{
	PuzzleScene* scene = (PuzzleScene*)getParent();
	string frameName1 = scene->getOwnUnitSpriteFrameName(0);
	string frameName2 = scene->getOwnUnitSpriteFrameName(1);
	Size sizeOrg = m_unit1->getContentSize();
	if(frameName1.length() == 0){
		m_unit1->setVisible(false);
	}
	else{
		m_unit1->setSpriteFrame(frameName1);
		Size sizeNew = m_unit1->getContentSize();
		m_unit1->setScale(sizeOrg.width / sizeNew.width / 2);
		m_unit1->setAnchorPoint(Vec2(0,1));
		m_unit1->setPositionX(m_unit1->getPositionX()  - sizeOrg.width / 2);
	}
	if(frameName2.length() == 0){
		m_unit2->setVisible(false);
	}
	else{
		m_unit2->setSpriteFrame(frameName2);
		Size sizeNew = m_unit2->getContentSize();
		m_unit2->setScale(sizeOrg.width / sizeNew.width / 2);
		m_unit2->setAnchorPoint(Vec2(0,1));
		m_unit2->setPositionX(m_unit2->getPositionX() - sizeOrg.width);
	}
};

bool PuzzleUILayer::onKCTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)
{
	Point loc2 = pTouch->getLocation();
	Rect scoreRC = m_Scorepanel->getBoundingBox();
	Rect baseRC = m_BasePanel->getBoundingBox();
	
	if(scoreRC.containsPoint(loc2) || baseRC.containsPoint(loc2)){
		pEvent->stopPropagation();
		return true;
	}
	return false;
};
