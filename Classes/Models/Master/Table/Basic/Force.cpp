//
//  Force.cpp
//  koumeChan
//
//  Created by 上野　彰三 on 2014/04/01.
//
//

#include "Force.h"
#include "JsonKeyString.h"
#include "KoumeChan.h"

using namespace cocos2d;
using namespace std;

Force::Force()
{
	
}

Force::~Force()
{
}

Force* Force::createWithJson(Json *json)
{
	Force* pRet = new Force();
	if(pRet && pRet->initWithJson(json)){
		pRet->autorelease();
	}
	else{
		CC_SAFE_DELETE(pRet);
		pRet = NULL;
	}
	return pRet;
}



string Force::toJsonString()
{
	string baseStr = BaseNamedMaster::toJsonString();
	string jsonStr = StringUtils::format("{%s,%s}", baseStr.c_str(),
					 jsInt(JS_ENEMY_FORCE,getEnemyForceNo()).c_str());
	return jsonStr;
}

bool Force::initWithJson(Json* json)
{
	if(BaseNamedMaster::initWithJson(json)){
		setEnemyForceNo(KoumeChan::getInt(json, JS_ENEMY_FORCE, 0));
		return true;
	}
	return false;
}
