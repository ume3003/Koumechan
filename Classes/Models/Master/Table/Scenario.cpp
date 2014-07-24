//
//  Scenario.cpp
//  koumeChan
//
//  Created by 上野　彰三 on 2014/04/01.
//
//

#include "Scenario.h"
#include "JsonKeyString.h"
#include "KoumeChan.h"

using namespace cocos2d;
using namespace std;

Scenario::Scenario()
{
	
}

Scenario::~Scenario()
{
	m_ScenarioRule.clear();
	m_ScenarioUnit.clear();
}

Scenario* Scenario::createWithJson(Json *json)
{
	Scenario* pRet = new Scenario();
	if(pRet && pRet->initWithJson(json)){
		pRet->autorelease();
	}
	else{
		CC_SAFE_DELETE(pRet);
		pRet = NULL;
	}
	return pRet;
}

bool Scenario::initWithJson(Json* json)
{
	if(BaseNamedMaster::initWithJson(json)){
		setMapNo(KoumeChan::getInt(json,JS_MAP,-1));
		return true;
	}
	return false;
}

string Scenario::toJsonString()
{
	string baseStr = BaseNamedMaster::toJsonString();
	string jsonStr = StringUtils::format("{%s,%s}",
										 baseStr.c_str(),
										 jsLong(JS_MAP,getMapNo()).c_str()
										 );
	return jsonStr;
};

void Scenario::addRule(BaseConditionMaster *master)
{
	m_ScenarioRule.pushBack(master);
}
void Scenario::addUnit(BaseConditionMaster *master)
{
	m_ScenarioUnit.pushBack(master);
}

void Scenario::clearChild(BaseMaster::MASTERNO masterNo)
{
	switch(masterNo){
		case BaseMaster::SCENARIO_RULE_MASTER:
			m_ScenarioRule.clear();
			break;
		case BaseMaster::SCENARIO_UNIT_MASTER:
			m_ScenarioUnit.clear();
			break;
		default:
			break;
	}
}
BaseConditionMaster* Scenario::getUnit(long l)
{
	if(0 <= l && l < getUnitCount()){
		return m_ScenarioUnit.at(l);
	}
	return NULL;
	
};

