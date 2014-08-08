//
//  PuzzleUnitManager.cpp
//  koumeChan
//
//  Created by 上野　彰三 on 2014/04/14.
//
//

#include "PuzzleUnitManager.h"
#include "PuzzleScene.h"
#include "KoumeChan.h"
#include "MagatamaUnit.h"
#include "ShikigamiUnit.h"

using namespace cocos2d;
using namespace std;

const int PuzzleUnitManager::m_ChainNumbers[] =
{
	PuzzleUnitManager::MAP_FIVE,
	PuzzleUnitManager::MAP_FOUR,
	PuzzleUnitManager::MAP_CROSS,
	PuzzleUnitManager::MAP_THREE
};
PuzzleUnitManager* PuzzleUnitManager::m_instance = NULL;

PuzzleUnitManager::PuzzleUnitManager():m_scene(NULL),m_map(NULL),m_callfunc(NULL)
{
}
PuzzleUnitManager::~PuzzleUnitManager()
{
	m_unitSummary.clear();
	m_unitKO.clear();
	clearPuzzleChain();
	m_chainManagers.clear();
	m_candidates.clear();
	CC_SAFE_RELEASE(m_callfunc);
	CC_SAFE_RELEASE(m_scene);
	CC_SAFE_RELEASE(m_map);
	stopHintTask();
	clearUnits();
}
PuzzleUnitManager* PuzzleUnitManager::getInstance()
{
	if(!m_instance){
		m_instance = new PuzzleUnitManager();
	}
	return m_instance;
}
void PuzzleUnitManager::initPuzzle(cocos2d::Scene *scene, PuzzleTMXTiledMap *map)
{
	setCurrentScene(scene);
	setMap(map);
	setCurrentFrameIdx(-1);
	initGame();
};
void PuzzleUnitManager::addCurActionMgr(ANIME_KIND kind)
{
//	log("====================action %d %d → %d===============",kind,getCurActionMgr(),getCurActionMgr() + 1);
	setCurActionMgr(getCurActionMgr() + 1);
};

void PuzzleUnitManager::initGame()
{
	clearUnits();
	PuzzleScene* pScene = (PuzzleScene*)getCurrentScene();
	if(pScene){
		pScene->setPlayer1HP(pScene->getHitpoit(PuzzleScene::PHASE_PLAYER_1));
		pScene->setPlayer2HP(pScene->getHitpoit(PuzzleScene::PHASE_PLAYER_2));
		pScene->setPlayer1Power(STARTPOWER);
		pScene->setPlayer2Power(STARTPOWER);
		pScene->updateScore();
	}
	m_unitSummary.clear();
	m_unitKO.clear();
	
	resetTag();
	setDeleteUnitPos(DELETE_UNIT_POS_START);

	initTurn();
	initPhase();
};

void PuzzleUnitManager::initTurn()
{
	log("++++++++ unit info ++++++++++++++++");
	map<long,int>::iterator it = m_unitSummary.begin();
	while(it != m_unitSummary.end()){
		long key = (*it).first;
		int val = (*it).second;
		log("+++++++++key %ld val %d",key,val);
		++it;
	}
	log("++++++++ unit info ++++++++++++++++");
};

void PuzzleUnitManager::initPhase()
{
	removeDeletedUnit();
	clearAllUnitAction();				// アクション情報のクリア
	clearPuzzleChain();					// チェイン情報のクリア
	setCurActionMgr(0);
	setAnimationCallbackCount(0);
	setAnimationCounter(0);
	setPhaseChainCount(0);
	m_candidates.clear();
//	setCurrentHint(m_candidates.end());
};

/////////////////////////////////////////////////////////////////////////////
//	新処理
////////////////////////////////////////////////////////////////////////////
//	チェインの実行。チェインがなくなるまで行われる
void PuzzleUnitManager::executeChain()
{
	clearPuzzleChain();
	while(hasChain()){
		doChain();
		if(hasEmptyCell()){
			dropUnits();
			dealFromTop();
			clearPuzzleChain();
			addCurActionMgr(DEAL_UNIT);
		}
	}
}
/////////////////////////////////////////////////////////////////
//	ユニット配布
/////////////////////////////////////////////////////////////////
void PuzzleUnitManager::dealUnit()
{
	if(true){
		dealFromTop();
	}
	else{
		dealToAny();
	}
	addCurActionMgr(DEAL_START);
	executeChain();
}
///////////////////////////////////////////////////////////////////////////////
//	ユニット操作
///////////////////////////////////////////////////////////////////////////////
//	すべてのユニットを完全消去
void PuzzleUnitManager::clearUnits()
{
	Map<int,PuzzleMapUnit*>::iterator it = m_units.begin();
	while(it != m_units.end()){
		PuzzleMapUnit* pUnit = (PuzzleMapUnit*)(*it).second;
		if(pUnit){
			pUnit->removeFromParentAndCleanup(true);
		}
		++it;
	}
	m_units.clear();
}
//	ユニットを生成し、マップのチャイルドへ
PuzzleMapUnit* PuzzleUnitManager::addMapUnit(cocos2d::Point pos,long unitNo,int rank)
{
	PuzzleScene* pScene = (PuzzleScene*)getCurrentScene();
	PuzzleTMXTiledMap* map = getMap();
	PuzzleMapUnit* mapUnit = NULL;
	int tag = -1;
	if(map && pScene){
		log("======================================");
		long uNo = pScene->getSeed();
		log("++++++++++ pos %2.0f/%2.0f ++++++++++++",pos.x,pos.y);
		log("++++++++++++++ uNo %ld +++++++++++++++",uNo);
		log("======================================");
//		unitNo = unitNo >= 0 ? unitNo : map->findUnitNoFromRate((rand() + 1) % map->getAppearanceRate());
		unitNo = unitNo >= 0 ? unitNo : uNo;
		if(unitNo >= 0){
			if(rank > 0){
				long sNo = pScene->getShikigamiNo(getCurrentTag());
				mapUnit = ShikigamiUnit::createWithData(unitNo,pos,getCurActionMgr(),getCurrentScene(),rank,sNo);
			}
			else{
				mapUnit = MagatamaUnit::createWithData(unitNo,pos,getCurActionMgr(),getCurrentScene());
				mapUnit->doWaitingAnimation();
			}
			if(mapUnit){
				mapUnit->setFitScaleToParent(map->getCelWidth(),map->getCelHeight());
				mapUnit->setPosition(map->getCenterPos(pos));
				tag = getNewTag();
				////////////////////
				//if(mapUnit->getForceNo() != 0L && tag % 3 == 0){
				//	mapUnit->setRank(1);
				//}
				map->addMapChild(unitNo, mapUnit, PuzzleScene::LZ_UNIT, tag);
				//////////////////
				setUnit(pos,mapUnit);
				if(m_unitSummary.find(unitNo) == m_unitSummary.end()){
					m_unitSummary[unitNo] = 0;
				}
				m_unitSummary[unitNo] = m_unitSummary[unitNo] + 1;
				
			}
			else{
				log("mapunit is null");
			}
		}
		else{
			log("unit no is under 0");
		}
	}
	else{
		log("map is null");
	}
	CCASSERT(tag >= 0, "create unit fail");
	return mapUnit;
};
//	ユニットがその座標にあるかチェック
bool PuzzleUnitManager::hasUnit(Point pos)
{
	PuzzleMapUnit* pUnit = getUnit(pos);
	return pUnit != NULL;
};
//	ユニットをその座標に設置。ただし、前にユニットがあるとだめ。入れ替えはswitchよんで
void PuzzleUnitManager::setUnit(Point pos,PuzzleMapUnit* unit)
{
	int idx = xyToIdx(pos);
	PuzzleMapUnit* pre = m_units.at(idx);
	CCASSERT(!pre, StringUtils::format("setUnit pre Unit exist %d",idx).c_str());
	if(pre){
		m_units.erase(idx);
		pre->removeFromParentAndCleanup(true);
	}
	m_units.insert(idx, unit);
}
/////////////////////////////////////////////
//	２つのユニットの位置を交換。両方ないとダメよ
void PuzzleUnitManager::switchUnit(cocos2d::Point pos1, cocos2d::Point pos2)
{
	PuzzleMapUnit* p1 = getUnit(pos1);
	PuzzleMapUnit* p2 = getUnit(pos2);
	int i1 = xyToIdx(pos1);
	int i2 = xyToIdx(pos2);
	if(p1 && p2){
		m_units.erase(	i1);
		m_units.erase(	i2);
		m_units.insert(	i1,p2);
		m_units.insert(	i2,p1);
	}
}
void PuzzleUnitManager::addUnitKOCount(long unitNo)
{
	if(m_unitKO.find(unitNo) == m_unitKO.end()){
		m_unitKO[unitNo] = 0;
	}
	m_unitKO[unitNo] = m_unitKO[unitNo] + 1;
}
///////////////////////////////////////////////////////////////
//	削除ポジションに移動
/////////////////////////////////////////////////////////////
void PuzzleUnitManager::unitDeleted(cocos2d::Point pos)
{
	PuzzleMapUnit* pUnit = getUnit(pos);
	m_units.erase(xyToIdx(pos));
	m_units.insert(getDeleteUnitPos(), pUnit);
	setDeleteUnitPos(getDeleteUnitPos() + 1);
};
/////////////////////////////////////////////////////////////////
//	削除ポジションに移動したものをすべて削除
////////////////////////////////////////////////////////////////
void PuzzleUnitManager::removeDeletedUnit()
{
//	log("============removeDelelteUnit================");
	for(int i = DELETE_UNIT_POS_START; i < getDeleteUnitPos();i++){
		PuzzleMapUnit* pre = m_units.at(i);
		if(pre){
			m_units.erase(i);
			pre->removeFromParentAndCleanup(true);
		}
	}
	setDeleteUnitPos(DELETE_UNIT_POS_START);
//	log("============removeDelelteUnit END================");
}

