//
//  MasterMapManager.cpp
//  koumeChan
//
//  Created by 上野　彰三 on 2014/04/01.
//
//

#include "MasterMapManager.h"

using namespace cocos2d;
using namespace std;

MasterMapManager* MasterMapManager::create(long version)
{
	MasterMapManager* pRet = new MasterMapManager();
	if(pRet && pRet->init(version)){
		pRet->autorelease();
	}
	else{
		CC_SAFE_DELETE(pRet);
		pRet = NULL;
	}
	return pRet;
}

string MasterMapManager::getTableName()
{
	return string("MasterMap");
};

BaseMaster* MasterMapManager::createMaster(Json* json)
{
	MasterMap* master = MasterMap::createWithJson(json);
//	log("MasterMap %ld %s:%s:%s",master->getMasterNo(),master->getName().asString().c_str(),
//		master->getDetail().asString().c_str(),master->getImage().asString().c_str());
	return master;
}

MasterMap* MasterMapManager::getMasterMap(long no)
{
	return (MasterMap*)getMaster(no);
}