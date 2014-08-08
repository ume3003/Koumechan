//
//  PuzzleUnitManager.h
//  koumeChan
//
//  Created by 上野　彰三 on 2014/04/14.
//
//

#ifndef __koumeChan__PuzzleUnitManager__
#define __koumeChan__PuzzleUnitManager__

#include "cocos2d.h"
#include "PuzzleMapUnit.h"
#include "PuzzleTMXTiledMap.h"
#include "PuzzleChainManager.h"

class PuzzleUnitManager : public cocos2d::Ref
{
public:
	static PuzzleUnitManager* getInstance()	;

	enum {
		DELETE_UNIT_POS_START = 65536
	};
	enum MAP_CHAIN_TYPE {
		MAP_THREE = 3,
		MAP_FOUR,
		MAP_FIVE,
		MAP_CROSS
	};
	enum {
		MAP_NUMBER_COUNT = 4
	};
	
	enum ANIME_KIND {
		DEAL_START = 0,
		DEAL_UNIT,
		COM_SCAN,
		SHUFFLE,
		USER_MOVE,
		USER_MOVEBACK,
		DO_CHAIN
	};
	
	void			initPuzzle(cocos2d::Scene* scene,PuzzleTMXTiledMap* map);
	void			initGame();
	void			initTurn();
	void			initPhase();
	

	void			clearUnits();
	PuzzleMapUnit*	getUnit(int idx)			{ return m_units.at(idx);};
	PuzzleMapUnit*	getUnit(cocos2d::Point pos)	{ return m_units.at(xyToIdx(pos));};
	void			setUnit(cocos2d::Point pos,PuzzleMapUnit* pUnit);
	bool			hasUnit(cocos2d::Point pos);
	void			switchUnit(cocos2d::Point pos1,cocos2d::Point pos2);

	bool			isSwitchable(cocos2d::Point srcPos,cocos2d::Point distPos);
	bool			doSwitch(cocos2d::Point srcPos,cocos2d::Point distPos);

	// 空きセルチェック
	bool			hasEmptyCell();
	// 削除フラグをたったユニットを削除
	void			removeDeletedUnit();
	void			unitDeleted(cocos2d::Point pos);
	// パズルユニット管理用
	PuzzleMapUnit*	addMapUnit(cocos2d::Point pos,long unitNo = -1,int rank = 0);
	// ユニット配布
	void			dealUnit();
	// ユニット落下処理
	void			dropUnits();
	// 連鎖チェック
	bool			hasChain();
	int				hasStraightChain(cocos2d::Point pos,bool bTop);
	int				hasCrossChain(cocos2d::Point pos,bool bTop,bool bLeft);
	int				findStraightChain(cocos2d::Point pos ,bool bTop);
	PuzzleChain*	findCrossChain(cocos2d::Point pos,bool bTop,bool bLeft);

	
	// 連鎖
	void			doChain();
	int				evalChain(cocos2d::Point pos1,cocos2d::Point pos2);
	
	// アニメーション実行
	void			unitAction(cocos2d::CallFunc* callback);
	void			unitAnimation();
	
	///////////////////////////////////////////
	// 新処理
	void			executeChain();

	bool			canChain();
	bool			shuffleUnits();
	void			doComScan();
	int				getComChainCandidate();
	
	void			railgunFullPower();
	void			limitBreak(int rank);
	void changeCurrentFrame(int idx);
	
	void createHintTask();
	void stopHintTask();
	
	void setSelectFrame(int idx);
	std::vector<int> makeLimitBreakTarget(int target,int level);
	void showLimitBreakTarget(int idx);
	int comFindEliteUnit();

	bool checkAllElite(PuzzleChain* chain);
	
	int getUnitKOSize()	{ return m_unitKO.size();};
	int getUnitKOCount(long unitNo)		{ return m_unitKO.find(unitNo) == m_unitKO.end() ? 0 : m_unitKO[unitNo];};
	void addUnitKOCount(long unitNo);
protected:
	PuzzleUnitManager();
	virtual ~PuzzleUnitManager();

	int						getNewTag();
	void					resetTag();
	
	void					clearPuzzleChain();
	// アクションアニメーション管理用
	void					clearAllUnitAction();
	
	// パズル処理系
	PuzzleChainManager*		getChainManager(int chain);

	
	// ユニットを供給セルに追加
	bool			supplyUnit(float waitTime);
	void			dealToAny();
	void			dealFromTop();
	void			tryDropUnit(PuzzleMapUnit* pUnit,cocos2d::Point src);

	void addCurActionMgr(ANIME_KIND kind);
	void makeSideUnitAction(int idx,int chainCount,int moveUnitIdx,bool bOwn);
	
	int findEnemyOnLine(int targetForce,bool bTop,int x,int y);
	bool compareForce(int targetForce,int nTargetPos);
	void makeChainThree(PuzzleChain* chain,int chainCount);
	void makeChainFour( PuzzleChain* chain,int chainCount);
	void makeChainFive( PuzzleChain* chain,int chainCount);
	void makeChainCross(PuzzleChain* chain,int chainCount);
	bool checkSideToForce(int forceNo);
	void setChainMarkandDelete(int idx);
	void setChainMark(int idx);
	
	int findOutBoundsTarget(bool bTop,cocos2d::Point basePos);
	int addAttackAction(int nTgt,cocos2d::Point posC,PuzzleChain* chain,int chainCount,cocos2d::Point sidePOS,PuzzleMapUnit* unit);
	PuzzleTMXTiledMap::MAP_POS getSidePOS();
	
	static PuzzleUnitManager* m_instance;
	static const int m_ChainNumbers[];
	cocos2d::Map<int,PuzzleMapUnit*> m_units;
	cocos2d::Map<int,PuzzleChainManager*> m_chainManagers;
	std::list<int> m_candidates;
	

	CC_SYNTHESIZE(int, m_animationCounter, AnimationCounter);
	CC_SYNTHESIZE(int, m_curActionMgr, CurActionMgr);
	CC_SYNTHESIZE_RETAIN(cocos2d::Scene*, m_scene, CurrentScene);
	CC_SYNTHESIZE_RETAIN(PuzzleTMXTiledMap*, m_map, Map);
	CC_SYNTHESIZE(int ,m_deleteUnitPos,DeleteUnitPos);
	CC_SYNTHESIZE(int,m_cuurentTag,CurrentTag);
	CC_SYNTHESIZE(int, m_animationCallbackCount, AnimationCallbackCount);
	CC_SYNTHESIZE(int,m_phaseChainCount,PhaseChainCount);
	CC_SYNTHESIZE(int,m_currentFrameIdx,CurrentFrameIdx);

	CC_SYNTHESIZE_RETAIN(cocos2d::CallFunc*, m_callfunc, CallFunc);
	
	CC_SYNTHESIZE(std::list<int>::iterator ,m_currentHint,CurrentHint);
	CC_SYNTHESIZE(long,m_seed,Seed);
	std::map<long,int> m_unitSummary;
	std::map<long,int> m_unitKO;
	
};

#endif /* defined(__koumeChan__PuzzleUnitManager__) */
