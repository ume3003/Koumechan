//
//  ConditionKind.cpp
//  koumeChan
//
//  Created by 上野　彰三 on 2014/04/01.
//
//

#include "ConditionKind.h"
#include "JsonKeyString.h"
#include "KoumeChan.h"

using namespace cocos2d;
using namespace std;

ConditionKind::ConditionKind()
{
	
}

ConditionKind::~ConditionKind()
{
}

ConditionKind* ConditionKind::createWithJson(Json *json)
{
	ConditionKind* pRet = new ConditionKind();
	if(pRet && pRet->initWithJson(json)){
		pRet->autorelease();
	}
	else{
		CC_SAFE_DELETE(pRet);
		pRet = NULL;
	}
	return pRet;
}



string ConditionKind::toJsonString()
{
	string baseStr = BaseNamedMaster::toJsonString();
	string jsonStr = StringUtils::format("{%s}",baseStr.c_str());
	return jsonStr;
}

