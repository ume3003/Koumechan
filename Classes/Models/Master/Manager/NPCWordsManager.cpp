//
//  NPCWordsManager.cpp
//  Koumechan
//
//  Created by 上野　彰三 on 2014/06/25.
//
//

#include "NPCWordsManager.h"
using namespace cocos2d;
using namespace std;

NPCWordsManager* NPCWordsManager::create(long version)
{
	NPCWordsManager* pRet = new NPCWordsManager();
	if(pRet && pRet->init(version)){
		pRet->autorelease();
	}
	else{
		CC_SAFE_DELETE(pRet);
		pRet = NULL;
	}
	return pRet;
}

string NPCWordsManager::getTableName()
{
	return string("NPCWORDS");
};

BaseMaster* NPCWordsManager::createMaster(Json* json)
{
	NPCWords* master = NPCWords::createWithJson(json);
//	log("NPCWords %ld %ld:%ld:%ld:%ld:%lld",
//		master->getMasterNo(),master->getParentNo(),master->getConditionNo(),
//		master->getKeyNo(),master->getKind(),master->getVal());
	return master;
}

NPCWords* NPCWordsManager::getNPCWords(long no)
{
	return (NPCWords*)getMaster(no);
}


void NPCWordsManager::clearData()
{
	BaseMasterManager::clearData();
	
	BaseMasterManager* parent = KoumeChan::getInstance()->getMasterManager(BaseMaster::NPC_MASTER);
	parent->clearChildData(BaseMaster::NPC_WORDS_MASTER);
	
	
}