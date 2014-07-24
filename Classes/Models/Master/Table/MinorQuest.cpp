//
//  MinorQuest.cpp
//  koumeChan
//
//  Created by 上野　彰三 on 2014/03/25.
//
//

#include "MinorQuest.h"
#include "JsonKeyString.h"
#include "KoumeChan.h"
#include "DirectionQuest.h"
#include "MajorQuest.h"

using namespace cocos2d;
using namespace std;

MinorQuest::MinorQuest()
{
	
}

MinorQuest::~MinorQuest()
{
	m_appearances.clear();
	m_units.clear();
}
MinorQuest* MinorQuest::createWithJson(Json *json)
{
	MinorQuest* pRet = new MinorQuest();
	if(pRet && pRet->initWithJson(json)){
		pRet->autorelease();
	}
	else{
		CC_SAFE_DELETE(pRet);
		pRet = NULL;
	}
	return pRet;
}
void MinorQuest::registerToParent()
{
	KoumeChan* chan = KoumeChan::getInstance();
	DirectionQuest* direction = chan->getDirectionMaster(getDirectionNo());
	if(direction){
		direction->addMinorQuestNo(getMasterNo());
	}
	MajorQuest* major = chan->getMajorQuestMaster(getMajorQuestNo());
	if(major){
		major->addMinorQuestNo(getMasterNo());
	}
	
}

bool MinorQuest::initWithJson(Json* json)
{
	if(BaseNamedMaster::initWithJson(json)){
		setDirectionNo(KoumeChan::getLong(json, JS_DIRECTION, -1));
		setMajorQuestNo(KoumeChan::getLong(json,JS_MAJOR,-1));
		setMapNo(KoumeChan::getInt(json,JS_MAP,-1));
		setAttackCount(KoumeChan::getInt(json,JS_ATTACK_COUNT,1));
		setNPCNo(KoumeChan::getLong(json, JS_NPC, 0));
		return true;
	}
	return false;
}

string MinorQuest::toJsonString()
{
	string baseStr = BaseNamedMaster::toJsonString();
	string jsonStr = StringUtils::format("{%s,%s,%s,%s,%s,%s}",
					baseStr.c_str(),
					jsLong(JS_DIRECTION,getDirectionNo()).c_str(),
				    jsLong(JS_MAJOR,getMajorQuestNo()).c_str(),
					jsLong(JS_MAP,getMapNo()).c_str(),
					jsLong(JS_NPC,getNPCNo()).c_str(),
					jsInt(JS_ATTACK_COUNT,getAttackCount()).c_str()
					);
	return jsonStr;
};

void MinorQuest::addAppearance(BaseConditionMaster *master)
{
	m_appearances.pushBack(master);
}
void MinorQuest::addUnit(BaseConditionMaster *master)
{
	m_units.pushBack(master);
}
void MinorQuest::addClear(BaseConditionMaster *master)
{
	m_clears.pushBack(master);
}
void MinorQuest::addReward(BaseConditionMaster *master)
{
	m_rewards.pushBack(master);
}


BaseConditionMaster* MinorQuest::getAppearance(long l)
{
	if(0 <= l && l < getAppearanceCount()){
		return m_appearances.at(l);
	}
	return NULL;
};
BaseConditionMaster* MinorQuest::getUnit(long l)
{
	if(0 <= l && l < getUnitCount()){
		return m_units.at(l);
	}
	return NULL;
	
};
BaseConditionMaster* MinorQuest::getClear(long l)
{
	if(0 <= l && l < getClearCount()){
		return m_clears.at(l);
	}
	return NULL;
	
};
BaseConditionMaster* MinorQuest::getReward(long l)
{
	if(0 <= l && l < getRewardCount()){
		return m_rewards.at(l);
	}
	return NULL;
};
void MinorQuest::clearChild(BaseMaster::MASTERNO masterNo)
{
	switch(masterNo){
		case BaseMaster::QUEST_APPEARANCE_MASTER:
			m_appearances.clear();
			break;
		case BaseMaster::QUEST_CLEAR_MASTER:
			m_clears.clear();
			break;
		case BaseMaster::QUEST_REWARD_MASTER:
			m_rewards.clear();
			break;
		case BaseMaster::QUEST_UNIT_MASTER:
			m_units.clear();
			break;
		default:
			break;
	}
}

