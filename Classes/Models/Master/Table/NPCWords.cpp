//
//  NPCWords.cpp
//  Koumechan
//
//  Created by 上野　彰三 on 2014/06/25.
//
//

#include "NPCWords.h"
#include "JsonKeyString.h"
#include "KoumeChan.h"
#include "MasterNPC.h"

using namespace cocos2d;
using namespace std;

NPCWords::NPCWords()
{
	
}

NPCWords::~NPCWords()
{
}

NPCWords* NPCWords::createWithJson(Json *json)
{
	NPCWords* pRet = new NPCWords();
	if(pRet && pRet->initWithJson(json)){
		pRet->autorelease();
	}
	else{
		CC_SAFE_DELETE(pRet);
		pRet = NULL;
	}
	return pRet;
}

bool NPCWords::initWithJson(Json* json)
{
	if(BaseConditionMaster::initWithJson(json)){
		setImage(Value(Json_getString(json,JS_IMAGE,"")));
		setWord(Value(Json_getString(json,JS_WORD,"")));
		return true;
	}
	return false;
}



string NPCWords::toJsonString()
{
	string baseStr = BaseConditionMaster::toJsonString();
	string jsonStr = StringUtils::format("{%s,%s,%s}",baseStr.c_str(),
										 jsStr(JS_WORD,getWord().asString().c_str()).c_str(),
										 jsStr(JS_IMAGE,getImage().asString().c_str()).c_str()
										 );
	return jsonStr;
}

void NPCWords::registerToParent()
{
	MasterNPC* parent = KoumeChan::getInstance()->getNPCMaster(getParentNo());
	if(parent){
		parent->addWords(this);
	}
	
}