//
//  CompetitionTMXMap.cpp
//  Koumechan
//
//  Created by 上野　彰三 on 2014/07/07.
//
//
#include "KoumeChan.h"
#include "CompetitionTMXMap.h"


using namespace cocos2d;
using namespace std;

CompetitionTMXMap* CompetitionTMXMap::create()
{
	CompetitionTMXMap* pRet = new CompetitionTMXMap();
	if(pRet && pRet->init()){
		pRet->autorelease();
	}
	else{
		CC_SAFE_DELETE(pRet);
		pRet = NULL;
	}
	return pRet;
}
bool CompetitionTMXMap::init()
{
	KoumeChan* chan = KoumeChan::getInstance();
	assert(chan);
	FriendMatch* pMatch = chan->getFriendMatch();
	if(pMatch){
		Scenario* sce = chan->getScenarioMaster(pMatch->getScenario());
		if(sce){
			setMapNo(sce->getMapNo());
			return PuzzleTMXTiledMap::init();
		}
	}
	return false;
}

bool CompetitionTMXMap::loadSpriteBatchNode()
{

	KoumeChan* chan = KoumeChan::getInstance();
	FriendMatch* pMatch = KoumeChan::getInstance()->getFriendMatch();
	setAppearanceRate(0);
	m_appearances.clear();
	if(pMatch){
		Scenario* sce = KoumeChan::getInstance()->getScenarioMaster(pMatch->getScenario());
		if(sce){
			long unitCount = sce->getUnitCount();
			SpriteFrameCache* spriteFrameCache = SpriteFrameCache::getInstance();
			for(long l = 0; l < unitCount;l++){
				BaseConditionMaster* scenarioUnit = sce->getUnit(l);
				if(scenarioUnit){
					MasterUnit* unit = chan->getUnitMaster(scenarioUnit->getKeyNo());
					spriteFrameCache->addSpriteFramesWithFile(unit->getPlistFileName(), unit->getPNGFileName());
					setAppearanceRate(getAppearanceRate() + scenarioUnit->getVal());
					m_appearances.push_back(getAppearanceRate());
				}
			}
			return true;
		}
	}

	return false;
}
int CompetitionTMXMap::findUnitOrderFromRate(long rate)
{
	FriendMatch* pMatch = KoumeChan::getInstance()->getFriendMatch();
	if(pMatch){
		Scenario* sce = KoumeChan::getInstance()->getScenarioMaster(pMatch->getScenario());
		if(sce){
			for(int i = 0 ; i < m_appearances.size();i++){
				if(rate < m_appearances.at(i)){
					return i;
				}
			}
		}
	}
	return -1;
}

long CompetitionTMXMap::findUnitNoFromRate(long rate)
{
	int no = findUnitOrderFromRate(rate);
	FriendMatch* pMatch = KoumeChan::getInstance()->getFriendMatch();
	if(pMatch){
		Scenario* sce = KoumeChan::getInstance()->getScenarioMaster(pMatch->getScenario());
		if(sce){
			BaseConditionMaster* scenarioUnit = sce->getUnit(no);
			if(scenarioUnit){
				return scenarioUnit->getKeyNo();
			}
		}
	}
	return -1;
}
