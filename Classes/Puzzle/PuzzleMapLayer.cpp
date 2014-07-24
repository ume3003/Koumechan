//
//  PuzzleMapLayer.cpp
//  koumeChan
//
//  Created by 上野　彰三 on 2014/03/25.
//
//

#include "PuzzleMapLayer.h"
#include "PuzzleScene.h"
#include "KcLayer.h"

using namespace cocos2d;
using namespace cocosbuilder;
using namespace cocos2d::extension;
using namespace std;

PuzzleMapLayer::PuzzleMapLayer(): m_mapBase(NULL),m_TMXMap(NULL),m_background(NULL)
{
	
};

PuzzleMapLayer::~PuzzleMapLayer()
{
	CC_SAFE_RELEASE(m_mapBase);
	CC_SAFE_RELEASE(m_TMXMap);
	CC_SAFE_RELEASE(m_background);
};

PuzzleMapLayer* PuzzleMapLayer::create()
{
	PuzzleMapLayer* pRet = new PuzzleMapLayer();
	if(pRet && pRet->init()){
		pRet->autorelease();
	}
	else{
		CC_SAFE_RELEASE(pRet);
		pRet = NULL;
	}
	return pRet;
};

bool PuzzleMapLayer::init()
{
	if(KcLayer::init()){
		return true;
	}
	return false;
};
bool PuzzleMapLayer::loadMap()
{
	PuzzleScene* pScene = (PuzzleScene*)getParent();
	if(pScene){
		setTMXMap(pScene->createTiledMap());
		if(getTMXMap()){
			getTMXMap()->loadSpriteBatchNode();
			return true;
		}
	}
	return false;
}

bool PuzzleMapLayer::onAssignCCBMemberVariable(Ref* pTarget, const char* pMemberVariableName, Node* pNode)
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_mapBase", Node*, m_mapBase);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_background", Sprite*, m_background);
	return false;
};

SEL_MenuHandler PuzzleMapLayer::onResolveCCBCCMenuItemSelector(Ref *pTarget, const char *pSelectorName)
{
	return NULL;
};

Control::Handler PuzzleMapLayer::onResolveCCBCCControlSelector(Ref *pTarget, const char *pSelectorName)
{
	return NULL;
};

void PuzzleMapLayer::onExit()
{
	KcLayer::onExit();
};
void PuzzleMapLayer::onEnter()
{
	KcLayer::onEnter();
	if(getTMXMap() && getMapBase() && getBackground()){
		Size mapSize = getTMXMap()->getContentSize();
		Size bgSize = getMapBase()->getContentSize();
		bgSize.height = bgSize.height - KoumeChan::getInstance()->getDiffHeight() *2;
		getMapBase()->setContentSize(bgSize);
		initControl(getMapBase(), false, true);
		getTMXMap()->setScale(min(bgSize.width / mapSize.width,bgSize.height / mapSize.height));
		getTMXMap()->setPosition(Point(bgSize.width / 2,bgSize.height));
		getTMXMap()->setAnchorPoint(Point(0.5,1));
		getMapBase()->addChild(getTMXMap(),KZO_MAP,KTAG_MAP);
	}
	
}
void PuzzleMapLayer::onEnterTransitionDidFinish()
{
	KcLayer::onEnterTransitionDidFinish();
	Size bgSize = Director::getInstance()->getWinSize();
	getBackground()->setTexture("battlebg.png");
	getBackground()->setVisible(true);
	getBackground()->setAnchorPoint(Point(0.5,1));
	getBackground()->setPosition(Point(bgSize.width / 2,bgSize.height));
	getBackground()->setLocalZOrder(KZO_BACKGROUND);
	Size biSize = getBackground()->getContentSize();
	getBackground()->setScale(MAX(bgSize.width / biSize.width,bgSize.height / biSize.height));
//	getBackground()->setContentSize(bgSize);
	PuzzleScene* scene = (PuzzleScene*)getParent();
	if(scene){
		scene->puzzleMainLoop();
	}
	assert(scene);
};

bool PuzzleMapLayer::onKCTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)
{
	return true;
	
};
