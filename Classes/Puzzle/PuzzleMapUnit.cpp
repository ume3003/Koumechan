//
//  PuzzleMapUnit.cpp
//  koumeChan
//
//  Created by 上野　彰三 on 2014/04/02.
//
//

#include "PuzzleMapUnit.h"
#include "PuzzleTMXTiledMap.h"
#include "PuzzleScene.h"
#include "PuzzleUnitManager.h"
#include "JsonKeyString.h"
#include "BaseDamage.h"
#include "Emotion.h"
using namespace cocos2d;
using namespace std;

PuzzleMapUnit::PuzzleMapUnit() : m_scene(NULL),m_frameSprite(NULL),m_hintSprite(NULL)
{
	setUnitNo(-1);
	setRank(0);
	setShikigamiNo(-1L);
	setPos(Point(-1,-1));
	setScaleToCell(1.0f);
	setDragMode(KDRAG_NONE);
	
}
PuzzleMapUnit::~PuzzleMapUnit()
{
	stopAllActions();
	removeAllChildren();
	CC_SAFE_RELEASE(m_scene);
	CC_SAFE_RELEASE(m_frameSprite);
	CC_SAFE_RELEASE(m_hintSprite);
}
bool PuzzleMapUnit::setupSprite()
{
	MasterUnit* unit = getUnit();
	if(unit ){
		std::string fileName = unit->getFrameName();
		setSpriteFrame(fileName);
		setAnchorPoint(Point(0.5,0.5));
		setScale(0.0f);
		return true;
	}
	return false;
}

bool PuzzleMapUnit::initWithData(long unitNo,Point pos,int actionOrder,Scene* scene,int rank,long shikigamiNo)
{
	if(KcSprite::init()){
		setUnitNo(unitNo);
		setPos(pos);
		setRank(rank);
		setShikigamiNo(shikigamiNo);
		if(setupSprite()){
			setVisible(false);
			setChainMark(false);
			setDeleted(false);
			setScene(scene);
			setMovable(true);
			return true;
		}
	}
	return false;
};
float PuzzleMapUnit::getFitScaleToParent(cocos2d::Size parentSize)
{
	Size  size = getContentSize();
	return min(parentSize.width / size.width,parentSize.height / size.height);
};
void PuzzleMapUnit::setFitScaleToParent(float width,float height)
{
	Size  size = getContentSize();
	m_scaleToCell = min(width / size.width,height / size.height);
};
cocos2d::Node* PuzzleMapUnit::getParentMap()
{
	return getParent();
	/*
	Node* parent = getParent();
	if(parent){
		return parent->getParent();
	}
	return NULL;
	 */
}

PuzzleMapUnit* PuzzleMapUnit::createWithData(long unitNo,Point pos,int actionOrder,Scene* scene,int rank,long shikigamiNo)
{
	PuzzleMapUnit* pRet = new PuzzleMapUnit();
	if(pRet && pRet->initWithData(unitNo,pos,actionOrder,scene,rank,shikigamiNo)){
		pRet->autorelease();
	}
	else{
		CC_SAFE_DELETE(pRet);
		pRet = NULL;
	}
	return pRet;
}

bool PuzzleMapUnit::onKCTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)
{
	PuzzleTMXTiledMap* map = (PuzzleTMXTiledMap*)getParentMap();
	PuzzleUnitManager* mgr = PuzzleUnitManager::getInstance();
	PuzzleScene* scene = (PuzzleScene*)getScene();
	if(scene && map && mgr){
		Point pos = map->convertTouchToNodeSpace(pTouch);
		Point mapPos = map->convertPosToMap(pos);
		if(scene->getPlayable() && mapPos == getPos() && getDragMode() == KDRAG_NONE){
			setDragMode(KDRAG_DRAGING);
			if(mgr->getCurrentFrameIdx() == xyToIdx(mapPos)){
				if(scene->canUnitUseLB(mgr->getCurrentFrameIdx())){
					scene->userUnitLBCommand(mapPos);
					scene->skillAttackAnimation();
					setDragMode(KDRAG_NONE);
				}
			}
			else{
				scene->userSelectUnit(mapPos);
				mgr->changeCurrentFrame(xyToIdx(mapPos));
			}
			pEvent->stopPropagation();
			return true;
		}
	}
	return false;
};

