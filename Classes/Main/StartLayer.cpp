//
//  StartLayer.cpp
//  koumeChan
//
//  Created by 上野　彰三 on 2014/03/11.
//
//

#include "StartLayer.h"

#include "KoumeChan.h"
#include "KCDef.h"
#include "JsonKeyString.h"
#include "StartScene.h"

using namespace cocos2d;
using namespace cocosbuilder;
using namespace cocos2d::extension;

StartLayer::StartLayer()
{
	
};

StartLayer::~StartLayer()
{
	
};

bool StartLayer::onAssignCCBMemberVariable(Ref* pTarget, const char* pMemberVariableName, Node* pNode)
{
	return false;
};

SEL_MenuHandler StartLayer::onResolveCCBCCMenuItemSelector(cocos2d::Ref *pTarget, const char *pSelectorName)
{
	return NULL;
};

Control::Handler StartLayer::onResolveCCBCCControlSelector(cocos2d::Ref *pTarget, const char *pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "tappedStart"	, StartLayer::tappedStart);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "tappedEnd"	, StartLayer::tappedEnd);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "tappedGGPS"	, StartLayer::tappedGGPS);
	return NULL;
};

void StartLayer::tappedGGPS(cocos2d::Ref *pSender, Control::EventType pCCControlEvent)
{
	((StartScene*)getParent())->signin();
};

void StartLayer::tappedStart(cocos2d::Ref *pSender, Control::EventType pCCControlEvent)
{
	((StartScene*)getParent())->login();
};


void StartLayer::tappedEnd(cocos2d::Ref *pSender, Control::EventType pCCControlEvent)
{
#ifdef SOUND_ON
	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
#endif
    Director::getInstance()->end();
	
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
	
};


void StartLayer::onEnterTransitionDidFinish()
{
	KoumeChan* chan = KoumeChan::getInstance();
	log("app %s native %s",chan->getSignIn() ? "in" : "out" ,NativeCall::isSignIn() ? "in" : "out");
	if(chan->getSignIn() && !NativeCall::isSignIn()){
		KoumeChan::getInstance()->showConnectInfoDialog(getParent());
		NativeCall::trySilentSignIn();
	}
};

void StartLayer::onEnter()
{
	Layer::onEnter();
	log("---------------------vKoumeChan StartLayer onEnter---------------------");

//	getChildByTag(KTAG_BACKGROUND)->setLocalZOrder(1);
	getChildByTag(KTAG_BACKGROUND)->setPosition(0,KoumeChan::getInstance()->getDiffHeight());
	getChildByTag(KTAG_BACKGROUND)->setAnchorPoint(Point(0,0));

	
	int lFont = KoumeChan::getInstance()->getLargeFont();
	int mFont = KoumeChan::getInstance()->getMidFont();

	Label* label = (Label*)getChildByTag(KTAG_TITLE);
	label->setSystemFontSize(lFont);
	label->setString("Koume Chan!");
	log("---------------------vKoumeChan StartLayer onEnter---------------------");
	
	ControlButton* start = (ControlButton*)getChildByTag(KTAG_START);
	start->setTitleTTFSizeForState(mFont, Control::State::NORMAL);
	start->setTitleForState("Start Game", Control::State::NORMAL);

	ControlButton* exit = (ControlButton*)getChildByTag(KTAG_END);
	exit->setTitleForState("End Game", Control::State::NORMAL);
	exit->setTitleTTFSizeForState(mFont, Control::State::NORMAL);

	log("---------------------vKoumeChan StartLayer onEnter---------------------");
	Point pos = getChildByTag(KTAG_USERNAME)->getPosition();
	getChildByTag(KTAG_USERNAME)->setPosition(Point(pos.x,pos.y - KoumeChan::getInstance()->getDiffHeight()));
	refreshSignInButton();
	log("---------------------vKoumeChan StartLayer onEnter---------------------");
};

void StartLayer::refreshSignInButton()
{
	log("---------------------vKoumeChan StartLayer refreshSignInButton---------------------");
	ControlButton* ggps = (ControlButton*)getChildByTag(KTAG_GOOGLE);
	ggps->setLocalZOrder(1);
	ggps->getTitleLabel()->setLocalZOrder(2);
	Node* node = getChildByTag(KTAG_USERNAME);
	Label* ttf = (Label*)node->getChildByTag(CTAG_TEXT);
	int mFont = KoumeChan::getInstance()->getMidFont();
	ggps->setTitleTTFSizeForState(mFont, Control::State::NORMAL);
	log("---------------------vKoumeChan StartLayer refreshSignInButton---------------------");
	// TODO:グーグルの規定にしたがったアイコンに変える。
	bool isSignIn = NativeCall::isSignIn();
	log("---------------------vKoumeChan StartLayer refreshSignInButton---------------------");
	Label* l = (Label*)ggps->getTitleLabelForState(Control::State::NORMAL);
	Label* lh = (Label*)ggps->getTitleLabelForState(Control::State::HIGH_LIGHTED);
	if(isSignIn){
		l->setString("SignOut Google");
		lh->setString("SignOut Google");
		
//		ggps->setTitleForState("SignOut Google", Control::State::NORMAL);
//		ggps->setTitleForState("SignOut Google", Control::State::HIGH_LIGHTED);
		Value v = KoumeChan::getInstance()->getDisplayName();
		ttf->setString(v.asString().c_str());
		node->setVisible(true);
		log("---%s--%s-%d %d--",ggps->getTitleTTFForState(Control::State::NORMAL).c_str(),
			ggps->getCurrentTitle().c_str(),ggps->getLocalZOrder(),ggps->getTitleLabel()->getLocalZOrder());
	}
	else{
		l->setString("SignIn Google");
		lh->setString("SignIn Google");
//		ggps->setTitleForState("SignIn Google", Control::State::NORMAL);
//		ggps->setTitleForState("SignIn Google", Control::State::HIGH_LIGHTED);
		ttf->setString("");
		node->setVisible(false);
	}
	
};

bool StartLayer::onKCTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)
{
	return false;
};


