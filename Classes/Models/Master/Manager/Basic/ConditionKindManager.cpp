//
//  ConditionKindManager.cpp
//  koumeChan
//
//  Created by 上野　彰三 on 2014/04/01.
//
//

#include "ConditionKindManager.h"
using namespace cocos2d;
using namespace std;

ConditionKindManager* ConditionKindManager::create(long version)
{
	ConditionKindManager* pRet = new ConditionKindManager();
	if(pRet && pRet->init(version)){
		pRet->autorelease();
	}
	else{
		CC_SAFE_DELETE(pRet);
		pRet = NULL;
	}
	return pRet;
}

string ConditionKindManager::getTableName()
{
	return string("ConditionKind");
};

BaseMaster* ConditionKindManager::createMaster(Json* json)
{
	ConditionKind* master = ConditionKind::createWithJson(json);
	log("ConditionKind %ld %s:%s:%s",master->getMasterNo(),master->getName().asString().c_str(),
		master->getDetail().asString().c_str(),master->getImage().asString().c_str());
	return master;
}

ConditionKind* ConditionKindManager::getConditionKind(long no)
{
	return (ConditionKind*)getMaster(no);
}