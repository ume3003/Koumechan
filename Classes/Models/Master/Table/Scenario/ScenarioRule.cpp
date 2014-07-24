//
//  ScenarioRule.cpp
//  koumeChan
//
//  Created by 上野　彰三 on 2014/04/01.
//
//

#include "ScenarioRule.h"
#include "JsonKeyString.h"
#include "KoumeChan.h"
#include "Scenario.h"

using namespace cocos2d;
using namespace std;

ScenarioRule::ScenarioRule()
{
	
}

ScenarioRule::~ScenarioRule()
{
}

ScenarioRule* ScenarioRule::createWithJson(Json *json)
{
	ScenarioRule* pRet = new ScenarioRule();
	if(pRet && pRet->initWithJson(json)){
		pRet->autorelease();
	}
	else{
		CC_SAFE_DELETE(pRet);
		pRet = NULL;
	}
	return pRet;
}



string ScenarioRule::toJsonString()
{
	string baseStr = BaseConditionMaster::toJsonString();
	string jsonStr = StringUtils::format("{%s}",baseStr.c_str());
	return jsonStr;
}

void ScenarioRule::registerToParent()
{
	Scenario* parent = KoumeChan::getInstance()->getScenarioMaster(getParentNo());
	if(parent){
		parent->addRule(this);
	}
	
}