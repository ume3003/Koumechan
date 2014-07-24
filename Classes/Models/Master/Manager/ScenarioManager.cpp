//
//  ScenarioManager.cpp
//  koumeChan
//
//  Created by 上野　彰三 on 2014/04/01.
//
//

#include "ScenarioManager.h"
using namespace cocos2d;
using namespace std;

ScenarioManager* ScenarioManager::create(long version)
{
	ScenarioManager* pRet = new ScenarioManager();
	if(pRet && pRet->init(version)){
		pRet->autorelease();
	}
	else{
		CC_SAFE_DELETE(pRet);
		pRet = NULL;
	}
	return pRet;
}

string ScenarioManager::getTableName()
{
	return string("Scenario");
};

BaseMaster* ScenarioManager::createMaster(Json* json)
{
	Scenario* master = Scenario::createWithJson(json);
//	log("Scenario %ld %s:%s:%s",master->getMasterNo(),master->getName().asString().c_str(),
//		master->getDetail().asString().c_str(),master->getImage().asString().c_str());
	return master;
}

Scenario* ScenarioManager::getScenario(long no)
{
	return (Scenario*)getMaster(no);
}

void ScenarioManager::clearData()
{
	BaseMasterManager::clearData();
	BaseMasterManager* parent = KoumeChan::getInstance()->getMasterManager(BaseMaster::DIRECT_MASTER);
	parent->clearChildData(BaseMaster::SCENARIO_MASTER);
	
}