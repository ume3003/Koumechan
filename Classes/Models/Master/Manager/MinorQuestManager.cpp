//
//  MinorQuestManager.cpp
//  koumeChan
//
//  Created by 上野　彰三 on 2014/03/25.
//
//

#include "MinorQuestManager.h"

using namespace cocos2d;
using namespace std;

MinorQuestManager* MinorQuestManager::create(long version)
{
	MinorQuestManager* pRet = new MinorQuestManager();
	if(pRet && pRet->init(version)){
		pRet->autorelease();
	}
	else{
		CC_SAFE_DELETE(pRet);
		pRet = NULL;
	}
	return pRet;
}

string MinorQuestManager::getTableName()
{
	return string("MinorQuest");
};

BaseMaster* MinorQuestManager::createMaster(Json* json)
{
	MinorQuest* master = MinorQuest::createWithJson(json);
//	log("MinorQuest %ld %s:%s:%s",master->getMasterNo(),master->getName().asString().c_str(),
//		master->getDetail().asString().c_str(),master->getImage().asString().c_str());
	return master;
}

MinorQuest* MinorQuestManager::getMinorQuest(long no)
{
	return (MinorQuest*)getMaster(no);
}

void MinorQuestManager::clearData()
{
	BaseMasterManager::clearData();
	
	BaseMasterManager* parent = KoumeChan::getInstance()->getMasterManager(BaseMaster::DIRECT_MASTER);
	parent->clearChildData(BaseMaster::MINOR_QUEST_MASTER);
	
	parent = KoumeChan::getInstance()->getMasterManager(BaseMaster::MAJOR_QUEST_MASTER);
	parent->clearChildData(BaseMaster::MINOR_QUEST_MASTER);
	
}