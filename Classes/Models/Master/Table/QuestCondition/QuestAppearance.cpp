//
//  QuestAppearance.cpp
//  koumeChan
//
//  Created by 上野　彰三 on 2014/04/01.
//
//

#include "QuestAppearance.h"
#include "JsonKeyString.h"
#include "KoumeChan.h"
#include "MinorQuest.h"

using namespace cocos2d;
using namespace std;

QuestAppearance::QuestAppearance()
{
	
}

QuestAppearance::~QuestAppearance()
{
}

QuestAppearance* QuestAppearance::createWithJson(Json *json)
{
	QuestAppearance* pRet = new QuestAppearance();
	if(pRet && pRet->initWithJson(json)){
		pRet->autorelease();
	}
	else{
		CC_SAFE_DELETE(pRet);
		pRet = NULL;
	}
	return pRet;
}



string QuestAppearance::toJsonString()
{
	string baseStr = BaseConditionMaster::toJsonString();
	string jsonStr = StringUtils::format("{%s}",baseStr.c_str());
	return jsonStr;
}

void QuestAppearance::registerToParent()
{
	MinorQuest* parent = KoumeChan::getInstance()->getMinorQuestMaster(getParentNo());
	if(parent){
		parent->addAppearance(this);
	}
	
}