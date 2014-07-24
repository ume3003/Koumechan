//
//  QuestUnitManager.cpp
//  koumeChan
//
//  Created by 上野　彰三 on 2014/04/01.
//
//

#include "QuestUnitManager.h"
using namespace cocos2d;
using namespace std;

QuestUnitManager* QuestUnitManager::create(long version)
{
	QuestUnitManager* pRet = new QuestUnitManager();
	if(pRet && pRet->init(version)){
		pRet->autorelease();
	}
	else{
		CC_SAFE_DELETE(pRet);
		pRet = NULL;
	}
	return pRet;
}

string QuestUnitManager::getTableName()
{
	return string("QuestUnit");
};

BaseMaster* QuestUnitManager::createMaster(Json* json)
{
	QuestUnit* master = QuestUnit::createWithJson(json);
//	log("QuestUnit %ld %ld:%ld:%ld:%ld:%lld",
//		master->getMasterNo(),master->getParentNo(),master->getConditionNo(),
//		master->getKeyNo(),master->getKind(),master->getVal());
	return master;
}

QuestUnit* QuestUnitManager::getQuestUnit(long no)
{
	return (QuestUnit*)getMaster(no);
}


void QuestUnitManager::clearData()
{
	BaseMasterManager::clearData();
	
	BaseMasterManager* parent = KoumeChan::getInstance()->getMasterManager(BaseMaster::MINOR_QUEST_MASTER);
	parent->clearChildData(BaseMaster::QUEST_UNIT_MASTER);
	
	
}