void PuzzleMapUnit::onKCTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)
{
	if(getDragMode() != KDRAG_DRAGING){
		return;
	}
	PuzzleScene* scene = (PuzzleScene*)getScene();
	PuzzleUnitManager* mgr = PuzzleUnitManager::getInstance();
	
	PuzzleTMXTiledMap* map = (PuzzleTMXTiledMap*)getParentMap();
	if(scene && map && mgr){
		Point pos = map->convertTouchToNodeSpace(pTouch);
		Point mapPos = map->convertPosToMap(pos);
		if(isNeighborCell(mapPos)){
			if(mgr->isSwitchable(getPos(), mapPos)){
				CallFunc* callback = CallFunc::create([this]{
					PuzzleScene* pScene = (PuzzleScene*)(this->getScene());
					if(pScene){
						pScene->cancelUserMove();
					}
				});
				mgr->changeCurrentFrame(-1);
				this->setDragMode(KDRAG_NONE);
				scene->setPlayable(false);
				mgr->setCurActionMgr(0);
				if(mgr->doSwitch(getPos(), mapPos)){
					scene->userMove(getPos(),mapPos);
					mgr->executeChain();
					callback = CallFunc::create([this]{
						PuzzleScene* pScene = (PuzzleScene*)(this->getScene());
						if(pScene){
							pScene->finishUserMove();
						}
					});
				}
				scene->addTask(PuzzleScene::USER_CHAIN_ANIMATION);
				mgr->unitAction(callback);
			}
		}
	}
};
void PuzzleMapUnit::onKCTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)
{
	setDragMode(KDRAG_NONE);
};
void PuzzleMapUnit::onKCTouchCancelled(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)
{
	PuzzleUnitManager* mgr = PuzzleUnitManager::getInstance();
	if(mgr){
		mgr->changeCurrentFrame(-1);
	}
	setDragMode(KDRAG_NONE);
};

bool PuzzleMapUnit::isNeighborCell(cocos2d::Point pos)
{
	Point cur = getPos();
	int x = abs(cur.x - pos.x);
	int y = abs(cur.y - pos.y);
	if( x + y == 1 && x * y == 0 ){
		return true;
	}
	return false;
};


int PuzzleMapUnit::getDistance(PuzzleMapUnit *pDist)
{
	if(pDist){
		Point src = getPos();
		Point dist = pDist->getPos();
		return MAX(abs(src.x - dist.x),abs(src.y - dist.y));
	}
	return 0;
};

MasterUnit* PuzzleMapUnit::getUnit()
{
	if(getShikigamiUnit()){
		return getShikigamiUnit();
	}
	return KoumeChan::getInstance()->getUnitMaster(getUnitNo());
};

MasterUnit* PuzzleMapUnit::getShikigamiUnit()
{
	return KoumeChan::getInstance()->getUnitMaster(getShikigamiNo());
};


