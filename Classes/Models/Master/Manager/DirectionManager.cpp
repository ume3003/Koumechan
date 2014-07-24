//
//  DirectionManager.cpp
//  koumeChan
//
//  Created by 上野　彰三 on 2014/03/17.
//
//

#include "DirectionManager.h"

using namespace cocos2d;
using namespace std;

DirectionManager* DirectionManager::create(long version)
{
	DirectionManager* pRet = new DirectionManager();
	if(pRet && pRet->init(version)){
		pRet->autorelease();
	}
	else{
		CC_SAFE_DELETE(pRet);
		pRet = NULL;
	}
	return pRet;
}

string DirectionManager::getTableName()
{
	return string("Director");
};

BaseMaster* DirectionManager::createMaster(Json* json)
{
	DirectionQuest* master = DirectionQuest::createWithJson(json);
//	log("Direction %ld %s:%s:%s",master->getMasterNo(),master->getName().asString().c_str(),
//		master->getDetail().asString().c_str(),master->getImage().asString().c_str());
	return master;
}

DirectionQuest* DirectionManager::getDirection(long no)
{
	return (DirectionQuest*)getMaster(no);
}

