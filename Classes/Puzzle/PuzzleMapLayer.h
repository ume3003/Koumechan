//
//  PuzzleMapLayer.h
//  koumeChan
//
//  Created by 上野　彰三 on 2014/03/25.
//
//

#ifndef __koumeChan__PuzzleMapLayer__
#define __koumeChan__PuzzleMapLayer__

#include "cocos2d.h"
#include "cocosbuilder/cocosbuilder.h"
#include "PuzzleScene.h"
#include "PuzzleTMXTiledMap.h"
#include "KcLayer.h"

class PuzzleMapLayer : public KcLayer,public cocosbuilder::CCBSelectorResolver,public cocosbuilder::CCBMemberVariableAssigner
{
public:
	
	enum {
		KZO_BACKGROUND = 0,
		KZO_MAP = 1,
		KZO_UNIT,
		KZO_EFFECT
	};
	
	enum {
		KTAG_MAP = 1,
		KTAG_UNITBASE = 100
	};
	
	static PuzzleMapLayer* create();
	bool loadMap();
	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::Ref* pTarget,const char* pSelectorName);
	virtual cocos2d::extension::Control::Handler onResolveCCBCCControlSelector(cocos2d::Ref* pTarget,const char* pSelectorName);
	virtual bool onAssignCCBMemberVariable(cocos2d::Ref* pTarget, const char* pMemberVariableName, Node* pNode);
	
	CC_SYNTHESIZE_RETAIN(cocos2d::Node*, m_mapBase, MapBase);
	CC_SYNTHESIZE_RETAIN(PuzzleTMXTiledMap*, m_TMXMap, TMXMap);
	CC_SYNTHESIZE_RETAIN(cocos2d::Sprite*, m_background, Background);
	
	
protected:
	PuzzleMapLayer();
	virtual ~PuzzleMapLayer();
	
	virtual bool init();
	virtual void onExit();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	
	virtual bool onKCTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
	virtual void onKCTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) {};
	virtual void onKCTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) {};
	virtual void onKCTouchCancelled(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) {};
	
	
};
#endif /* defined(__koumeChan__PuzzleMapLayer__) */