long PuzzleMapUnit::getForceNo()
{
	MasterUnit* unit = getUnit();
	if(unit){
		return unit->getForceNo();
	}
	return 0;
}
void PuzzleMapUnit::addAction(int actionOrder,PuzzleAction* action)
{
	PuzzleActionManager* mgr = getActionManager(actionOrder);
	if(!mgr){
		mgr = PuzzleActionManager::create();
		setActionManager(actionOrder,mgr);
	}
	mgr->addAction(action);
};
FiniteTimeAction* PuzzleMapUnit::appearAction(PuzzleAction* action)
{
	return ScaleTo::create(action->getDuration(),getScaleToCell());
};
FiniteTimeAction* PuzzleMapUnit::desappearAction(PuzzleAction* action)
{
	return ScaleTo::create(action->getDuration(),0.0f);
};
FiniteTimeAction* PuzzleMapUnit::createAction(PuzzleAction *action)
{
	return CallFunc::create([this]{
		this->setVisible(true);
	});
}
bool PuzzleMapUnit::doAction(int actionOrder,CallFunc* callback)
{
	PuzzleActionManager* mgr = getActionManager(actionOrder);
	PuzzleTMXTiledMap* map = (PuzzleTMXTiledMap*)getParentMap();
	if(mgr && map){
		bool bCallback = true;
		Vector<FiniteTimeAction*> actions;
		for(int i = 0 ; i < mgr->getActionSize();i++){
			PuzzleAction* action = mgr->getAction(i);
			Point pos = getPos();
			if(action){
				Point posMap = action->getPos();
				Point posCen = map->getCenterPos(posMap);
				switch(action->getAction()){
					case PuzzleAction::PZ_CREATE:
						actions.pushBack(createAction(action));
						break;
					case PuzzleAction::PZ_APPEAR:
						actions.pushBack(appearAction(action));
						break;
					case PuzzleAction::PZ_DESAPPEAR:
						actions.pushBack(desappearAction(action));
						break;
					case PuzzleAction::PZ_DOCALLBACK:
						actions.pushBack(callback);
						bCallback = false;
						break;
					case PuzzleAction::PZ_MOVEOUT:
						actions.pushBack(
							 Spawn::createWithTwoActions(
								MoveTo::create(action->getDuration(),posMap),
								RotateBy::create(action->getDuration(), 360)
							)
						);
						break;
					case PuzzleAction::PZ_SCORE:
						actions.pushBack(CallFunc::create([this,action]{
							this->showScore(action->getScoreType(),(int)action->getDuration(),action->getPos());
						}));
						break;
					case PuzzleAction::PZ_ELITE_SCORE:
						actions.pushBack(Spawn::createWithTwoActions(
							DelayTime::create(0.5f),
							CallFunc::create([this,action]{
							this->showEliteScore(action->getScoreType(),(int)action->getDuration(),action->getPos());
						})));
						break;
					case PuzzleAction::PZ_EXPLOSION:
						actions.pushBack(CallFunc::create([this,posMap]{
							this->setPos(posMap);
						}));
						break;
					case PuzzleAction::PZ_ATTACK:
						actions.pushBack(
							Spawn::create(
								DelayTime::create(action->getDuration()),
								CallFunc::create([this,pos,action]{
									this->showExplosionLine(pos, action->getPos(),action->getDuration());
								}),
								NULL)
						);
						break;
					case PuzzleAction::PZ_WARP:
						actions.pushBack(Place::create(posCen));
						actions.pushBack(CallFunc::create([this,posMap]{
							this->setPos(posMap);
						}));
						break;
					case PuzzleAction::PZ_WAIT:
						actions.pushBack(DelayTime::create(action->getDuration()));
						break;
					case PuzzleAction::PZ_MOVE:
						actions.pushBack(MoveTo::create(action->getDuration(),posCen));
						actions.pushBack(CallFunc::create([this,posMap]{
							this->setPos(posMap);
						}));
						break;
					case PuzzleAction::PZ_CHAINCOUNT:
						actions.pushBack(CallFunc::create([this,action]{
							this->showChainCount((int)action->getDuration(),action->getPos());
						}));
						break;
					case PuzzleAction::PZ_MARK:
						actions.pushBack(Spawn::createWithTwoActions(DelayTime::create(action->getDuration()),
																	 CallFunc::create([this]{ this->showBackGround();})));
						break;
					case PuzzleAction::PZ_DOWN:
						actions.pushBack(MoveTo::create(0.3f * action->getDuration(),posCen));
						actions.pushBack(CallFunc::create([this,posMap]{
							this->setPos(posMap);
						}));
						break;
					case PuzzleAction::PZ_DOWNLEFT:
						actions.pushBack(MoveTo::create(0.2f,map->getCenterPos(Point(posMap.x + 1,posMap.y))));
						actions.pushBack(MoveTo::create(0.1f,posCen));
						actions.pushBack(CallFunc::create([this,posMap]{
							this->setPos(posMap);
						}));
						break;
					case PuzzleAction::PZ_DOWNRIGHT:
						actions.pushBack(MoveTo::create(0.2f,map->getCenterPos(Point(posMap.x - 1,posMap.y))));
						actions.pushBack(MoveTo::create(0.1f,map->getCenterPos(posMap)));
						actions.pushBack(CallFunc::create([this,posMap]{
							this->setPos(posMap);
						}));
						break;
					default:
						break;
				}
			}
		}
		if(actions.size() > 0){
			if(bCallback){
				actions.pushBack(callback)	;
			}
			Sequence* ac = Sequence::create(actions);
			runAction(ac);
			return true;
		}
	}
	return false;
};
//  "JSUNIT":{"NO","0","TAG":,0}
std::string PuzzleMapUnit::toJsonString()
{
	std::string str = StringUtils::format("%s:{%s,%s}",JS_UNIT,jsLong(JS_NO, getUnitNo()).c_str(),jsInt(JS_TAG_NO,getTag()).c_str());
	return str;
}
// { "UNIT":{"NO","0","TAG":,0} ,"DATA":{[]} }
std::string PuzzleMapUnit::actionToString(int actionOrder)
{
	PuzzleActionManager* mgr = getActionManager(actionOrder);
	std::string strMgr = StringUtils::format("%s:{[",JS_DATA);
	if(mgr){
		strMgr = StringUtils::format("%s%s",strMgr.c_str(),mgr->toJsonString().c_str());
	}
	strMgr = StringUtils::format("%s]}",strMgr.c_str());
	std::string str = StringUtils::format("{%s,%s}",toJsonString().c_str(),strMgr.c_str());
	return str;
};

void PuzzleMapUnit::clearAction()
{
	Map<int,PuzzleActionManager*>::iterator it = m_actionMgr.begin();
	while(it != m_actionMgr.end())
	{
		PuzzleActionManager* mgr = (PuzzleActionManager*)(*it).second;
		if(mgr){
			mgr->clear();
		}
		++it;
	}
	m_actionMgr.clear();
};

