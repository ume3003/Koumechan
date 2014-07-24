//
//  FriendMatch.cpp
//  Koumechan
//
//  Created by 上野　彰三 on 2014/07/08.
//
//

#include "FriendMatch.h"
#include "JsonKeyString.h"
#include "KoumeChan.h"
using namespace cocos2d;
using namespace std;

FriendMatch::FriendMatch() : m_myPlayer(NULL),m_urPlayer(NULL)
{
	
}
FriendMatch* FriendMatch::createWithJson(Json *json,cocos2d::Value myUUID)
{
	FriendMatch* pRet = new FriendMatch();
	if(pRet && pRet->loadFromSrv(json,myUUID)){
		pRet->autorelease();
	}
	else{
		CC_SAFE_DELETE(pRet);
		pRet = NULL;
	}
	return pRet;
};
Friends* FriendMatch::getFriends()
{
	if(getOwner()){
		return getUrPlayer();
	}
	return getMyPlayer();
}
bool FriendMatch::loadFromSrv(Json *json,cocos2d::Value myUUID)
{
	if(json){
		string err = Json_getString(json,JS_ERROR,"");
		if(err.length() == 0){
			setUUID(Value(Json_getString(json,JS_FRIEND_COM_ID,"")));
			setCount(KoumeChan::getInt(json,JS_FRIEND_COM_COUNT,0));
			setScenario(KoumeChan::getLLong(json, JS_SCENARIO, 0));
			setMyUUID(Value(Json_getString(json,JS_FRIEND_ME,"")));
			setUrUUID(Value(Json_getString(json,JS_FRIEND_YOU,"")));
			setSeed(KoumeChan::getLLong(json, JS_RAMDOM_SEED, 0));
			Json* regJson = Json_getItem(json,JS_FRIEND_REGISTERED);
			if(regJson){
				Json* myJson = Json_getItem(regJson,V2C(getMyUUID()));
				Json* urJson = Json_getItem(regJson,V2C(getUrUUID()));
				if(myJson){
					setMyPlayer(Friends::createWithJson(myJson));
				}
				if(urJson){
					setUrPlayer(Friends::createWithJson(urJson));
				}
				setOwner(myUUID.asString() == getMyUUID().asString());				
				return true;
			}
		}
	}
	return false;
};