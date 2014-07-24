//
//  GameCharacter.cpp
//  koumeChan
//
//  Created by 上野　彰三 on 2014/03/17.
//
//

#include "GameCharacter.h"
#include "JsonKeyString.h"
#include "KoumeChan.h"
using namespace cocos2d;
using namespace std;

GameCharacter::GameCharacter()
{
	setId(-1);
	setStamina(0);
	setMaxStamina(0);
	setMoney(0);
	setGold(0);
	setLevel(1);
	setExp(0);
	setHP(100);
	setLastCommand(0);
	
}
GameCharacter* GameCharacter::createWithJson(Json *json)
{
	GameCharacter* pRet = new GameCharacter();
	if(pRet && pRet->loadFromSrv(json)){
		pRet->autorelease();
	}
	else{
		CC_SAFE_DELETE(pRet);
		pRet = NULL;
	}
	return pRet;
};

bool GameCharacter::loadFromSrv(Json *json)
{
	if(json){
		setId(			KoumeChan::getLong(json	,JS_ID			,getId()));
		setStamina(		KoumeChan::getLong(json	,JS_STAMINA		,getStamina()));
		setMaxStamina(	KoumeChan::getLong(json	,JS_MAX_STAMINA	,getMaxStamina()));
		setMoney(		KoumeChan::getLong(json	,JS_MONEY		,getMoney()));
		setHP(			KoumeChan::getLong(json	,JS_HP			,getHP()));
		setLevel(		KoumeChan::getLong(json	,JS_LEVEL		,getLevel()));
		setExp(			KoumeChan::getLong(json	,JS_EXPERIENCE	,getExp()));
		setGold(		KoumeChan::getLong(json	,JS_GOLD		,getGold()));
		setLastCommand(	KoumeChan::getLLong(json,JS_LAST_COMMAND,getLastCommand()));
		return true;
	}
	return false;
};