void PuzzleMapUnit::addWarpAnimation(int actionOrder, float waitTime, cocos2d::Point warpPos)
{
	addAction(actionOrder,PuzzleAction::create(PuzzleAction::PZ_DESAPPEAR	,getPos(),0.1f * waitTime));
	addAction(actionOrder,PuzzleAction::create(PuzzleAction::PZ_WAIT		,getPos(),0.5f));
	addAction(actionOrder,PuzzleAction::create(PuzzleAction::PZ_WARP		,warpPos,0.3f));
	addAction(actionOrder,PuzzleAction::create(PuzzleAction::PZ_MARK		,warpPos,0.2f));
	addAction(actionOrder,PuzzleAction::create(PuzzleAction::PZ_APPEAR		,warpPos,0.3f));
}
void PuzzleMapUnit::addSideChainAnimation(int actionOrder, float waitTime,Point outPos)
{
	addAction(actionOrder,PuzzleAction::create(PuzzleAction::PZ_WAIT		,getPos(),0.3f * waitTime));
	addAction(actionOrder,PuzzleAction::create(PuzzleAction::PZ_MARK		,getPos(),0.3f));
	addAction(actionOrder,PuzzleAction::create(PuzzleAction::PZ_MOVE		,outPos  ,0.2f));
	addAction(actionOrder,PuzzleAction::create(PuzzleAction::PZ_DOCALLBACK	,outPos  ,0.0f));
	addAction(actionOrder,PuzzleAction::create(PuzzleAction::PZ_DESAPPEAR	,outPos  ,0.3f));
	
}

void PuzzleMapUnit::addEliteAttackAnimation(int actionOrder,float waitTime,int chainCount)
{
	BaseDamage::BD_TYPE skillType = BaseDamage::NONE;
	Skill* skill = getSkill(0);
	if(skill != NULL){
		skillType = skill->getSkillDamage();
	}
	
	addAction(actionOrder,PuzzleAction::create(PuzzleAction::PZ_WAIT		,getPos(),0.3f * waitTime));
	addAction(actionOrder,PuzzleAction::create(PuzzleAction::PZ_MARK		,getPos(),0.3f));
	if(skillType != BaseDamage::NONE){
		addAction(actionOrder,PuzzleAction::create(PuzzleAction::PZ_ELITE_SCORE,getPos(),chainCount,skillType));
	}
	addAction(actionOrder,PuzzleAction::create(PuzzleAction::PZ_MOVE		,getPos(),0.2f));
	addAction(actionOrder,PuzzleAction::create(PuzzleAction::PZ_DOCALLBACK	,getPos(),0.0f));
	addAction(actionOrder,PuzzleAction::create(PuzzleAction::PZ_DESAPPEAR	,getPos(),0.3f));
	
}

void PuzzleMapUnit::addEliteCreateAnimation(int actionOrder,float waitTime,float attackedTime)
{
	addAction(actionOrder,PuzzleAction::create(PuzzleAction::PZ_CREATE		,getPos(),0));
	addAction(actionOrder,PuzzleAction::create(PuzzleAction::PZ_WAIT		,getPos(),0.3f * waitTime));
	addAction(actionOrder,PuzzleAction::create(PuzzleAction::PZ_WAIT		,getPos(),0.3f));	// MARK
	addAction(actionOrder,PuzzleAction::create(PuzzleAction::PZ_WAIT		,getPos(),0.2f));	// WAIT
	addAction(actionOrder,PuzzleAction::create(PuzzleAction::PZ_WAIT		,getPos(),0.1f * attackedTime));	// MOVE
	addAction(actionOrder,PuzzleAction::create(PuzzleAction::PZ_APPEAR		,getPos(),0.6f));
	
}

