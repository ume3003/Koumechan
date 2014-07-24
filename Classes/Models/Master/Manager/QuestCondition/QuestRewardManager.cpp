//
//  QuestRewardManager.cpp
//  koumeChan
//
//  Created by 上野　彰三 on 2014/04/01.
//
//

#include "QuestRewardManager.h"
using namespace cocos2d;
using namespace std;

QuestRewardManager* QuestRewardManager::create(long version)
{
	QuestRewardManager* pRet = new QuestRewardManager();
	if(pRet && pRet->init(version)){
		pRet->autorelease();
	}
	else{
		CC_SAFE_DELETE(pRet);
		pRet = NULL;
	}
	return pRet;
}

string QuestRewardManager::getTableName()
{
	return string("QuestReward");
};

BaseMaster* QuestRewardManager::createMaster(Json* json)
{
	QuestReward* master = QuestReward::createWithJson(json);
//	log("QuestReward %ld %ld:%ld:%ld:%ld:%lld",
//		master->getMasterNo(),master->getParentNo(),master->getConditionNo(),
//		master->getKeyNo(),master->getKind(),master->getVal());
	return master;
}

QuestReward* QuestRewardManager::getQuestReward(long no)
{
	return (QuestReward*)getMaster(no);
}


void QuestRewardManager::clearData()
{
	BaseMasterManager::clearData();
	
	BaseMasterManager* parent = KoumeChan::getInstance()->getMasterManager(BaseMaster::MINOR_QUEST_MASTER);
	parent->clearChildData(BaseMaster::QUEST_REWARD_MASTER);
	
	
}