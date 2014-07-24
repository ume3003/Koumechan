//
//  QuestClear.cpp
//  koumeChan
//
//  Created by 上野　彰三 on 2014/04/01.
//
//

#include "QuestClear.h"
#include "JsonKeyString.h"
#include "KoumeChan.h"
#include "MinorQuest.h"

using namespace cocos2d;
using namespace std;

QuestClear::QuestClear()
{
	
}

QuestClear::~QuestClear()
{
}

QuestClear* QuestClear::createWithJson(Json *json)
{
	QuestClear* pRet = new QuestClear();
	if(pRet && pRet->initWithJson(json)){
		pRet->autorelease();
	}
	else{
		CC_SAFE_DELETE(pRet);
		pRet = NULL;
	}
	return pRet;
}



string QuestClear::toJsonString()
{
	string baseStr = BaseConditionMaster::toJsonString();
	string jsonStr = StringUtils::format("{%s}",baseStr.c_str());
	return jsonStr;
}

void QuestClear::registerToParent()
{
	MinorQuest* parent = KoumeChan::getInstance()->getMinorQuestMaster(getParentNo());
	if(parent){
		parent->addClear(this);
	}
	
}