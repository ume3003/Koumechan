//
//  BaseDamage.cpp
//  Koumechan
//
//  Created by 上野　彰三 on 2014/06/26.
//
//

#include "BaseDamage.h"
#include "JsonKeyString.h"
#include "KoumeChan.h"

using namespace cocos2d;
using namespace std;

BaseDamage::BaseDamage()
{
	
}

BaseDamage::~BaseDamage()
{
}

BaseDamage* BaseDamage::createWithJson(Json *json)
{
	BaseDamage* pRet = new BaseDamage();
	if(pRet && pRet->initWithJson(json)){
		pRet->autorelease();
	}
	else{
		CC_SAFE_DELETE(pRet);
		pRet = NULL;
	}
	return pRet;
}



string BaseDamage::toJsonString()
{
	string baseStr = BaseMaster::toJsonString();
	string jsonStr = StringUtils::format("{%s,%s,%s,%s,%s,%s}"	,baseStr.c_str(),
										 jsStr(JS_DESCRIPTION	,getDescription().asString().c_str()).c_str(),
										 jsInt(JS_OWN_HITPOINT	,getOwnHitPoint()).c_str(),
										 jsInt(JS_OWN_POWER		,getOwnPower()).c_str(),
										 jsInt(JS_ENEMY_HITPOINT,getEnemyHitPoint()).c_str(),
										 jsInt(JS_ENEMY_POWER	,getEnemyPower()).c_str()
										 );
	return jsonStr;
}

bool BaseDamage::initWithJson(Json* json)
{
	if(BaseMaster::initWithJson(json)){
		setDescription(		Value(Json_getString(json,JS_DESCRIPTION,"")));
		setOwnHitPoint(		KoumeChan::getInt(json, JS_OWN_HITPOINT, 0));
		setOwnPower(		KoumeChan::getInt(json, JS_OWN_POWER, 0));
		setEnemyHitPoint(	KoumeChan::getInt(json, JS_ENEMY_HITPOINT, 0));
		setEnemyPower(		KoumeChan::getInt(json, JS_ENEMY_POWER, 0));
		return true;
	}
	return false;
}
