//
//  QuestAppearanceManager.cpp
//  koumeChan
//
//  Created by 上野　彰三 on 2014/04/01.
//
//

#include "QuestAppearanceManager.h"
using namespace cocos2d;
using namespace std;

QuestAppearanceManager* QuestAppearanceManager::create(long version)
{
	QuestAppearanceManager* pRet = new QuestAppearanceManager();
	if(pRet && pRet->init(version)){
		pRet->autorelease();
	}
	else{
		CC_SAFE_DELETE(pRet);
		pRet = NULL;
	}
	return pRet;
}

string QuestAppearanceManager::getTableName()
{
	return string("QuestAppearance");
};

BaseMaster* QuestAppearanceManager::createMaster(Json* json)
{
	QuestAppearance* master = QuestAppearance::createWithJson(json);
//	log("QuestAppearance %ld %ld:%ld:%ld:%ld:%lld",
//		master->getMasterNo(),master->getParentNo(),master->getConditionNo(),
//		master->getKeyNo(),master->getKind(),master->getVal());
	return master;
}

QuestAppearance* QuestAppearanceManager::getQuestAppearance(long no)
{
	return (QuestAppearance*)getMaster(no);
}

void QuestAppearanceManager::clearData()
{
	BaseMasterManager::clearData();
	
	BaseMasterManager* parent = KoumeChan::getInstance()->getMasterManager(BaseMaster::MINOR_QUEST_MASTER);
	parent->clearChildData(BaseMaster::QUEST_APPEARANCE_MASTER);
	
	
}