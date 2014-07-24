//
//  MasterUnitSkillManager.cpp
//  koumeChan
//
//  Created by 上野　彰三 on 2014/04/01.
//
//

#include "MasterUnitSkillManager.h"
using namespace cocos2d;
using namespace std;

MasterUnitSkillManager* MasterUnitSkillManager::create(long version)
{
	MasterUnitSkillManager* pRet = new MasterUnitSkillManager();
	if(pRet && pRet->init(version)){
		pRet->autorelease();
	}
	else{
		CC_SAFE_DELETE(pRet);
		pRet = NULL;
	}
	return pRet;
}

string MasterUnitSkillManager::getTableName()
{
	return string("MasterUnitSkill");
};

BaseMaster* MasterUnitSkillManager::createMaster(Json* json)
{
	MasterUnitSkill* master = MasterUnitSkill::createWithJson(json);
//	log("UnitSkill %ld %ld:%ld:%ld:%ld:%lld",
//		master->getMasterNo(),master->getParentNo(),master->getConditionNo(),
//		master->getKeyNo(),master->getKind(),master->getVal());

	return master;
}

MasterUnitSkill* MasterUnitSkillManager::getMasterUnitSkill(long no)
{
	return (MasterUnitSkill*)getMaster(no);
}

void MasterUnitSkillManager::clearData()
{
	BaseMasterManager::clearData();
	BaseMasterManager* parent = KoumeChan::getInstance()->getMasterManager(BaseMaster::UNIT_MASTER);
	parent->clearChildData(BaseMaster::UNIT_SKILL_MASTER);
	
}