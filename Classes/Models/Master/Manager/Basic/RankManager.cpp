//
//  RankManager.cpp
//  koumeChan
//
//  Created by 上野　彰三 on 2014/04/01.
//
//

#include "RankManager.h"
using namespace cocos2d;
using namespace std;

RankManager* RankManager::create(long version)
{
	RankManager* pRet = new RankManager();
	if(pRet && pRet->init(version)){
		pRet->autorelease();
	}
	else{
		CC_SAFE_DELETE(pRet);
		pRet = NULL;
	}
	return pRet;
}

string RankManager::getTableName()
{
	return string("Rank");
};

BaseMaster* RankManager::createMaster(Json* json)
{
	Rank* master = Rank::createWithJson(json);
	log("Rank %ld %s:%s:%s",master->getMasterNo(),master->getName().asString().c_str(),
		master->getDetail().asString().c_str(),master->getImage().asString().c_str());
	return master;
}

Rank* RankManager::getRank(long no)
{
	return (Rank*)getMaster(no);
}