///////////////////////////////////////////////////////////////////////////////
//	空きチェック
////////////////////////////////////////////////////////////////////////////
bool PuzzleUnitManager::hasEmptyCell()
{
	PuzzleTMXTiledMap* map = getMap();
	if(map){
		// TODO : 非同期で消去されるユニットはここで再度確認して消す
		for(int y = 0 ;y < map->getMapHeight();y++){
			for( int x = 0 ; x < map->getMapWidth();x++){
				Point pos = Point(x,y);
				if(map->isMovableCell(pos)){
					if(!hasUnit(pos)){
						//log("==========find empty cell %2.0f/%2.0f",pos.x,pos.y);
						return true;
					}
				}
			}
		}
	}
	return false;
}
////////////////////////////////////////////////////////////////////
//	チェイン情報をすべてクリア。チェインマークもはずす
///////////////////////////////////////////////////////////////////
void PuzzleUnitManager::clearPuzzleChain()
{
	Map<int,PuzzleChainManager*>::iterator it = m_chainManagers.begin();
	while(it != m_chainManagers.end()){
		PuzzleChainManager* mgr = (PuzzleChainManager*)(*it).second;
		if(mgr){
			mgr->clearChains();
		}
		++it;
	}
	Map<int,PuzzleMapUnit*>::iterator it2 = m_units.begin();
	while(it2 != m_units.end()){
		PuzzleMapUnit* pUnit = (PuzzleMapUnit*)(*it2).second;
		if(pUnit && pUnit->getChainMark()){
			pUnit->setChainMark(false);
		}
		++it2;
	}
}



// 入れ替えるユニットがあるか。
bool PuzzleUnitManager::isSwitchable(cocos2d::Point srcPos, cocos2d::Point distPos)
{
	PuzzleMapUnit* pSrc = getUnit(srcPos);
	PuzzleMapUnit* pDist = getUnit(distPos);
	if(pSrc && pDist && pSrc->getMovable() && pDist->getMovable()){
		return true;
	}
	return false;
}
//////////////////////////////////////////////////////////
//	供給せるにユニットを追加。何巡目なのかを引数で渡す
//////////////////////////////////////////////////////////
bool PuzzleUnitManager::supplyUnit(float waitTime)
{
	PuzzleTMXTiledMap* map = getMap();
	bool isSupplied = false;
	if(map){
		long cnt = map->getSupplyCellCount();
		for(int i = 0;i < cnt;i++){
			Point pos = idxToPos(map->getSupplyCell(i));
			Point underPos = Point(pos.x,pos.y - 1);
			if(map->isMovableCell(underPos)){
				if(!hasUnit(underPos) && !hasUnit(pos)){
					PuzzleMapUnit* pUnit = addMapUnit(pos);
					if(pUnit){
						isSupplied = true;
						pUnit->addCreateAnimation(getCurActionMgr(), waitTime);
					}
				}
			}
		}
	}
	return isSupplied;
}
/////////////////////////////////////////////////////////////
//	全画面の空きセルにユニットを追加する
/////////////////////////////////////////////////////////////
void PuzzleUnitManager::dealToAny()
{
	PuzzleTMXTiledMap* map = getMap();
	if(map){
		for(int x = 0;x < map->getMapWidth();x++){
			for(int y = 0 ; y < map->getMapHeight();y++){
				Point pos = Point(x,y);
				if(map->isMovableCell(pos) && getUnit(pos) == NULL){
					PuzzleMapUnit* pUnit = addMapUnit(pos);
					if(pUnit){
						pUnit->addAppearAnimation(getCurActionMgr());
					}
				}
			}
		}
	}
}
///////////////////////////////////////////////////////////
//	供給セルにユニットを追加する。空きセルがなくなるまで行われる
///////////////////////////////////////////////////////////
void PuzzleUnitManager::dealFromTop()
{
	int wait = 0;
	while(hasEmptyCell()){
		float waitTime = wait * 0.3f;
		if(supplyUnit(waitTime)){
			wait++;
		}
		dropUnits();
	}
}

