//
//  MasterUnitSkill.cpp
//  koumeChan
//
//  Created by 上野　彰三 on 2014/04/01.
//
//

#include "MasterUnitSkill.h"
#include "JsonKeyString.h"
#include "KoumeChan.h"
#include "MinorQuest.h"

using namespace cocos2d;
using namespace std;

MasterUnitSkill::MasterUnitSkill()
{
	
}

MasterUnitSkill::~MasterUnitSkill()
{
}

MasterUnitSkill* MasterUnitSkill::createWithJson(Json *json)
{
	MasterUnitSkill* pRet = new MasterUnitSkill();
	if(pRet && pRet->initWithJson(json)){
		pRet->autorelease();
	}
	else{
		CC_SAFE_DELETE(pRet);
		pRet = NULL;
	}
	return pRet;
}



string MasterUnitSkill::toJsonString()
{
	string baseStr = BaseConditionMaster::toJsonString();
	string jsonStr = StringUtils::format("{%s}",baseStr.c_str());
	return jsonStr;
}

void MasterUnitSkill::registerToParent()
{
	MasterUnit* parent = KoumeChan::getInstance()->getUnitMaster(getParentNo());
	if(parent){
		parent->addSkill(this);
	}
	
}