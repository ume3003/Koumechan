//
//  ScenarioUnit.cpp
//  koumeChan
//
//  Created by 上野　彰三 on 2014/04/01.
//
//

#include "ScenarioUnit.h"
#include "JsonKeyString.h"
#include "KoumeChan.h"
#include "Scenario.h"

using namespace cocos2d;
using namespace std;

ScenarioUnit::ScenarioUnit()
{
	
}

ScenarioUnit::~ScenarioUnit()
{
}

ScenarioUnit* ScenarioUnit::createWithJson(Json *json)
{
	ScenarioUnit* pRet = new ScenarioUnit();
	if(pRet && pRet->initWithJson(json)){
		pRet->autorelease();
	}
	else{
		CC_SAFE_DELETE(pRet);
		pRet = NULL;
	}
	return pRet;
}



string ScenarioUnit::toJsonString()
{
	string baseStr = BaseConditionMaster::toJsonString();
	string jsonStr = StringUtils::format("{%s}",baseStr.c_str());
	return jsonStr;
}

void ScenarioUnit::registerToParent()
{
	Scenario* parent = KoumeChan::getInstance()->getScenarioMaster(getParentNo());
	if(parent){
		parent->addUnit(this);
	}
	
}