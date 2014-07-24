//
//  MajorQuestManager.cpp
//  koumeChan
//
//  Created by 上野　彰三 on 2014/03/25.
//
//

#include "MajorQuestManager.h"
#include "DirectionManager.h"

using namespace cocos2d;
using namespace std;

MajorQuestManager* MajorQuestManager::create(long version)
{
	MajorQuestManager* pRet = new MajorQuestManager();
	if(pRet && pRet->init(version)){
		pRet->autorelease();
	}
	else{
		CC_SAFE_DELETE(pRet);
		pRet = NULL;
	}
	return pRet;
}

string MajorQuestManager::getTableName()
{
	return string("MajorQuest");
};

BaseMaster* MajorQuestManager::createMaster(Json* json)
{
	MajorQuest* master = MajorQuest::createWithJson(json);
//	log("MajorQuest %ld %s:%s:%s",master->getMasterNo(),master->getName().asString().c_str(),
//		master->getDetail().asString().c_str(),master->getImage().asString().c_str());
	return master;
}

MajorQuest* MajorQuestManager::getMajorQuest(long no)
{
	return (MajorQuest*)getMaster(no);
}

void MajorQuestManager::clearData()
{
	BaseMasterManager::clearData();
	BaseMasterManager* parent = KoumeChan::getInstance()->getMasterManager(BaseMaster::DIRECT_MASTER);
	parent->clearChildData(BaseMaster::MAJOR_QUEST_MASTER);
	
}