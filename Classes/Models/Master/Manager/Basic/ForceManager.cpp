//
//  ForceManager.cpp
//  koumeChan
//
//  Created by 上野　彰三 on 2014/04/01.
//
//

#include "ForceManager.h"
using namespace cocos2d;
using namespace std;

ForceManager* ForceManager::create(long version)
{
	ForceManager* pRet = new ForceManager();
	if(pRet && pRet->init(version)){
		pRet->autorelease();
	}
	else{
		CC_SAFE_DELETE(pRet);
		pRet = NULL;
	}
	return pRet;
}

string ForceManager::getTableName()
{
	return string("Force");
};

BaseMaster* ForceManager::createMaster(Json* json)
{
	Force* master = Force::createWithJson(json);
	log("Force %ld %s:%s:%s",master->getMasterNo(),master->getName().asString().c_str(),
		master->getDetail().asString().c_str(),master->getImage().asString().c_str());
	return master;
}

Force* ForceManager::getForce(long no)
{
	return (Force*)getMaster(no);
}