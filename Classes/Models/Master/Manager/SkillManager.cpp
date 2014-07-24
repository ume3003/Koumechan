//
//  SkillManager.cpp
//  koumeChan
//
//  Created by 上野　彰三 on 2014/04/01.
//
//

#include "SkillManager.h"
using namespace cocos2d;
using namespace std;

SkillManager* SkillManager::create(long version)
{
	SkillManager* pRet = new SkillManager();
	if(pRet && pRet->init(version)){
		pRet->autorelease();
	}
	else{
		CC_SAFE_DELETE(pRet);
		pRet = NULL;
	}
	return pRet;
}

string SkillManager::getTableName()
{
	return string("Skill");
};

BaseMaster* SkillManager::createMaster(Json* json)
{
	Skill* master = Skill::createWithJson(json);
//	log("Skill %ld %s:%s:%s",master->getMasterNo(),master->getName().asString().c_str(),
//		master->getDetail().asString().c_str(),master->getImage().asString().c_str());
	return master;
}

Skill* SkillManager::getSkill(long no)
{
	return (Skill*)getMaster(no);
}