//
//  CharacterColumn.cpp
//  koumeChan
//
//  Created by 上野　彰三 on 2014/04/01.
//
//

#include "CharacterColumn.h"
#include "JsonKeyString.h"
#include "KoumeChan.h"

using namespace cocos2d;
using namespace std;

CharacterColumn::CharacterColumn()
{
	
}

CharacterColumn::~CharacterColumn()
{
}

CharacterColumn* CharacterColumn::createWithJson(Json *json)
{
	CharacterColumn* pRet = new CharacterColumn();
	if(pRet && pRet->initWithJson(json)){
		pRet->autorelease();
	}
	else{
		CC_SAFE_DELETE(pRet);
		pRet = NULL;
	}
	return pRet;
}



string CharacterColumn::toJsonString()
{
	string baseStr = BaseNamedMaster::toJsonString();
	string jsonStr = StringUtils::format("{%s}",baseStr.c_str());
	return jsonStr;
}

