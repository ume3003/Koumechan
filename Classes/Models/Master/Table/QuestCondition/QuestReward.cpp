//
//  QuestReward.cpp
//  koumeChan
//
//  Created by 上野　彰三 on 2014/04/01.
//
//

#include "QuestReward.h"
#include "JsonKeyString.h"
#include "KoumeChan.h"
#include "MinorQuest.h"

using namespace cocos2d;
using namespace std;

QuestReward::QuestReward()
{
	
}

QuestReward::~QuestReward()
{
}

QuestReward* QuestReward::createWithJson(Json *json)
{
	QuestReward* pRet = new QuestReward();
	if(pRet && pRet->initWithJson(json)){
		pRet->autorelease();
	}
	else{
		CC_SAFE_DELETE(pRet);
		pRet = NULL;
	}
	return pRet;
}



string QuestReward::toJsonString()
{
	string baseStr = BaseConditionMaster::toJsonString();
	string jsonStr = StringUtils::format("{%s}",baseStr.c_str());
	return jsonStr;
}

void QuestReward::registerToParent()
{
	MinorQuest* parent = KoumeChan::getInstance()->getMinorQuestMaster(getParentNo());
	if(parent){
		parent->addReward(this);
	}
	
}