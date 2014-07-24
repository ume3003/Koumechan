//
//  MasterUnitManager.cpp
//  koumeChan
//
//  Created by 上野　彰三 on 2014/04/01.
//
//

#include "MasterUnitManager.h"

using namespace cocos2d;
using namespace std;

MasterUnitManager* MasterUnitManager::create(long version)
{
	MasterUnitManager* pRet = new MasterUnitManager();
	if(pRet && pRet->init(version)){
		pRet->autorelease();
	}
	else{
		CC_SAFE_DELETE(pRet);
		pRet = NULL;
	}
	return pRet;
}

string MasterUnitManager::getTableName()
{
	return string("MasterUnit");
};

BaseMaster* MasterUnitManager::createMaster(Json* json)
{
	MasterUnit* master = MasterUnit::createWithJson(json);
//	log("MasterUnit %ld %s:%s:%s",master->getMasterNo(),master->getName().asString().c_str(),
//		master->getDetail().asString().c_str(),master->getImage().asString().c_str());
	return master;
}

MasterUnit* MasterUnitManager::getMasterUnit(long no)
{
	return (MasterUnit*)getMaster(no);
}