///////////////////////////////////////////////////////////////////////////////
//	ユニット落下処理
////////////////////////////////////////////////////////////////////////////
void PuzzleUnitManager::dropUnits()
{
	PuzzleTMXTiledMap* map = getMap();
	if(map){
		for(int y = map->getMapHeight() -1;y >= 0;y--){
			for(int x = 0 ; x < map->getMapWidth();x++){
				Point pos = Point(x,y);
				PuzzleMapUnit* pUnit = getUnit(pos);
				if(pUnit){
					tryDropUnit(pUnit,pos);
				}
			}
		}
	}
	
}
void PuzzleUnitManager::tryDropUnit(PuzzleMapUnit* pUnit,cocos2d::Point src)
{
	PuzzleTMXTiledMap* map = getMap();
	if(pUnit && map){
		Point dist = src;
		Point distU = Point(src.x		,src.y - 1);
		Point distL = Point(src.x - 1	,src.y - 1);
		Point srcL  = Point(src.x - 1	,src.y);
		Point distR = Point(src.x + 1	,src.y - 1);
		Point srcR  = Point(src.x + 1	,src.y);
		PuzzleAction::PZ_ACTION act = PuzzleAction::PZ_DOWN;
		if(!hasUnit(distU) && map->isMovableCell(distU)){
			dist = distU;
		}
		else{
			if(!map->isMovableCell(srcL) && !hasUnit(distL) && map->isMovableCell(distL)){
				dist = distL;
				act = PuzzleAction::PZ_DOWNLEFT;
			}
			else if(!map->isMovableCell(srcR) && !hasUnit(distR) && map->isMovableCell(distR)){
				dist = distR;
				act = PuzzleAction::PZ_DOWNRIGHT;
			}
		}
		if(src.y != dist.y){
			m_units.insert(xyToIdx(dist), pUnit);
			m_units.erase(xyToIdx(src));
			pUnit->addAction(getCurActionMgr(),PuzzleAction::create(act, dist,0.3f));
		}
	}
};
///////////////////////////////////////////////////////////////////////////////
//	連鎖チェック
////////////////////////////////////////////////////////////////////////////
bool PuzzleUnitManager::hasChain()
{
	bool bChain = false;
	PuzzleTMXTiledMap* map = getMap();
	if(map){
		int ny = map->getMapHeight();
		int nx = map->getMapWidth();
		for(int y = 0 ; y < ny ; y++){
			for(int x = 0 ; x < nx ; x++){
				Point pos = Point(x,y);
				if(hasUnit(pos)){
					int topCnt = hasStraightChain(pos,true);
					int leftCnt = hasStraightChain(pos,false);
					int crossCnt = hasCrossChain(pos,topCnt > 2,leftCnt > 2);
					if(MAX(MAX(topCnt, leftCnt),crossCnt) >= 3){
						bChain = true;
					}
				}
			}
		}
	}
	return bChain;
}
/////////////////////////////////////////////////////////
//	クロスチェインを走破し、登録する
////////////////////////////////////////////////////////
int PuzzleUnitManager::hasCrossChain(cocos2d::Point pos, bool bTop, bool bLeft)
{
	PuzzleChain* chain = findCrossChain(pos, bTop, bLeft);
	if(chain != NULL){
		PuzzleChainManager* manager = getChainManager(MAP_CROSS);
		if(manager){
			manager->addChain(chain);
		}
		return 6;
	}
	return 0;
}
////////////////////////////////////////////////////////
//	クロスチェイン判定
///////////////////////////////////////////////////////
PuzzleChain* PuzzleUnitManager::findCrossChain(cocos2d::Point pos,bool bTop,bool bLeft)
{
	PuzzleChain* chain = PuzzleChain::create(0);
	if(!bTop && !bLeft){
		return NULL;
	}
	if(bTop){
		for(int y = 0; y < 3;y++){
			chain->addChain(xyToIdx(Point(pos.x,pos.y + y)));
		}
		if(bLeft){
			chain->addChain(xyToIdx(Point(pos.x + 1,pos.y)));
			chain->addChain(xyToIdx(Point(pos.x + 2,pos.y)));
			chain->setType(KoumeChan::CHAIN_T_1R);
		}
		else if(2 < findStraightChain(Point(pos.x			,pos.y + 1), false)){
			chain->addChain(xyToIdx(Point(pos.x + 1		,pos.y + 1)));
			chain->addChain(xyToIdx(Point(pos.x + 2		,pos.y + 1)));
			chain->setType(KoumeChan::CHAIN_T_2R);
		}
		else if(2 < findStraightChain(Point(pos.x - 2		,pos.y + 1), false)){
			chain->addChain(xyToIdx(Point(pos.x - 1		,pos.y + 1)));
			chain->addChain(xyToIdx(Point(pos.x - 2		,pos.y + 1)));
			chain->setType(KoumeChan::CHAIN_T_2L);
		}
		else if(2 < findStraightChain(Point(pos.x			,pos.y + 2), false)){
			chain->addChain(xyToIdx(Point(pos.x + 1		,pos.y + 2)));
			chain->addChain(xyToIdx(Point(pos.x + 2		,pos.y + 2)));
			chain->setType(KoumeChan::CHAIN_T_3R);
		}
		else if(2 < findStraightChain(Point(pos.x - 2		,pos.y + 2), false)){
			chain->addChain(xyToIdx(Point(pos.x - 1		,pos.y + 2)));
			chain->addChain(xyToIdx(Point(pos.x - 2		,pos.y + 2)));
			chain->setType(KoumeChan::CHAIN_T_3L);
		}
		else if(2 < findStraightChain(Point(pos.x - 1		,pos.y + 2), false)){
			chain->addChain(xyToIdx(Point(pos.x - 1	,pos.y + 2)));
			chain->addChain(xyToIdx(Point(pos.x + 1	,pos.y + 2)));
			chain->setType(KoumeChan::CHAIN_T_3C);
		}
	}
	else if(bLeft){
		for(int x = 0; x < 3;x++){
			chain->addChain(xyToIdx(Point(pos.x + x,pos.y)));
		}
		if(2 < findStraightChain(Point(pos.x + 1,pos.y), true)){
			chain->addChain(xyToIdx(Point(pos.x + 1	,pos.y + 1)));
			chain->addChain(xyToIdx(Point(pos.x + 1	,pos.y + 2)));
			chain->setType(KoumeChan::CHAIN_Y_2T);
		}
		else if(2 < findStraightChain(Point(pos.x + 2,pos.y), true)){
			chain->addChain(xyToIdx(Point(pos.x + 2	,pos.y + 1)));
			chain->addChain(xyToIdx(Point(pos.x + 2	,pos.y + 2)));
			chain->setType(KoumeChan::CHAIN_Y_3T);
		}
	}
	if(chain->getType() != KoumeChan::NO_CHAIN ){
		return chain;
	}
	return NULL;
}
///////////////////////////////////////////////////////////////////////
//	直線チェインを走破し、登録する
//////////////////////////////////////////////////////////////////////
int PuzzleUnitManager::hasStraightChain(cocos2d::Point pos, bool bTop)
{
	int count = findStraightChain(pos,bTop);
	PuzzleTMXTiledMap* map = getMap();
	if(map && count > 2){
		for(int c = 3; c <= count ; c++){
			PuzzleChainManager* manager = getChainManager(c);
			PuzzleChain* chain = PuzzleChain::create(c);
			chain->setTop(bTop);
			for(int i = 0;i < c;i++){
				Point nPos = map->getNeighborPoint(pos, bTop, i);
				chain->addChain(xyToIdx(nPos));
			}
			if(manager){
				manager->addChain(chain);
			}
		}
		return count;
	}
	return 0;
}
///////////////////////////////////////////////////////////////
//	直線チェイン判定
///////////////////////////////////////////////////////////////
int PuzzleUnitManager::findStraightChain(Point pos,bool bTop)
{
	int count = 1;
	PuzzleTMXTiledMap* map = getMap();
	PuzzleMapUnit* pUnit = getUnit(pos);
	if(pUnit && map){
		for(int i = 1; i < 5; i++){
			PuzzleMapUnit* pNeighor = getUnit(map->getNeighborPoint(pos, bTop, i));
			if(pNeighor && pNeighor->getUnitNo() == pUnit->getUnitNo()){
				count++;
			}
			else{
				break;
			}
		}
	}
	return count;
}
/////////////////////////////////////////////////////////////
//	チェイン情報のクリア
/////////////////////////////////////////////////////////////
PuzzleChainManager* PuzzleUnitManager::getChainManager(int chain)
{
	PuzzleChainManager* manager = m_chainManagers.at(chain);
	if(!manager){
		manager = PuzzleChainManager::create();
		m_chainManagers.insert(chain, manager);
	}
	return manager;
}
//////////////////////////////////////////////////////////////////////////////////////////
//		ユニットアクションのクリア
//////////////////////////////////////////////////////////////////////////////////////////
void PuzzleUnitManager::clearAllUnitAction()
{
	Map<int,PuzzleMapUnit*>::iterator it = m_units.begin();
	while(it != m_units.end()){
		PuzzleMapUnit* pUnit = (PuzzleMapUnit*)(*it).second;
		if(pUnit){
			pUnit->clearAction();
		}
		++it;
	}
	setCurActionMgr(0);
}
////////////////////////////////////////////////////////////////////////////////////
//	指定ユニットを入れ替えた時の連鎖評価点を返す
/////////////////////////////////////////////////////////////////////////////////
int PuzzleUnitManager::evalChain(Point pos1,Point pos2)
{
	if(getUnit(pos1) && getUnit(pos2)){
		switchUnit(pos1,pos2);
		int sx = MIN(pos1.x,pos2.x) - 2;
		int sy = MIN(pos1.y,pos2.y) - 2;
		int dx = MAX(pos2.x,pos1.x) + 2;
		int dy = MAX(pos2.y,pos1.y) + 2;
		int ntarget = 0;
		for(int y = sy;y <= dy ;y++){
			for(int x = sx; x <= dx ; x++){
				Point pos = Point(x,y);
				int nTop = findStraightChain(pos, true);
				int nLeft = findStraightChain(pos, false);
				if(nTop > 3 || nLeft > 3){
					ntarget = MAX(ntarget,MAX(nTop,nLeft) - 2);
				}
				else if (nTop == 3 || nLeft == 3){
					PuzzleChain* chain = findCrossChain(pos, nTop == 3, nLeft == 3);
					ntarget = MAX(ntarget,chain ? 2 : 1);
				}
			}
		}
		switchUnit(pos1, pos2);
		return ntarget;
	}
	return 0;
}

