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
			setHP(KoumeChan::getLLong(fr, JS_HP, -1));
			setLevel(KoumeChan::getLLong(fr, JS_LEVEL, -1));
			setUUID(Value(Json_getString(fr,JS_UUID,"")));
			setName(Value(Json_getString(fr,JS_DISPLAY_NAME,"")));
			setURL(Value(Json_getString(fr,JS_IMAGE_URL,"")));
			setEmail(Value(Json_getString(fr,JS_MAIL_ADDRESS,"")));
		}
		else{
			setLoginId(KoumeChan::getLLong(json, JS_ID, -1));
			setHP(KoumeChan::getLLong(json, JS_HP, -1));
			setLevel(KoumeChan::getLLong(json, JS_LEVEL, -1));
			setUUID(Value(Json_getString(json,JS_UUID,"")));
			setName(Value(Json_getString(json,JS_DISPLAY_NAME,"")));
			setURL(Value(Json_getString(json,JS_IMAGE_URL,"")));
			setEmail(Value(Json_getString(json,JS_MAIL_ADDRESS,"")));
		}
		return true;
	}
	return false;
};

Friends* Friends::createMyData()
{
	KoumeChan* chan = KoumeChan::getInstance();
	GameCharacter* chara = chan->getGameCharacter();
	Friends* pRet = new Friends();
	if(pRet ){
		pRet->autorelease();
		pRet->setLoginId(chan->getLoginId());
		pRet->setHP(chara->getHP());
		pRet->setLevel(chara->getLevel());
		pRet->setUUID(chan->getUUID());
		pRet->setName(chan->getDisplayName());
		pRet->setURL(chan->getProfileUrl());
		pRet->setEmail(chan->getMailAddress());
	}
	else{
		CC_SAFE_DELETE(pRet);
		pRet = NULL;
	}
	return pRet;
};

Friends* Friends::createNPC(MasterNPC *npc)
{
	Friends* pRet = new Friends();
	if(pRet ){
		pRet->autorelease();
		pRet->setLoginId(-1);
		pRet->setHP(npc->getHP());
		pRet->setLevel(npc->getLevel());
		pRet->setName(npc->getName());
		pRet->setURL(npc->getImage());
	}
	else{
		CC_SAFE_DELETE(pRet);
		pRet = NULL;
	}
	return pRet;
};