void PuzzleMapUnit::addAttackChainAnimation(int actionOrder, float waitTime,Point outPos,float attackedTime)
{
	addAction(actionOrder,PuzzleAction::create(PuzzleAction::PZ_WAIT		,getPos(),0.3f * waitTime));
	addAction(actionOrder,PuzzleAction::create(PuzzleAction::PZ_WAIT		,getPos(),0.3f));	// MARK
	addAction(actionOrder,PuzzleAction::create(PuzzleAction::PZ_WAIT		,getPos(),0.2f));	// WAIT
	addAction(actionOrder,PuzzleAction::create(PuzzleAction::PZ_WAIT		,getPos(),0.1f * attackedTime));	// MOVE
	addAction(actionOrder,PuzzleAction::create(PuzzleAction::PZ_WAIT		,getPos(),0.2f));	// WAIT
	addAction(actionOrder,PuzzleAction::create(PuzzleAction::PZ_WAIT		,getPos(),0.2f));	// MOVE OUT
	addAction(actionOrder,PuzzleAction::create(PuzzleAction::PZ_MOVEOUT		,outPos  ,0.4f));
	addAction(actionOrder,PuzzleAction::create(PuzzleAction::PZ_DOCALLBACK	,outPos  ,0.0f));
	addAction(actionOrder,PuzzleAction::create(PuzzleAction::PZ_DESAPPEAR	,outPos  ,0.3f));
	
}
void PuzzleMapUnit::addCenterChainAnimation(int actionOrder, float waitTime,Point outPos,int nTgt,int chainCount,float attackedTime,BaseDamage::BD_TYPE scoreType)
{
	addAction(actionOrder,PuzzleAction::create(PuzzleAction::PZ_WAIT		,getPos(),0.3f * waitTime));
	addAction(actionOrder,PuzzleAction::create(PuzzleAction::PZ_MARK		,getPos(),0.3f));
	addAction(actionOrder,PuzzleAction::create(PuzzleAction::PZ_WAIT		,getPos(),0.2f));
	if(nTgt>= 0){
		Point tgtPos = idxToPos(nTgt);
		addAction(actionOrder,PuzzleAction::create(PuzzleAction::PZ_ATTACK	,tgtPos  ,0.1f * attackedTime));
		
	}
	if(chainCount > 0){
		addAction(actionOrder,PuzzleAction::create(PuzzleAction::PZ_CHAINCOUNT	,getPos(),chainCount));
	}
	addAction(actionOrder,PuzzleAction::create(PuzzleAction::PZ_WAIT		,getPos(),0.2f));
	addAction(actionOrder,PuzzleAction::create(PuzzleAction::PZ_SCORE		,getPos(),chainCount,scoreType));
	addAction(actionOrder,PuzzleAction::create(PuzzleAction::PZ_MOVEOUT		,outPos  ,0.4f));
	addAction(actionOrder,PuzzleAction::create(PuzzleAction::PZ_WAIT		,getPos(),0.3f));
	addAction(actionOrder,PuzzleAction::create(PuzzleAction::PZ_DOCALLBACK	,getPos(),0.0f));
	addAction(actionOrder,PuzzleAction::create(PuzzleAction::PZ_DESAPPEAR	,getPos(),0.3f));
	
}
void PuzzleMapUnit::addEnemyCenterAnimation(int actionOrder, float waitTime,Point outPos,int nTgt,int chainCount,float attackedTime,BaseDamage::BD_TYPE scoreType)
{
	log("enemycenter %d %2.0f",actionOrder,waitTime);
	addAction(actionOrder,PuzzleAction::create(PuzzleAction::PZ_WAIT		,getPos(),0.3f * waitTime));
	addAction(actionOrder,PuzzleAction::create(PuzzleAction::PZ_MARK		,getPos(),0.3f));
	addAction(actionOrder,PuzzleAction::create(PuzzleAction::PZ_WAIT		,getPos(),0.2f));
/*
	if(nTgt>= 0){
		Point tgtPos = idxToPos(nTgt);
		addAction(actionOrder,PuzzleAction::create(PuzzleAction::PZ_ATTACK	,tgtPos  ,0.1f * attackedTime));
		
	}
*/
	if(chainCount > 0){
		addAction(actionOrder,PuzzleAction::create(PuzzleAction::PZ_CHAINCOUNT	,getPos(),chainCount));
	}
	addAction(actionOrder,PuzzleAction::create(PuzzleAction::PZ_WAIT		,getPos(),0.2f));
	addAction(actionOrder,PuzzleAction::create(PuzzleAction::PZ_SCORE		,getPos(),chainCount,scoreType));
	addAction(actionOrder,PuzzleAction::create(PuzzleAction::PZ_WAIT		,getPos(),0.3f));
	addAction(actionOrder,PuzzleAction::create(PuzzleAction::PZ_DOCALLBACK	,getPos(),0.0f));
	addAction(actionOrder,PuzzleAction::create(PuzzleAction::PZ_DESAPPEAR	,getPos(),0.3f));
	
}
void PuzzleMapUnit::addEliteCenterAnimation(int actionOrder,float waitTime,cocos2d::Point outPos,int nTgt,int chainCount,float attackedTime,BaseDamage::BD_TYPE scoreType)
{
	BaseDamage::BD_TYPE skillType = BaseDamage::NONE;
	Skill* skill = getSkill(0);
	if(skill != NULL){
		skillType = skill->getSkillDamage();
	}
	
	addAction(actionOrder,PuzzleAction::create(PuzzleAction::PZ_WAIT		,getPos(),0.3f * waitTime));
	addAction(actionOrder,PuzzleAction::create(PuzzleAction::PZ_MARK		,getPos(),0.3f));
	addAction(actionOrder,PuzzleAction::create(PuzzleAction::PZ_WAIT		,getPos(),0.2f));
	if(nTgt>= 0){
		Point tgtPos = idxToPos(nTgt);
		addAction(actionOrder,PuzzleAction::create(PuzzleAction::PZ_ATTACK	,tgtPos  ,0.1f * attackedTime));
		
	}
	if(chainCount > 0){
		addAction(actionOrder,PuzzleAction::create(PuzzleAction::PZ_CHAINCOUNT	,getPos(),chainCount));
	}
	addAction(actionOrder,PuzzleAction::create(PuzzleAction::PZ_WAIT		,getPos(),0.2f));
	addAction(actionOrder,PuzzleAction::create(PuzzleAction::PZ_SCORE		,getPos(),chainCount,scoreType));
	if(skillType != BaseDamage::NONE){
		addAction(actionOrder,PuzzleAction::create(PuzzleAction::PZ_ELITE_SCORE,getPos(),chainCount,skillType));
	}
	addAction(actionOrder,PuzzleAction::create(PuzzleAction::PZ_MOVEOUT		,outPos  ,0.4f));
	addAction(actionOrder,PuzzleAction::create(PuzzleAction::PZ_WAIT		,getPos(),0.3f));
	addAction(actionOrder,PuzzleAction::create(PuzzleAction::PZ_DOCALLBACK	,getPos(),0.0f));
	addAction(actionOrder,PuzzleAction::create(PuzzleAction::PZ_DESAPPEAR	,getPos(),0.3f));
}