///////////////////////////////////////////////////////////////////////////
//	チェインできるか？
///////////////////////////////////////////////////////////////////////////
bool PuzzleUnitManager::canChain()
{
	m_candidates.clear();
	PuzzleTMXTiledMap* map = getMap();
	if(map){
		for(int x = 0;x < map->getMapWidth();x++){
			for(int y = 0 ; y < map->getMapHeight();y++){
				Point pos = Point(x,y);
				Point posU = Point(x,y+1);
				Point posL = Point(x + 1,y);
				int nV = evalChain(pos,posU) * 2;
				int nH = evalChain(pos,posL) * 2;
				if(nV > 0 || nH > 0){
					PuzzleMapUnit* pUnit = getUnit(pos);
					if(pUnit){
						bool bOwn = checkSideToForce(pUnit->getForceNo());
						if(nV > 0){
							int candidate = idxToCandidate(xyToIdx(pos), bOwn ? nV +1 : nV);
							m_candidates.push_back(vhCandidate(candidate,true));
						}
						if(nH > 0){
							int candidate = idxToCandidate(xyToIdx(pos), bOwn ? nH + 1 : nH);
							m_candidates.push_back(vhCandidate(candidate,false));
							
						}
					}
				}
			}
		}
		m_candidates.sort(greater<int>());
	}
	return m_candidates.size() > 0;
}
int PuzzleUnitManager::getComChainCandidate()
{
	
	if(m_candidates.size() > 0){
		std::list<int>::iterator it = m_candidates.begin();
		int cnt = 0;
		int rank = -1;
		while(it != m_candidates.end()){
			int candidate = (int)(*it);
			int r = candidateRank(candidateInt(candidate));
			if(rank < 0 || rank == r){
				rank = r;
				cnt++;
			}
			++it;
		}
		if(cnt != 0){
			int c = rand() % cnt;
			
			cnt = 0;
			it = m_candidates.begin();
			while(it != m_candidates.end()){
				if(c == cnt){
					return (int)(*it);
				}
				cnt++;
				++it;
			}
		}
	}
	return 0;
}
void PuzzleUnitManager::doComScan()
{
	int cnt = 0;
	float diff = m_candidates.size() < 10 ? 0.2f : 0.1f;
	std::list<int>::iterator it = m_candidates.begin();
	while(it != m_candidates.end()){
		int candidate = (int)(*it);
//		bool b = candidateVH(candidate);
		int c = candidateInt(candidate);
		int idx = candidateIdx(c);
//		int rank = candidateRank(c);
		//log("%d %d %d %s",candidate,rank,idx,b? "V" : "H");
		PuzzleMapUnit* pUnit = getUnit(idxToPos(idx));
		if(pUnit && cnt < 20){
			pUnit->addMarkAnimation(getCurActionMgr(),cnt * diff);
		}
		cnt++;
		++it;
	}
	if(cnt > 0){
		addCurActionMgr(COM_SCAN);
	}
}
///////////////////////////////////////////////////////////////////////////
//	シャッフルする
///////////////////////////////////////////////////////////////////////////
bool PuzzleUnitManager::shuffleUnits()
{
	bool canShuffle = false;
	cocos2d::Vector<PuzzleMapUnit*> unitBuffer;	// ユニットバッファ
	map<int,int> countBuffer;					// ユニットの個数をかぞえるバッファ
	vector<int> posBuffer;						// ポジションバッファ
	PuzzleTMXTiledMap* pMap = getMap();
	if(pMap){
		for(int x = 0 ; x < pMap->getMapWidth();x++){
			for(int y = 0 ; y < pMap->getMapHeight();y++){
				int pos = xyToIdx(x, y);
				PuzzleMapUnit* pUnit = getUnit(pos);
				if(pUnit){
					long unitNo = pUnit->getUnitNo();
					if(countBuffer.find(unitNo) == countBuffer.end()){
						countBuffer.insert(map<int,int>::value_type(unitNo,0));
					}
					countBuffer[unitNo] = countBuffer[unitNo] + 1;
					unitBuffer.pushBack(pUnit);
					posBuffer.push_back(pos);
				}
			}
		}
		
		// 最低数のチェック
		int baseCount = 0;
		map<int,int>::iterator cntIt = countBuffer.begin();
		while(cntIt != countBuffer.end()){
			int curCnt = (int)(*cntIt).first;
			baseCount = MAX(baseCount,curCnt);
			++cntIt;
		}
		if(baseCount > 2){
			canShuffle = true;
			for(int i = 0; i < unitBuffer.size();i++){
				if(i % 3 == 0){
					if(i + 3 < unitBuffer.size()){
						unitBuffer.swap(i,i+3);
					}
				}
			}
			m_units.clear();												// 手持ちを消去
			for(int i = 0 ; i < unitBuffer.size();i++){						// ポジションとユニットの組み合わせを元バッファにいれていく
				int nPos = posBuffer.at(i);
				PuzzleMapUnit* pUnit = unitBuffer.at(i);
				if(pUnit){
					m_units.insert(nPos, pUnit);
					Point newPos = idxToPos(nPos);
					Point orgPos = pUnit->getPos();
					log("%d %d %2.0f/%2.0f %2.0f/%2.0f",pUnit->getTag(),getCurActionMgr(),orgPos.x,orgPos.y,newPos.x,newPos.y);
					pUnit->addWarpAnimation(getCurActionMgr(), i % 5,newPos);
				}
			}
			if(unitBuffer.size() > 0){
				addCurActionMgr(SHUFFLE);
			}
		}
	}
	// 後始末
	unitBuffer.clear();
	posBuffer.clear();
	countBuffer.clear();

	return canShuffle;
}
///////////////////////////////////////////////////////////////////////////
//	ユニット用タグの管理
///////////////////////////////////////////////////////////////////////////
int PuzzleUnitManager::getNewTag()
{
	setCurrentTag(getCurrentTag() + 1);
	return getCurrentTag();
};
void PuzzleUnitManager::resetTag()
{
	setCurrentTag(PuzzleScene::LTAG_UNITBASE);
};

