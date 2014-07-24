//
//  BaseDamageManager.cpp
//  Koumechan
//
//  Created by 上野　彰三 on 2014/06/26.
//
//

#include "BaseDamageManager.h"

using namespace cocos2d;
using namespace std;

BaseDamageManager* BaseDamageManager::create(long version)
{
	BaseDamageManager* pRet = new BaseDamageManager();
	if(pRet && pRet->init(version)){
		pRet->autorelease();
	}
	else{
		CC_SAFE_DELETE(pRet);
		pRet = NULL;
	}
	return pRet;
}

string BaseDamageManager::getTableName()
{
	return string("BaseDamage");
};

BaseMaster* BaseDamageManager::createMaster(Json* json)
{
	BaseDamage* master = BaseDamage::createWithJson(json);
//	log("BaseDamage %ld %s:%d:%d:%d:%d",
//		master->getMasterNo(),
//		master->getDescription().asString().c_str(),
//		master->getOwnHitPoint(),
//		master->getOwnPower(),
//		master->getEnemyHitPoint(),
//		master->getEnemyPower());
	return master;
}

BaseDamage* BaseDamageManager::getBaseDamage(BaseDamage::BD_TYPE no)
{
	return (BaseDamage*)getMaster(no);
}