void PuzzleMapUnit::addChainAnimation(int actionOrder, float waitTime,Point outPos,int chainCount)
{
	addAction(actionOrder,PuzzleAction::create(PuzzleAction::PZ_WAIT		,getPos(),0.3f * waitTime));
	addAction(actionOrder,PuzzleAction::create(PuzzleAction::PZ_MARK		,getPos(),0.3f));
	addAction(actionOrder,PuzzleAction::create(PuzzleAction::PZ_MOVEOUT		,outPos  ,0.4f));
	if(chainCount > 0){
		addAction(actionOrder,PuzzleAction::create(PuzzleAction::PZ_CHAINCOUNT	,getPos(),chainCount));
	}
	addAction(actionOrder,PuzzleAction::create(PuzzleAction::PZ_WAIT		,getPos(),0.3f));
	addAction(actionOrder,PuzzleAction::create(PuzzleAction::PZ_DOCALLBACK	,getPos(),0.0f));
	addAction(actionOrder,PuzzleAction::create(PuzzleAction::PZ_DESAPPEAR	,getPos(),0.3f));
	
}

void PuzzleMapUnit::addMarkAnimation(int actionOrder,float waitTime)
{
	addAction(actionOrder,PuzzleAction::create(PuzzleAction::PZ_WAIT,getPos(),waitTime));
	addAction(actionOrder,PuzzleAction::create(PuzzleAction::PZ_MARK,getPos(),0.3f));
}
void PuzzleMapUnit::addAppearAnimation(int actionOrder)
{
	float dura = 0.3f * ( getTag() % 5);
	addAction(actionOrder, PuzzleAction::create(PuzzleAction::PZ_WAIT  ,getPos(), dura));
	addAction(actionOrder, PuzzleAction::create(PuzzleAction::PZ_CREATE,getPos(),0.0f));
	addAction(actionOrder, PuzzleAction::create(PuzzleAction::PZ_APPEAR,getPos(),0.3f));
}

void PuzzleMapUnit::addCreateAnimation(int actionOrder,float waitTime)
{
	addAction(actionOrder,PuzzleAction::create(PuzzleAction::PZ_CREATE,getPos(),0));
	addAction(actionOrder,PuzzleAction::create(PuzzleAction::PZ_WAIT  ,getPos(),waitTime));
	addAction(actionOrder,PuzzleAction::create(PuzzleAction::PZ_APPEAR,getPos(),0));
	
}

Skill* PuzzleMapUnit::getSkill(int level)
{
	MasterUnit* unit = getUnit();
	if(unit){
		MasterUnitSkill* unitSkill = (MasterUnitSkill*)unit->getSkill(level);
		if(unitSkill){
			return KoumeChan::getInstance()->getSkillMaster(unitSkill->getKeyNo());
		}
	}
	return NULL;
}

void PuzzleMapUnit::setHint()
{
	scheduleOnce(schedule_selector(PuzzleMapUnit::startHint), 5.0f);
}
void PuzzleMapUnit::startHint(float frame)
{
	PuzzleScene* scene = (PuzzleScene*)getScene();
	if(scene){
		if(scene->getPlayable()){
			showHint(true);
		}
	}
}
void PuzzleMapUnit::nextHint()
{
}
void PuzzleMapUnit::showHint(bool bShow)
{
	Size size = getScaledContentSize();
	if(bShow){
		if(!getHintSprite()){
			Sprite* sp = Emotion::getInstance()->getSprite(Emotion::CHECK0);
			sp->setVisible(true);
			sp->setAnchorPoint(Point(0,0));
			Point pos = getPosition();
			sp->setPosition(Point(pos.x - size.width / 2,pos.y - size.height / 2));
			setFrameSprite(sp);
			getParentMap()->addChild(sp,99,99);
			Sequence* seq = Sequence::create(
											 Show::create(),
											 JumpBy::create(3.0f, Vec2(0,size.height /3), size.height/2, 3),
											 CallFunc::create([this]{
												this->nextHint();
												this->setHintSprite(NULL);
											}),
											 RemoveSelf::create(),
											 NULL);
			sp->runAction(seq);
		}
	}
	else{
		unscheduleAllSelectors();
		if(getHintSprite()){
			getHintSprite()->stopAllActions();
			getHintSprite()->removeFromParent();
			setHintSprite(NULL);
		}
	}
}



