//
//  ScenarioUnitManager.cpp
//  koumeChan
//
//  Created by 上野　彰三 on 2014/04/01.
//
//

#include "ScenarioUnitManager.h"
using namespace cocos2d;
using namespace std;

ScenarioUnitManager* ScenarioUnitManager::create(long version)
{
	ScenarioUnitManager* pRet = new ScenarioUnitManager();
	if(pRet && pRet->init(version)){
		pRet->autorelease();
	}
	else{
		CC_SAFE_DELETE(pRet);
		pRet = NULL;
	}
	return pRet;
}

string ScenarioUnitManager::getTableName()
{
	return string("ScenarioUnit");
};

BaseMaster* ScenarioUnitManager::createMaster(Json* json)
{
	ScenarioUnit* master = ScenarioUnit::createWithJson(json);
//	log("ScenarioUnit %ld %ld:%ld:%ld:%ld:%lld",
//		master->getMasterNo(),master->getParentNo(),master->getConditionNo(),
//		master->getKeyNo(),master->getKind(),master->getVal());
	return master;
}

ScenarioUnit* ScenarioUnitManager::getScenarioUnit(long no)
{
	return (ScenarioUnit*)getMaster(no);
}


void ScenarioUnitManager::clearData()
{
	BaseMasterManager::clearData();
	
	BaseMasterManager* parent = KoumeChan::getInstance()->getMasterManager(BaseMaster::SCENARIO_MASTER);
	parent->clearChildData(BaseMaster::SCENARIO_UNIT_MASTER);
	
	
}