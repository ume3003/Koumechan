//
//  MasterNPC.cpp
//  Koumechan
//
//  Created by 上野　彰三 on 2014/06/23.
//
//

#include "MasterNPC.h"
#include "JsonKeyString.h"
#include "KoumeChan.h"

using namespace cocos2d;
using namespace std;

MasterNPC::MasterNPC()
{
	setLevel(1);
	setHP(100);
}

MasterNPC::~MasterNPC()
{
}

MasterNPC* MasterNPC::createWithJson(Json *json)
{
	MasterNPC* pRet = new MasterNPC();
	if(pRet && pRet->initWithJson(json)){
		pRet->autorelease();
	}
	else{
		CC_SAFE_DELETE(pRet);
		pRet = NULL;
	}
	return pRet;
}



string MasterNPC::toJsonString()
{
	string baseStr = BaseNamedMaster::toJsonString();
	string jsonStr = StringUtils::format("{%s,%s,%s}",
										 baseStr.c_str(),
										 jsLong(JS_LEVEL,getLevel()).c_str(),
										 jsLong(JS_HP,getHP()).c_str()
										 );
	return jsonStr;
}

bool MasterNPC::initWithJson(Json* json)
{
	if(BaseNamedMaster::initWithJson(json)){
		setLevel(	KoumeChan::getLong(json,JS_LEVEL,1));
		setHP(		KoumeChan::getLong(json,JS_HP,100));
		return true;
	}
	return false;
}


BaseConditionMaster* MasterNPC::getWords(long l)
{
	if(0 <= l && l < getWordsCount()){
		return m_words.at(l);
	}
	return NULL;
};
void MasterNPC::clearChild(BaseMaster::MASTERNO masterNo)
{
	m_words.clear();
}

void MasterNPC::addWords(BaseConditionMaster *master)
{
	m_words.pushBack(master);
}