void PuzzleMapUnit::showBackGround()
{
	Size size = getScaledContentSize();
	
	LayerColor* lc = LayerColor::create(Color4B::BLUE, size.width, size.height);
	if(lc){
		Point pos = getPosition();
		lc->setPosition(Point(pos.x - size.width / 2,pos.y - size.height / 2));
		getParentMap()->addChild(lc, PuzzleScene::LZ_UI, 99);
		
		Sequence* seq = Sequence::create(FadeTo::create(0.5f, 1),FadeOut::create(0.5f),
										 RemoveSelf::create(),NULL);
		lc->runAction(seq);
	}
}

void PuzzleMapUnit::showExplosion(cocos2d::Point mapPos)
{
	Size size = getScaledContentSize();
	size.width = size.width * getScaleToCell();
	size.height = size.height * getScaleToCell();

	PuzzleTMXTiledMap* map = (PuzzleTMXTiledMap*)getParentMap();
	ParticleExplosion* explosion = ParticleExplosion::create();
	if(explosion){
		explosion->setContentSize(size);
		Point pos = getPosition();
		explosion->setPosition(Point(pos.x ,pos.y ));
		map->addChild(explosion);
		Sequence* seq = Sequence::create(FadeTo::create(0.3f, 1),FadeOut::create(0.3f),
										 RemoveSelf::create(),NULL);
		explosion->runAction(seq);
		
	}
}
void PuzzleMapUnit::showExplosionLine(cocos2d::Point startPos,cocos2d::Point endPos,float duration)
{
	Size size = getScaledContentSize();
	PuzzleTMXTiledMap* map = (PuzzleTMXTiledMap*)getParentMap();
	int xDiff = startPos.x - endPos.x;
	int yDiff = startPos.y - endPos.y;
	int diff = xDiff + yDiff > 0 ? -1 : 1;
	int  dist = MAX(abs(xDiff),abs(yDiff)) + 1;
	if(duration != 0.0f && dist != 0){
		float dur = duration / 4;
		for(int i = 0;i < dist;i++){
			Vector<FiniteTimeAction*> actions;
			ParticleExplosion* explosion = ParticleExplosion::create();
			explosion->setContentSize(size);
			explosion->setScale(i == dist - 1 ? 1.5f : 1.0f);
			Point tgt = xDiff == 0 ? Point(startPos.x,startPos.y + i * diff) : Point(startPos.x + i * diff,startPos.y);
			explosion->setPosition(map->getCenterPos(tgt));
			actions.pushBack(DelayTime::create(i * 0.1f));
			actions.pushBack(FadeTo::create(dur,2));
			actions.pushBack(DelayTime::create(dur * 2));
			actions.pushBack(FadeOut::create(dur));
			actions.pushBack(RemoveSelf::create());
			map->addChild(explosion, 99);
			Sequence* seq = Sequence::create(actions);
			explosion->runAction(seq);
		}
	}
}

void PuzzleMapUnit::showChainCount(int count,Point pos)
{
	if(count > 1){
		PuzzleScene* scene = (PuzzleScene*)getScene();
		if(scene){
			scene->sayComboCount(count);
		}
	}
	
	
}
void PuzzleMapUnit::showPoint(cocos2d::Point pos,POINT_TYPE type,int nPoint)
{
	std::string str = StringUtils::format("%d",nPoint);
	PuzzleTMXTiledMap* map = (PuzzleTMXTiledMap*)getParentMap();
	Size size = getScaledContentSize();
	Color4B color = Color4B::WHITE;
	if(map){
		switch(type){
			case OWN_HP:
				str = StringUtils::format("HitPoint %+d",nPoint);
				color = Color4B::BLACK;
				break;
			case OWN_PW:
				str = StringUtils::format("Power %+d",nPoint);
				color = Color4B::BLUE;
				break;
			case ENEMY_HP:
				str = StringUtils::format("Damage %+d",nPoint);
				color = Color4B::RED;
				break;
			case ENEMY_PW:
				str = StringUtils::format("Decrease %+d",nPoint);
				color = Color4B::ORANGE;
				break;
			default:
				break;
		}
		Label* ttf = Label::createWithSystemFont(str, DLG_FONT, DLG_LARGE_FONT_SIZE);
		if(ttf){
			ttf->setTextColor(color);
			ttf->setScale(2.5 * size.width / ttf->getContentSize().width );
			ttf->setPosition(pos);
			getParentMap()->addChild(ttf,PuzzleScene::LZ_UI,99);
			Sequence* seq = Sequence::create(Show::create(),JumpBy::create(1.0f,Point(0,size.height / 3),size.height,1),RemoveSelf::create(),NULL);
			ttf->runAction(seq);
		}
	}
}
cocos2d::Size PuzzleMapUnit::getScaledContentSize()
{
	Size size = getContentSize();
	size.width = size.width * getScaleToCell();
	size.height = size.height * getScaleToCell();
	return size;
}