////////////////////////////////////////////////////////////////////////////
///	ユーザー入力
////////////////////////////////////////////////////////////////////////////
bool PuzzleUnitManager::doSwitch(cocos2d::Point srcPos, cocos2d::Point distPos)
{
	PuzzleMapUnit* pSrc = getUnit(srcPos);
	PuzzleMapUnit* pDist = getUnit(distPos);
	bool bReturn = false;
	if(pSrc && pDist){
		bReturn = evalChain(srcPos, distPos) > 0;
		//log("switch %d",getCurActionMgr());
		switchUnit(srcPos,distPos);
		pDist->addAction(getCurActionMgr(), PuzzleAction::create(PuzzleAction::PZ_MOVE,srcPos,0.2f));
		pSrc->addAction(getCurActionMgr(),  PuzzleAction::create(PuzzleAction::PZ_MOVE,distPos,0.2f));
		addCurActionMgr(USER_MOVE);
		
		if(!bReturn){
			switchUnit(srcPos, distPos);
			pDist->addAction(getCurActionMgr(), PuzzleAction::create(PuzzleAction::PZ_MOVE,distPos,0.2f));
			pSrc->addAction(getCurActionMgr(),  PuzzleAction::create(PuzzleAction::PZ_MOVE,srcPos,0.2f));
			addCurActionMgr(USER_MOVEBACK);
		}
	}
	return bReturn;
};

///////////////////////////////////////////////////////////////////////////////
//	チェイン処理
////////////////////////////////////////////////////////////////////////////
void PuzzleUnitManager::doChain()
{
//	int actCount = getCurActionMgr() ;
	int chainCount = 0;
	log("++++++++++++++++++++++++++++ chain exec %d ++++++++++++++++++++++++++++++++++++",getCurActionMgr());
	PuzzleTMXTiledMap* map = getMap();
	PuzzleScene* pScene = (PuzzleScene*)getCurrentScene();
	if(map && pScene){
		for(int n = 0; n < MAP_NUMBER_COUNT;n++){
			PuzzleChainManager* mgr = m_chainManagers.at(m_ChainNumbers[n]);
			log("=================chain %d start=============",m_ChainNumbers[n]);
			if(mgr){
				for(int i = 0 ; i < mgr->getChainSize();i++){
					PuzzleChain* chain = mgr->getChain(i);
					log("execute chain %d",i);
					if(chain){
						bool bChain = true;
						for(int j = 0;j < chain->getChainCount();j++){
							PuzzleMapUnit* pUnit = getUnit(idxToPos(chain->getChain(j)));
							if(!pUnit || pUnit->getChainMark()){
								bChain = false;
							}
						}
						if(bChain){
							if(pScene->getState() == PuzzleScene::PUZZLE_INGAME){
								setPhaseChainCount(getPhaseChainCount() + 1);
							}
							// この段階で、チェインの効果を作成 3 4 5 T など。
							//log("do chain %s",chain->toJsonString().c_str());
							switch(chain->getType()){
								case KoumeChan::CHAIN_THREE:
									makeChainThree(chain,chainCount);
									break;
								case KoumeChan::CHAIN_FOUR:
									makeChainFour(chain,chainCount);
									break;
								case KoumeChan::CHAIN_FIVE:
									makeChainFive(chain,chainCount);
									break;
								default:
									makeChainCross(chain,chainCount);
									break;
							}
							chainCount++;
						}
					}
				}
			}
		}
	}
	if(chainCount > 0){
		addCurActionMgr(DO_CHAIN);
	}
	//log("++++++++++++++++++++++++++++ chain exec %d end %d ++++++++++++++++++++++++++++++++++++",getCurActionMgr(),chainCount);
}
///////////////////////////////////////////////////////////////////
//	ユニットのアニメーション実行
////////////////////////////////////////////////////////
void PuzzleUnitManager::unitAnimation()
{
//	time_t now = time(NULL);
	int cnt = MAX(0,getAnimationCallbackCount() - 1);
	if(cnt == 0){
		setAnimationCallbackCount(0);
//		log("========== unit animation start %d %d %ld==============",getCurActionMgr(),getAnimationCounter(),now);
		CallFunc* callback = CallFunc::create(CC_CALLBACK_0(PuzzleUnitManager::unitAnimation, this));
		if(getAnimationCounter() < getCurActionMgr()){
			Map<int,PuzzleMapUnit*>::iterator it = m_units.begin();
			while(it != m_units.end()){
				PuzzleMapUnit* pUnit = (PuzzleMapUnit*)(*it).second;
				if(pUnit){
					if(pUnit->doAction(getAnimationCounter(),callback)){
						setAnimationCallbackCount(getAnimationCallbackCount() + 1);
					}
				}
				++it;
			}
			//log("===================== unit animation end   =========================");
			setAnimationCounter(getAnimationCounter() + 1);
		}
		else{
			//log("*********************finished animation ");
			if(getCallFunc()){
				getCallFunc()->execute();
			}
			//log("======== animation callback is %d at %d",getAnimationCallbackCount(),getAnimationCounter());
		}
	}
	else{
		setAnimationCallbackCount(cnt);
	}
}
void PuzzleUnitManager::unitAction(cocos2d::CallFunc *callback)
{
	setCallFunc(callback);
	setAnimationCounter(0);
	unitAnimation();
}


int PuzzleUnitManager::comFindEliteUnit()
{
	PuzzleTMXTiledMap* map = getMap();
	for(int x = 0; x < map->getMapWidth();x++){
		for(int y = 0;y < map->getMapHeight();y++){
			int idx = xyToIdx(x, y);
			PuzzleMapUnit* pTarget = getUnit(idx);
			if(pTarget && pTarget->getRank() > 0){
				if(checkSideToForce(pTarget->getForceNo())){
					return idx;
				}
			}
		}
	}
	return -1;
}


void PuzzleUnitManager::showLimitBreakTarget(int target)
{
	PuzzleTMXTiledMap* map = getMap();
	PuzzleScene* scene = (PuzzleScene*)getCurrentScene();
	int level = scene->getLBLevel(scene->getCurrentPlayerPower());
	if(level > 0){
		vector<int> vec = makeLimitBreakTarget(target,level);
		map->clearShadowCell();
		for(int i = 0;i < vec.size();i++){
			int idx = vec.at(i);
			map->addShadowCell(idx);
		}
	}
	
}

vector<int> PuzzleUnitManager::makeLimitBreakTarget(int target,int level)
{
	PuzzleTMXTiledMap* map = getMap();
	PuzzleMapUnit* pTarget = getUnit(target);
	Skill* skill = pTarget->getSkill(level);
	vector<int> vecTarget;
	
	if(pTarget && map && skill){
		DIRECT direct = map->getDirectionFromUnit(pTarget->getPos());
		vector<int> idxs = skill->getArea(direct, xyToIdx(pTarget->getPos()));

		for(int i = 0; i < idxs.size();i++){
			int idx = idxs.at(i);
			PuzzleMapUnit* pUnit = getUnit(idx);
			if(pUnit){
				long lForce = pUnit->getForceNo();
				if(!checkSideToForce(lForce) && map->isMovableCell(idxToPos(idx))){
					vecTarget.push_back(idx);
				}
			}
		}
	}
	return vecTarget;
}



