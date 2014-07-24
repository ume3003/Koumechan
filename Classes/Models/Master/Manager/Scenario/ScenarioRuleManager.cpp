//
//  ScenarioRuleManager.cpp
//  koumeChan
//
//  Created by 上野　彰三 on 2014/04/01.
//
//

#include "ScenarioRuleManager.h"
using namespace cocos2d;
using namespace std;

ScenarioRuleManager* ScenarioRuleManager::create(long version)
{
	ScenarioRuleManager* pRet = new ScenarioRuleManager();
	if(pRet && pRet->init(version)){
		pRet->autorelease();
	}
	else{
		CC_SAFE_DELETE(pRet);
		pRet = NULL;
	}
	return pRet;
}

string ScenarioRuleManager::getTableName()
{
	return string("ScenarioRule");
};

BaseMaster* ScenarioRuleManager::createMaster(Json* json)
{
	ScenarioRule* master = ScenarioRule::createWithJson(json);
//	log("ScenarioRule %ld %ld:%ld:%ld:%ld:%lld",
//		master->getMasterNo(),master->getParentNo(),master->getConditionNo(),
//		master->getKeyNo(),master->getKind(),master->getVal());
	return master;
}

ScenarioRule* ScenarioRuleManager::getScenarioRule(long no)
{
	return (ScenarioRule*)getMaster(no);
}


void ScenarioRuleManager::clearData()
{
	BaseMasterManager::clearData();
	
	BaseMasterManager* parent = KoumeChan::getInstance()->getMasterManager(BaseMaster::SCENARIO_MASTER);
	parent->clearChildData(BaseMaster::SCENARIO_RULE_MASTER);
	
	
}