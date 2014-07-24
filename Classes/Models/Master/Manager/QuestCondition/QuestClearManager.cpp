//
//  QuestClearManager.cpp
//  koumeChan
//
//  Created by 上野　彰三 on 2014/04/01.
//
//

#include "QuestClearManager.h"
using namespace cocos2d;
using namespace std;

QuestClearManager* QuestClearManager::create(long version)
{
	QuestClearManager* pRet = new QuestClearManager();
	if(pRet && pRet->init(version)){
		pRet->autorelease();
	}
	else{
		CC_SAFE_DELETE(pRet);
		pRet = NULL;
	}
	return pRet;
}

string QuestClearManager::getTableName()
{
	return string("QuestClear");
};

BaseMaster* QuestClearManager::createMaster(Json* json)
{
	QuestClear* master = QuestClear::createWithJson(json);
//	log("QuestClear %ld %ld:%ld:%ld:%ld:%lld",
//		master->getMasterNo(),master->getParentNo(),master->getConditionNo(),
//		master->getKeyNo(),master->getKind(),master->getVal());
	return master;
}

QuestClear* QuestClearManager::getQuestClear(long no)
{
	return (QuestClear*)getMaster(no);
}

void QuestClearManager::clearData()
{
	BaseMasterManager::clearData();
	
	BaseMasterManager* parent = KoumeChan::getInstance()->getMasterManager(BaseMaster::MINOR_QUEST_MASTER);
	parent->clearChildData(BaseMaster::QUEST_CLEAR_MASTER);
	
	
}