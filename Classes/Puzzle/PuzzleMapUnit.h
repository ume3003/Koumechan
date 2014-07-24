//
//  PuzzleMapUnit.h
//  koumeChan
//
//  Created by 上野　彰三 on 2014/04/02.
//
//

#ifndef __koumeChan__PuzzleMapUnit__
#define __koumeChan__PuzzleMapUnit__

#include "cocos2d.h"
#include "KcSprite.h"
#include "PuzzleAction.h"
#include "BaseDamage.h"
#include "PuzzleActionManager.h"
#include "MasterUnit.h"

class PuzzleMapUnit : public KcSprite
{
public:
	
	static PuzzleMapUnit* createWithData(long unitNo,cocos2d::Point pos,int actionOrder,cocos2d::Scene* scene);
	
	enum DRAGMODE {
		KDRAG_NONE = 0,
		KDRAG_DRAGING
	};
	enum POINT_TYPE {
		OWN_HP = 0,
		OWN_PW,
		ENEMY_HP,
		ENEMY_PW
	};
	
	bool isNeighborCell(cocos2d::Point pos);
	int getDistance(PuzzleMapUnit* pDist);
	float getFitScaleToParent(cocos2d::Size parentSize);
	void setFitScaleToParent(float width,float height);
	std::string toJsonString();
	
	void addAction(int actionOrder,PuzzleAction* action);
	bool doAction(int actionOrder,cocos2d::CallFunc* callback);
	std::string actionToString(int actionOrder);
	void clearAction();
	
	virtual void showBackGround();
	virtual void showScore(BaseDamage::BD_TYPE scoreType,int chainCount,cocos2d::Point pos);
	virtual void showEliteScore(BaseDamage::BD_TYPE scoreType,int chainCount,cocos2d::Point pos);
	virtual void showExplosionLine(cocos2d::Point startPos,cocos2d::Point endPos,float duration);
	virtual void showExplosion(cocos2d::Point mapPos);
	virtual void showChainCount(int count,cocos2d::Point pos);
	virtual void showPoint(cocos2d::Point pos,POINT_TYPE type,int nPoint);

	virtual void addAppearAnimation(	int actionOrder);
	virtual void addCreateAnimation(	int actionOrder,float waitTime);
	virtual void addEliteCreateAnimation(int actionOrder,float waitTime,float attackedTime);
	virtual void addMarkAnimation(		int actionOrder,float waitTime);
	virtual void addChainAnimation(		int actionOrder,float waitTime,cocos2d::Point outPos,int chainCount);
	virtual void addWarpAnimation(		int actionOrder,float waitTime,cocos2d::Point warpPos);
	virtual void addSideChainAnimation(	int actionOrder,float waitTime,cocos2d::Point centerPos);
	virtual void addCenterChainAnimation(int actionOrder,float waitTime,cocos2d::Point outPos,int nTgt,int chainCount,float distTime,BaseDamage::BD_TYPE scoreType);
	virtual void addAttackChainAnimation(int actionOrder,float waitTime,cocos2d::Point centerPos,float attackedTime);

	virtual void addEliteAttackAnimation(int actionOrder,float waitTime,int chainCount);
	virtual void addEliteCenterAnimation(int actionOrder,float waitTime,cocos2d::Point outPos,int nTgt,int chainCount,float distTime,BaseDamage::BD_TYPE scoreType);
	virtual void addEnemyCenterAnimation(int actionOrder,float waitTime,cocos2d::Point outPos,int nTgt,int chainCount,float distTime,BaseDamage::BD_TYPE scoreType);
	
	void showHint(bool bShow);
	void startHint(float frame);
	void nextHint();
	void setHint();
	
	Skill* getSkill(int skillLevel);
	MasterUnit* getUnit();
	long getForceNo();
	cocos2d::Size getScaledContentSize();
	
protected:
	PuzzleMapUnit();
	virtual ~PuzzleMapUnit();
	virtual bool initWithData(long unitNo,cocos2d::Point pos,int actionOrder,cocos2d::Scene* scene);
	virtual bool onKCTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
	virtual void onKCTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
	virtual void onKCTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
	virtual void onKCTouchCancelled(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);

	cocos2d::Map<int,PuzzleActionManager*> m_actionMgr;
	
	PuzzleActionManager* getActionManager(int index)	{ return m_actionMgr.at(index);};
	void setActionManager(int index,PuzzleActionManager* mgr) { m_actionMgr.insert(index,mgr);};

	cocos2d::Node* getParentMap();
	
	CC_SYNTHESIZE(DRAGMODE			, m_dragMode	, DragMode);
	CC_SYNTHESIZE(cocos2d::Point	, m_pos			, Pos);
	CC_SYNTHESIZE(long				, m_unitNo		, UnitNo);
	CC_SYNTHESIZE(bool				, m_chainMark	, ChainMark);
	CC_SYNTHESIZE(bool				, m_deleted		, Deleted);
	CC_SYNTHESIZE(bool				, m_movable		, Movable);
	CC_SYNTHESIZE(float				, m_scaleToCell	, ScaleToCell);
	CC_SYNTHESIZE(int				, m_rank		, Rank);
	CC_SYNTHESIZE_RETAIN(cocos2d::Sprite*	, m_frameSprite	, FrameSprite);
	CC_SYNTHESIZE_RETAIN(cocos2d::Sprite*	, m_hintSprite	, HintSprite);
	CC_SYNTHESIZE_RETAIN(cocos2d::Scene*	, m_scene		, Scene);
	
};

#endif /* defined(__koumeChan__PuzzleMapUnit__) */
