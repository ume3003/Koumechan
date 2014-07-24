//
//  QuestTMXMap.cpp
//  Koumechan
//
//  Created by 上野　彰三 on 2014/07/07.
//
//
#include "KoumeChan.h"
#include "MinorQuest.h"
#include "QuestTMXMap.h"


using namespace cocos2d;
using namespace std;

QuestTMPMap* QuestTMPMap::create()
{
	QuestTMPMap* pRet = new QuestTMPMap();
	if(pRet && pRet->init()){
		pRet->autorelease();
	}
	else{
		CC_SAFE_DELETE(pRet);
		pRet = NULL;
	}
	return pRet;
}

bool QuestTMPMap::init()
{
	KoumeChan* chan = KoumeChan::getInstance();
	MinorQuest* quest = chan->getMinorQuestMaster();
	if(quest){
		setMapNo(quest->getMapNo());
		return PuzzleTMXTiledMap::init();
	}
	return false;
}

bool QuestTMPMap::loadSpriteBatchNode()
{
	KoumeChan* chan = KoumeChan::getInstance();
	MinorQuest* quest = chan->getMinorQuestMaster();
	setAppearanceRate(0);
	m_appearances.clear();
	if(quest){
		long unitCount = quest->getUnitCount();
		SpriteFrameCache* spriteFrameCache = SpriteFrameCache::getInstance();
		for(long l = 0; l < unitCount;l++){
			BaseConditionMaster* questUnit = quest->getUnit(l);
			MasterUnit* unit = chan->getUnitMaster(questUnit->getKeyNo());
			spriteFrameCache->addSpriteFramesWithFile(unit->getPlistFileName(), unit->getPNGFileName());
			setAppearanceRate(getAppearanceRate() + questUnit->getVal());
			m_appearances.push_back(getAppearanceRate());
		}
		return true;
	}
	return false;
}

long QuestTMPMap::findUnitNoFromRate(long rate)
{
	KoumeChan* chan = KoumeChan::getInstance();
	MinorQuest* quest = chan->getMinorQuestMaster();
	for(int i = 0 ; i < m_appearances.size();i++){
		if(rate < m_appearances.at(i)){
			BaseConditionMaster* questUnit = quest->getUnit(i);
			if(questUnit){
				return questUnit->getKeyNo();
			}
			else{
				CCASSERT(false, "appearancerate is illigal");
				break;
			}
		}
	}
	return -1;
}
