//
//  Friends.cpp
//  Koumechan
//
//  Created by 上野　彰三 on 2014/07/08.
//
//

#include "Friends.h"
#include "JsonKeyString.h"
#include "KoumeChan.h"
using namespace cocos2d;
using namespace std;

Friends::Friends()
{
	setId(-1);
	
}
Friends* Friends::createWithJson(Json *json)
{
	Friends* pRet = new Friends();
	if(pRet && pRet->loadFromSrv(json)){
		pRet->autorelease();
	}
	else{
		CC_SAFE_DELETE(pRet);
		pRet = NULL;
	}
	return pRet;
};

bool Friends::loadFromSrv(Json *json)
{
	if(json){
		setId(			KoumeChan::getLong(json	,JS_ID			,getId()));
		Json* fr = Json_getItem(json, JS_FRIEND);
		if(fr){
			setLoginId(KoumeChan::getLLong(fr, JS_ID, -1));
			setUUID(Value(Json_getString(fr,JS_UUID,"")));
			setName(Value(Json_getString(fr,JS_DISPLAY_NAME,"")));
			setURL(Value(Json_getString(fr,JS_IMAGE_URL,"")));
			setEmail(Value(Json_getString(fr,JS_MAIL_ADDRESS,"")));
		}
		else{
			setLoginId(KoumeChan::getLLong(json, JS_ID, -1));
			setUUID(Value(Json_getString(json,JS_UUID,"")));
			setName(Value(Json_getString(json,JS_DISPLAY_NAME,"")));
			setURL(Value(Json_getString(json,JS_IMAGE_URL,"")));
			setEmail(Value(Json_getString(json,JS_MAIL_ADDRESS,"")));
		}
		return true;
	}
	return false;
};