void PuzzleUnitManager::limitBreak(int rank)
{
	PuzzleTMXTiledMap* map	= getMap();
	Point sidePOS			= map->getMapPoint(getSidePOS());
	
	map->clearShadowCell();
	
	int nIdx = getCurrentFrameIdx();
	PuzzleMapUnit* pSubject = getUnit(nIdx);
	changeCurrentFrame(-1);
	
	if(pSubject && pSubject->getRank() > 0){
		Skill* skill = pSubject->getSkill(rank);
		if(skill){
			BaseDamage::BD_TYPE scoreType = skill->getSkillDamage();
			vector<int> vec = makeLimitBreakTarget(nIdx,rank);
			
			for(int i = 0; i < vec.size();i++){
				int nTgt = vec.at(i);
				PuzzleMapUnit* pTarget = getUnit(nTgt);
				if(pTarget){
					pTarget->addCenterChainAnimation(getCurActionMgr(), 0, sidePOS, 0, 0, 0, scoreType);
					addUnitKOCount(pSubject->getShikigamiNo());
					setChainMarkandDelete(nTgt);
				}
			}
			
			pSubject->addCenterChainAnimation(getCurActionMgr(), 0, sidePOS, 0, 0, 0, scoreType);
			setChainMarkandDelete(xyToIdx(pSubject->getPos()));
			
			setCurActionMgr(getCurActionMgr() + 1);
		}
	}
	else{
		int i = 0;
		int ratio = rank * 2 - 1;
		int xSt = map->getMapWidth() /  2 - rank + 1;
		int xEn =xSt + ratio;
		
		for(int x = xSt; x < xEn ;x++){
			for(int y = 0 ; y < map->getMapHeight();y++){
				Point pos = Point(x,y);
				PuzzleMapUnit* pUnit = getUnit(pos);
				if(pUnit){
					long nForce = KoumeChan::getInstance()->getUnitForce(pUnit->getUnitNo());
					if(!checkSideToForce(nForce) && i < 20){
						pUnit->addCenterChainAnimation(getCurActionMgr() + i % ratio, 0,sidePOS,0, 0,0,BaseDamage::RAIL_OWN);
						setChainMarkandDelete(xyToIdx(pos));
						i++;
					}
					
				}
			}
		}
		setCurActionMgr(getCurActionMgr() + MIN(ratio,i));
	}

}

void PuzzleUnitManager::railgunFullPower()
{
	PuzzleTMXTiledMap* map	= getMap();
	Point sidePOS			= map->getMapPoint(getSidePOS());
	int i = 0;
	
	for(int x = map->getMapWidth() /  3; x < map->getMapWidth() * 2 / 3 ;x++){
		for(int y = 0 ; y < map->getMapHeight();y++){
			Point pos = Point(x,y);
			PuzzleMapUnit* pUnit = getUnit(pos);
			if(pUnit){
				long nForce			= pUnit->getForceNo();
				if(!checkSideToForce(nForce) && i < 20){
					pUnit->addCenterChainAnimation(getCurActionMgr() + i % 5, 0,sidePOS,0, 0,0,BaseDamage::RAIL_OWN);
					setChainMarkandDelete(xyToIdx(pos));
					i++;
				}
				
			}
		}
	}
	setCurActionMgr(getCurActionMgr() + 5);
}


bool PuzzleUnitManager::compareForce(int targetForce, int nTargetPos)
{
	PuzzleMapUnit* pUnit = getUnit(idxToPos(nTargetPos));
	if(pUnit){
		long forceNo = pUnit->getForceNo();
		Point tPos = idxToPos(nTargetPos);
		if(forceNo == targetForce){
			return true;
		}
	}
	return false;
}
int PuzzleUnitManager::findEnemyOnLine(int targetForce, bool bTop,int x,int y)
{
	PuzzleTMXTiledMap* map = getMap();
	if(map){
		int size = bTop ? MAX(x,map->getMapWidth() - x) : MAX(y,map->getMapHeight() - y) ;
		for(int i = 1 ; i < size;i++){
			int tgt1 = bTop ? xyToIdx(x + i,y) : xyToIdx(x,y + i);
			int tgt2 = bTop ? xyToIdx(x - i,y) : xyToIdx(x,y - i);
			if(compareForce(targetForce, tgt1)){
				return tgt1;
			}
			if(compareForce(targetForce, tgt2)){
				return tgt2;
			}
		}
	}
	return -1;
}
bool PuzzleUnitManager::checkSideToForce(int forceNo)
{
	PuzzleScene* pScene = (PuzzleScene*)getCurrentScene();
	if(pScene){
		Force* force = pScene->getCurrentPhaseForce();
		if(force){
			return force->getMasterNo() == forceNo;
		}
	}
	return false;
}
int PuzzleUnitManager::findOutBoundsTarget(bool bTop,cocos2d::Point basePos)
{
	Point tPos = Point(0,0);
	PuzzleTMXTiledMap* map = getMap();
	if(map){
		if(bTop){
			tPos = Point(0,basePos.y);
			if(basePos.x < map->getMapWidth() - basePos.x){
				tPos = Point(map->getMapWidth(),basePos.y);
			}
		}
		else{
			tPos = Point(basePos.x,0);
			if(basePos.y < map->getMapHeight() - basePos.y){
				tPos = Point(basePos.x,map->getMapHeight());
			}
		}
		
	}
//	log("自軍だけどライン上に敵なし %2.0f/%2.0f",tPos.x,tPos.y);
	return xyToIdx(tPos);
}
PuzzleTMXTiledMap::MAP_POS PuzzleUnitManager::getSidePOS()
{
	PuzzleScene* pScene = (PuzzleScene*)getCurrentScene();
	if(pScene){
		if(pScene->getPhase() == PuzzleScene::PHASE_PLAYER_1){
			return PuzzleTMXTiledMap::LEFT_SIDE;
		}
		return PuzzleTMXTiledMap::RIGHT_SIDE;
	}
	return PuzzleTMXTiledMap::BOTTOM_SIDE;
}

void PuzzleUnitManager::makeSideUnitAction(int idx,int chainCount,int moveUnitIdx,bool bOwn)
{
	Point pos = idxToPos(idx);
	PuzzleMapUnit* pUnit = getUnit(pos);
	if(pUnit){
		if(pUnit->getRank() == 0){
			pUnit->addSideChainAnimation(getCurActionMgr(), chainCount, idxToPos(moveUnitIdx));
			setChainMarkandDelete(idx);
		}
		else {
			if(bOwn){
				// エリートユニットスキル処理
				pUnit->addEliteAttackAnimation(getCurActionMgr(), chainCount, getPhaseChainCount());
				log("エリートスキル発動");
				setChainMarkandDelete(idx);
			}
			else{
				log("敵エリートなのでなにもしない　サイド");
				setChainMark(idx);
			}
		}
	}
}
bool PuzzleUnitManager::checkAllElite(PuzzleChain *chain)
{
	bool bElite = true;
	if(chain){
		for(int i = 0 ; i < chain->getChainCount();i++){
			PuzzleMapUnit* pUnit = getUnit(chain->getChain(i));
			if(pUnit && pUnit->getRank() == 0){
				return false;
			}
		}
	}
	return bElite;
}

