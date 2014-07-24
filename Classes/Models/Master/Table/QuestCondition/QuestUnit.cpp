//
//  QuestUnit.cpp
//  koumeChan
//
//  Created by 上野　彰三 on 2014/04/01.
//
//

#include "QuestUnit.h"
#include "JsonKeyString.h"
#include "KoumeChan.h"
#include "MinorQuest.h"

using namespace cocos2d;
using namespace std;

QuestUnit::QuestUnit()
{
	
}

QuestUnit::~QuestUnit()
{
}

QuestUnit* QuestUnit::createWithJson(Json *json)
{
	QuestUnit* pRet = new QuestUnit();
	if(pRet && pRet->initWithJson(json)){
		pRet->autorelease();
	}
	else{
		CC_SAFE_DELETE(pRet);
		pRet = NULL;
	}
	return pRet;
}



string QuestUnit::toJsonString()
{
	string baseStr = BaseConditionMaster::toJsonString();
	string jsonStr = StringUtils::format("{%s}",baseStr.c_str());
	return jsonStr;
}

void QuestUnit::registerToParent()
{
	MinorQuest* parent = KoumeChan::getInstance()->getMinorQuestMaster(getParentNo());
	if(parent){
		parent->addUnit(this);
	}
	
}