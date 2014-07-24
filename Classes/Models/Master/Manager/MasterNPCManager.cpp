//
//  MasterNPCManager.cpp
//  Koumechan
//
//  Created by 上野　彰三 on 2014/06/23.
//
//

#include "MasterNPCManager.h"
using namespace cocos2d;
using namespace std;

MasterNPCManager* MasterNPCManager::create(long version)
{
	MasterNPCManager* pRet = new MasterNPCManager();
	if(pRet && pRet->init(version)){
		pRet->autorelease();
	}
	else{
		CC_SAFE_DELETE(pRet);
		pRet = NULL;
	}
	return pRet;
}

string MasterNPCManager::getTableName()
{
	return string("NPC");
};

BaseMaster* MasterNPCManager::createMaster(Json* json)
{
	MasterNPC* master = MasterNPC::createWithJson(json);
//	log("NPC %ld %s:%s:%s:%ld %ld",master->getMasterNo(),master->getName().asString().c_str(),
//		master->getDetail().asString().c_str(),master->getImage().asString().c_str(),
//		((MasterNPC*)master)->getHP(),((MasterNPC*)master)->getLevel());
	return master;
}

MasterNPC* MasterNPCManager::getMasterNPC(long no)
{
	return (MasterNPC*)getMaster(no);
}

