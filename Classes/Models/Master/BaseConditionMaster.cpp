//
//  BaseConditionMaster.cpp
//  koumeChan
//
//  Created by 上野　彰三 on 2014/04/01.
//
//

#include "BaseConditionMaster.h"
#include "KCDef.h"
#include "KoumeChan.h"
#include "JsonKeyString.h"

using namespace cocos2d;
using namespace std;

bool BaseConditionMaster::initWithJson(Json* json)
{
	if(BaseMaster::initWithJson(json)){
		setParentNo(	KoumeChan::getLong(json,JS_PARENT,-1		));
		setConditionNo(	KoumeChan::getLong(json,JS_CONDITION,-1	));
		setKind(		KoumeChan::getLong(json,JS_KIND,-1		));
		setKeyNo(		KoumeChan::getLong(json,JS_KEY_NO,-1		));
		setVal(			KoumeChan::getLLong(json,JS_VALUE,-1	));
		return true;
	}
	return false;
}

string BaseConditionMaster::toJsonString()
{
	string baseStr = BaseMaster::toJsonString();
	string jsonStr = StringUtils::format("%s,%s,%s,%s,%s,%s",baseStr.c_str(),
										 jsLong(JS_PARENT	,getParentNo()).c_str(),
										 jsLong(JS_CONDITION,getConditionNo()).c_str(),
										 jsLong(JS_KIND		,getKind()).c_str(),
										 jsLong(JS_KEY_NO	,getKeyNo()).c_str(),
										 jsLLong(JS_VALUE	,getVal()).c_str()
										 );
	return jsonStr;
}