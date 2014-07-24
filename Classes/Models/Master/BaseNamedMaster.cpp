//
//  BaseNamedMaster.cpp
//  koumeChan
//
//  Created by 上野　彰三 on 2014/03/17.
//
//

#include "BaseNamedMaster.h"
#include "KCDef.h"
#include "JsonKeyString.h"

using namespace cocos2d;
using namespace std;

bool BaseNamedMaster::initWithJson(Json* json)
{
	if(BaseMaster::initWithJson(json)){
		setName(Value(Json_getString(json,JS_NAME,"")));
		setDetail(Value(Json_getString(json,JS_DETAIL,"")));
		setImage(Value(Json_getString(json,JS_IMAGE,"")));
		return true;
	}
	return false;
}

string BaseNamedMaster::toJsonString()
{
	string baseStr = BaseMaster::toJsonString();
	string jsonStr = StringUtils::format("%s,%s,%s,%s",baseStr.c_str(),
					jsStr(JS_NAME,getName().asString().c_str()).c_str(),
					jsStr(JS_DETAIL,getDetail().asString().c_str()).c_str(),
					jsStr(JS_IMAGE,getImage().asString().c_str()).c_str()
					);
	return jsonStr;
}