void PuzzleMapUnit::showScore(BaseDamage::BD_TYPE scoreType, int chainCount,Point mapPos)
{
	BaseDamage* bd = KoumeChan::getInstance()->getBaseDamageMaster(scoreType);
	PuzzleTMXTiledMap* map = (PuzzleTMXTiledMap*)getParentMap();
	PuzzleScene* scene = (PuzzleScene*)getScene();
	Size sizeC = getScaledContentSize();
	if(scene && bd && map && scene->getPhase() != PuzzleScene::PHASE_NONE){
		int nChain = chainCount > 1 ? chainCount * 2 : 0;	// チェイン数による追加点
		int nOwnHP = bd->getOwnHitPoint();				// 自分HPの増減点
		int nOwnPW = bd->getOwnPower();					// 自分PWの増減点
		int nEneHP = bd->getEnemyHitPoint();			// 敵HPの増減点
		int nEnePW = bd->getEnemyPower();				// 敵PWの増減点
		log("+++++++ score %d ownHP %d ownPW %d EnemyHP %d enemyPW %d",scoreType,nOwnHP,nOwnPW,nEneHP,nEnePW);
		Point pos = map->getCenterPos(mapPos);
		if(nOwnHP != 0){
			Point posN = Point(pos.x - sizeC.width,pos.y + sizeC.height);
			showPoint(posN,OWN_HP,	nOwnHP + nChain);
			scene->changeOwnHP(		nOwnHP + nChain);
		}
		if(nOwnPW != 0){
			Point posN = Point(pos.x - sizeC.width,pos.y - sizeC.height);
			showPoint(posN,OWN_PW,	nOwnPW + nChain);
			scene->changeOwnPW(		nOwnPW + nChain);
		}
		if(nEneHP != 0){
			Point posN = Point(pos.x + sizeC.width,pos.y + sizeC.height);
			showPoint(posN,ENEMY_HP,nEneHP - nChain);
			scene->changeEnemyHP(	nEneHP - nChain);
		}
		if(nEnePW != 0){
			Point posN = Point(pos.x + sizeC.width,pos.y - sizeC.height);
			showPoint(posN,ENEMY_PW,nEnePW - nChain);
			scene->changeEnemyPW(	nEnePW - nChain);
		}
		scene->updateScore();
	}
}

void PuzzleMapUnit::showEliteScore(BaseDamage::BD_TYPE scoreType, int chainCount,Point mapPos)
{
	log("showEliteScore");
	MasterUnit* unit = getUnit();
	MasterUnitSkill* unitSkill = (MasterUnitSkill*)unit->getSkill(0);
	Skill* skill = KoumeChan::getInstance()->getSkillMaster(unitSkill->getKeyNo());
	PuzzleTMXTiledMap* map = (PuzzleTMXTiledMap*)getParentMap();
	Emotion::EMOTION_TYPE emo = Emotion::MARU0;
	switch(skill->getMasterNo()){
		case Skill::TAUNT:
			emo = Emotion::KIRARI0;
			break;
		case Skill::ATTACK:
		case Skill::MAGIC:
			emo = Emotion::NIYARI0;
			break;
		case Skill::BUFF:
		case Skill::HEAL:
			emo = Emotion::HOSHI0;
			break;
		default:
			break;
	}
	
	Sprite* sp = Emotion::getInstance()->getSprite(emo);
	if(map && sp){
		sp->setPosition(map->getCenterPos(mapPos));
		sp->setScale(2.0f);
		getParentMap()->addChild(sp,PuzzleScene::LZ_UI,99);
		Size size = getScaledContentSize();
		Sequence* seq = Sequence::create(Show::create(),JumpBy::create(1.0f,Point(0,size.height / 2),size.height,1),RemoveSelf::create(),NULL);
		sp->runAction(seq);
	}
	PuzzleScene* scene = (PuzzleScene*)getScene();
	if(scene){
		scene->saySkill(unitSkill->getKeyNo());
	}
	showScore(scoreType, chainCount, mapPos);
	
}