void PuzzleUnitManager::makeChainThree(PuzzleChain* chain,int chainCount)
{
	int nTgt = -1;
	PuzzleTMXTiledMap* map	= getMap();
	Point sidePOS			= map->getMapPoint(getSidePOS());
	Point posC				= idxToPos(chain->getChain(1));	// 中心点
	PuzzleMapUnit* pUnitC	= getUnit(posC);
	BaseDamage::BD_TYPE scoreType = BaseDamage::THREE_OWN;
	bool bAllElite = checkAllElite(chain);
	
	if(pUnitC){		// センターユニットに各種処理を集める
		long nForce			= pUnitC->getForceNo();
		Force* force		= KoumeChan::getInstance()->getForceMaster(nForce);
		Point tPos			= Point(0,0);
		float attackedTime	= 1.0f;
		bool bOwn = true;
		if(nForce == NEUTRAL){	// 中立
			scoreType = BaseDamage::THREE_NEUTRAL;
		}
		else if(checkSideToForce(nForce)){	// 自軍
			if(force){
				nTgt	= findEnemyOnLine(force->getEnemyForceNo(),chain->getTop(), posC.x, posC.y);
				nTgt = addAttackAction(nTgt,posC,chain,chainCount,sidePOS,pUnitC);
				tPos = idxToPos(nTgt);
				attackedTime	= MAX(3.0f,MAX(abs(posC.x - tPos.x),abs(posC.y - tPos.y)));
			}
		}
		else{	// 敵軍
			bOwn = false;
			scoreType = BaseDamage::THREE_ENEMY;
		}
		// 両脇ユニットはセンターによって終わり
		makeSideUnitAction(chain->getChain(0), chainCount, chain->getChain(1),bOwn);
		makeSideUnitAction(chain->getChain(2), chainCount, chain->getChain(1),bOwn);
		
		// エリートで自分　エリート処理＋消す
		// エリートで敵　　通常処理＋消さない
		// 通常　　　　　　通常処理＋消す
		
		if(pUnitC->getRank() > 0){
			if(bOwn){
				pUnitC->addEliteCenterAnimation(getCurActionMgr(), chainCount, sidePOS, nTgt, getPhaseChainCount(), attackedTime, scoreType);
				log("センターエリート処理 %2.0f",attackedTime);
				setChainMarkandDelete(chain->getChain(1));
				
			}
			else{
				if(bAllElite){
					pUnitC->addEnemyCenterAnimation(getCurActionMgr(), chainCount,sidePOS,nTgt, getPhaseChainCount(),attackedTime,scoreType);
					setChainMarkandDelete(chain->getChain(1));
				}
				else{
					setChainMark(chain->getChain(1));
				}
			}
		}
		else{
			pUnitC->addCenterChainAnimation(getCurActionMgr(), chainCount,sidePOS,nTgt, getPhaseChainCount(),attackedTime,scoreType);
			setChainMarkandDelete(chain->getChain(1));
		}
	}
	else{
		assert(false);
	}

};
void PuzzleUnitManager::makeChainFour(PuzzleChain* chain,int chainCount)
{
	int nTgt = -1;
	PuzzleTMXTiledMap* map	= getMap();
	Point sidePOS			= map->getMapPoint(getSidePOS());
	PuzzleMapUnit* pUnit	= getUnit(chain->getChain(0));
	if(pUnit){
		long nForce			= pUnit->getForceNo();
		Force* force		= KoumeChan::getInstance()->getForceMaster(nForce);
		bool bOwn = true;
		if(nForce != NEUTRAL && !checkSideToForce(nForce)){
			bOwn = false;
		}
		bool bAllElite = checkAllElite(chain);

		for(int i = 0 ; i < 4 ; i++){		// センターユニットに各種処理を集める
			Point posC				= idxToPos(chain->getChain(i));	// 中心点
			PuzzleMapUnit* pUnitC	= getUnit(posC);
			Point tPos			= Point(0,0);
			BaseDamage::BD_TYPE scoreType = BaseDamage::FOUR_OWN;
			float attackedTime	= 1.0f;
			if(pUnitC){
				if(i == 1 || i == 2){
					makeSideUnitAction(chain->getChain(i), chainCount, chain->getChain(i == 1 ? 0 : 3),bOwn);
				}
				else{
					if(nForce == NEUTRAL){	// 中立
						scoreType = BaseDamage::FOUR_NEUTRAL;
					}
					else if(checkSideToForce(nForce)){	// 自軍
						if(force){
							nTgt	= findEnemyOnLine(force->getEnemyForceNo(),chain->getTop(), posC.x, posC.y);
							nTgt = addAttackAction(nTgt,posC,chain,chainCount,sidePOS,pUnitC);
							tPos = idxToPos(nTgt);
							attackedTime	= MAX(3.0f,MAX(abs(posC.x - tPos.x),abs(posC.y - tPos.y)));
						}
					}
					else{	// 敵軍
						scoreType = BaseDamage::FOUR_ENEMY;
					}
					if(pUnitC->getRank() > 0){
						if(bOwn){
							log("センターエリート処理");
							pUnitC->addEliteCenterAnimation(getCurActionMgr(), chainCount, sidePOS, nTgt, getPhaseChainCount(), attackedTime, scoreType);
							setChainMarkandDelete(chain->getChain(i));
							
						}
						else{
							if(bAllElite){
								pUnitC->addEnemyCenterAnimation(getCurActionMgr(), chainCount,sidePOS,nTgt, getPhaseChainCount(),attackedTime,scoreType);
								setChainMarkandDelete(chain->getChain(i));
							}
							else{
								setChainMark(chain->getChain(i));
							}
						}
					}
					else{
						pUnitC->addCenterChainAnimation(getCurActionMgr(), chainCount,sidePOS,nTgt, getPhaseChainCount(),attackedTime,scoreType);
						setChainMarkandDelete(chain->getChain(i));
					}
				}
			}
			else{
				assert(false);
			}
		}
	}
};

