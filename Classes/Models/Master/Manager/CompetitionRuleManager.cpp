//
//  CompetitionRuleManager.cpp
//  koumeChan
//
//  Created by 上野　彰三 on 2014/04/01.
//
//

#include "CompetitionRuleManager.h"
using namespace cocos2d;
using namespace std;

CompetitionRuleManager* CompetitionRuleManager::create(long version)
{
	CompetitionRuleManager* pRet = new CompetitionRuleManager();
	if(pRet && pRet->init(version)){
		pRet->autorelease();
	}
	else{
		CC_SAFE_DELETE(pRet);
		pRet = NULL;
	}
	return pRet;
}

string CompetitionRuleManager::getTableName()
{
	return string("CompetitionRule");
};

BaseMaster* CompetitionRuleManager::createMaster(Json* json)
{
	CompetitionRule* master = CompetitionRule::createWithJson(json);
//	log("CompetitionRule %ld %s:%s:%s",master->getMasterNo(),master->getName().asString().c_str(),
//		master->getDetail().asString().c_str(),master->getImage().asString().c_str());
	return master;
}

CompetitionRule* CompetitionRuleManager::getCompetitionRule(long no)
{
	return (CompetitionRule*)getMaster(no);
}