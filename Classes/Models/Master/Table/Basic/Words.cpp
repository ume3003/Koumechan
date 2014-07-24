//
//  Wordd.cpp
//  Koumechan
//
//  Created by 上野　彰三 on 2014/06/25.
//
//

#include "Words.h"

#include "JsonKeyString.h"
#include "KoumeChan.h"

using namespace cocos2d;
using namespace std;

Words::Words()
{
	
}

Words::~Words()
{
}

Words* Words::createWithJson(Json *json)
{
	Words* pRet = new Words();
	if(pRet && pRet->initWithJson(json)){
		pRet->autorelease();
	}
	else{
		CC_SAFE_DELETE(pRet);
		pRet = NULL;
	}
	return pRet;
}



string Words::toJsonString()
{
	string baseStr = BaseNamedMaster::toJsonString();
	string jsonStr = StringUtils::format("{%s}",baseStr.c_str());
	return jsonStr;
}