void PuzzleUnitManager::makeChainFive(PuzzleChain* chain,int chainCount)
{
	int nTgt = -1;
	PuzzleTMXTiledMap* map	= getMap();
	Point sidePOS			= map->getMapPoint(getSidePOS());
	PuzzleMapUnit* pUnit	= getUnit(chain->getChain(0));
	if(pUnit){
		int nForce			= pUnit->getForceNo();
		Force* force		= KoumeChan::getInstance()->getForceMaster(nForce);
		bool bOwn = true;
		if(nForce != NEUTRAL && !checkSideToForce(nForce)){
			bOwn = false;
		}
		bool bAllElite = checkAllElite(chain);
		
		for(int i = 0 ; i < 5 ; i++){		// センターユニットに各種処理を集める
			Point posC				= idxToPos(chain->getChain(i));	// 中心点
			PuzzleMapUnit* pUnitC	= getUnit(posC);
			Point tPos			= Point(0,0);
			float attackedTime	= 1.0f;
			if(pUnitC){
				BaseDamage::BD_TYPE scoreType = BaseDamage::FIVE_OWN;
				if(nForce == NEUTRAL){	// 中立
					scoreType = BaseDamage::FIVE_NEUTRAL;
				}
				else if(checkSideToForce(nForce)){	// 自軍
					if(force){
						nTgt	= findEnemyOnLine(force->getEnemyForceNo(),chain->getTop(), posC.x, posC.y);
						nTgt = addAttackAction(nTgt,posC,chain,chainCount,sidePOS,pUnitC);
						tPos = idxToPos(nTgt);
						attackedTime	= MAX(3.0f,MAX(abs(posC.x - tPos.x),abs(posC.y - tPos.y)));
					}
				}
				else{	// 敵軍
					scoreType = BaseDamage::FIVE_ENEMY;
				}
				if(pUnitC->getRank() > 0){
					if(bOwn){
						log("センターエリート処理");
						pUnitC->addEliteCenterAnimation(getCurActionMgr(), chainCount, sidePOS, nTgt, getPhaseChainCount(), attackedTime, scoreType);
						setChainMarkandDelete(chain->getChain(i));
						
					}
					else{
						if(bAllElite){
							pUnitC->addEnemyCenterAnimation(getCurActionMgr(), chainCount,sidePOS,nTgt, getPhaseChainCount(),attackedTime,scoreType);
							setChainMarkandDelete(chain->getChain(i));
						}
						else{
							setChainMark(chain->getChain(i));
						}
					}
				}
				else{
					pUnitC->addCenterChainAnimation(getCurActionMgr(), chainCount,sidePOS,nTgt, getPhaseChainCount(),attackedTime,scoreType);
					setChainMarkandDelete(chain->getChain(i));
				}
			}
			else{
				assert(false);
			}
		}
	}

};
void PuzzleUnitManager::makeChainCross(PuzzleChain* chain,int chainCount)
{
	int nTgt = -1;
	PuzzleTMXTiledMap* map	= getMap();
	Point sidePOS			= map->getMapPoint(getSidePOS());
	PuzzleMapUnit* pUnit	= getUnit(chain->getChain(0));
	if(pUnit){
		int nForce			= pUnit->getForceNo();
		Force* force		= KoumeChan::getInstance()->getForceMaster(nForce);
		bool bOwn = true;
		if(nForce != NEUTRAL && !checkSideToForce(nForce)){
			bOwn = false;
		}
		bool bAllElite = checkAllElite(chain);
		for(int i = 0 ; i < 5 ; i++){		// センターユニットに各種処理を集める
			Point posC				= idxToPos(chain->getChain(i));	// 中心点
			PuzzleMapUnit* pUnitC	= getUnit(posC);
			Point tPos			= Point(0,0);
			float attackedTime	= 1.0f;
			if(pUnitC){
				BaseDamage::BD_TYPE scoreType = BaseDamage::BORN_OWN;
				if(i == 1 || (chain->getType() == KoumeChan::CHAIN_T_3C && i == 2) || (chain->getType() != KoumeChan::CHAIN_T_3C && i == 3)){
					makeSideUnitAction(chain->getChain(i), chainCount, chain->getChain(i == 1 ? 0 : 4),bOwn);
				}
				else{
					if(nForce == NEUTRAL){	// 中立
						scoreType = BaseDamage::BORN_NEUTRAL;
					}
					else if(checkSideToForce(nForce)){	// 自軍
						if(force){
							nTgt	= findEnemyOnLine(force->getEnemyForceNo(),chain->getTop(), posC.x, posC.y);
							nTgt = addAttackAction(nTgt,posC,chain,chainCount,sidePOS,pUnitC);
							tPos = idxToPos(nTgt);
							attackedTime	= MAX(3.0f,MAX(abs(posC.x - tPos.x),abs(posC.y - tPos.y)));
						}
					}
					else{	// 敵軍
						scoreType = BaseDamage::BORN_ENEMY;
					}
					if(pUnitC->getRank() > 0){
						if(bOwn){
							log("センターエリート処理");
							pUnitC->addEliteCenterAnimation(getCurActionMgr(), chainCount, sidePOS, nTgt, getPhaseChainCount(), attackedTime, scoreType);
							setChainMarkandDelete(chain->getChain(i));
							
						}
						else{
							if(bAllElite){
								pUnitC->addEnemyCenterAnimation(getCurActionMgr(), chainCount,sidePOS,nTgt, getPhaseChainCount(),attackedTime,scoreType);
								setChainMarkandDelete(chain->getChain(i));
							}
							else{
								setChainMark(chain->getChain(i));
							}
						}
					}
					else{
						pUnitC->addCenterChainAnimation(getCurActionMgr(), chainCount,sidePOS,nTgt, getPhaseChainCount(),attackedTime,scoreType);
						setChainMarkandDelete(chain->getChain(i));
					}
				}
			}
			else{
				assert(false);
			}
		}
	}
};

int PuzzleUnitManager::addAttackAction(int nTgt,Point posC,PuzzleChain* chain,int chainCount,Point sidePOS,PuzzleMapUnit* pUnit)
{
	PuzzleMapUnit* pTarget = getUnit(nTgt);
	if(pTarget){
		Point tPos			= idxToPos(nTgt);
		float attackedTime	= MAX(3.0f,MAX(abs(posC.x - tPos.x),abs(posC.y - tPos.y)));
		pTarget->addAttackChainAnimation(getCurActionMgr(), chainCount, sidePOS,attackedTime);
		setChainMarkandDelete(nTgt);
		
		PuzzleMapUnit* pElite = addMapUnit(tPos,pUnit->getUnitNo(),1);
		if(pUnit->getShikigamiNo() >= 0){
			addUnitKOCount(pUnit->getShikigamiNo());
		}
//		pElite->setRank(1);
		pElite->addEliteCreateAnimation(getCurActionMgr(), chainCount,attackedTime );
		
	}
	else{
		nTgt = findOutBoundsTarget(chain->getTop(),posC);
	}
	return nTgt;
}
void PuzzleUnitManager::setChainMark(int idx)
{
	Point tPos = idxToPos(idx);
	PuzzleMapUnit* pTarget = getUnit(tPos);
	pTarget->setChainMark(true);
}
void PuzzleUnitManager::setChainMarkandDelete(int idx)
{
	Point tPos = idxToPos(idx);
	PuzzleMapUnit* pTarget = getUnit(tPos);
	pTarget->setChainMark(true);
	unitDeleted(tPos);
}
void PuzzleUnitManager::changeCurrentFrame(int idx)
{
	int oldIdx = getCurrentFrameIdx();
	if(oldIdx != idx){
		setSelectFrame(idx);
		setCurrentFrameIdx(idx);
	}
};
void PuzzleUnitManager::setSelectFrame(int idx)
{
	PuzzleTMXTiledMap* map = getMap();
	PuzzleMapUnit* pTarget = getUnit(idx);
	Sprite* sp	= (Sprite*)map->getChildByTag(PuzzleTMXTiledMap::TAG_FRAME);
	if(pTarget){
		Size size	= pTarget->getScaledContentSize();
		if(!sp){
			sp = Sprite::createWithSpriteFrameName("frame0.png");
			sp->setAnchorPoint(Point(0.5,0.5));
			sp->setContentSize(size);
			map->addChild(sp, 99,PuzzleTMXTiledMap::TAG_FRAME);
		}
		sp->setVisible(true);
		Point pos = pTarget->getPosition();
//		sp->setPosition(Point(pos.x - size.width / 2,pos.y - size.height / 2));
		sp->setPosition(map->getCenterPos(idxToPos(idx)));
		// LB状況とスキルの表示
		if(pTarget->getRank() > 0){
			showLimitBreakTarget(idx);
		}
		else{
			map->clearShadowCell();
		}
	}
	else{
		map->clearShadowCell();
		if(sp){
			sp->setVisible(false);
		}
	}
}


void PuzzleUnitManager::createHintTask()
{
	std::list<int>::iterator it = getCurrentHint();
	if(it == m_candidates.end()){
		it = m_candidates.begin();
	}
	else{
		it++;
	}
	if(it == m_candidates.end()){
		it = m_candidates.begin();
	}
	setCurrentHint(it);
	int candidate = (int)(*it);
	int c = candidateInt(candidate);
	int idx = candidateIdx(c);
	PuzzleMapUnit* unit = getUnit(idx);
	if(unit){
//		unit->setHint();
	}
};

void PuzzleUnitManager::stopHintTask()
{
	std::list<int>::iterator it = getCurrentHint();
	if(*it){
		int candidate = (int)(*it);
		int c = candidateInt(candidate);
		int idx = candidateIdx(c);
		PuzzleMapUnit* unit = getUnit(idx);
		if(unit){
			unit->showHint(false);
		}
	}
};

