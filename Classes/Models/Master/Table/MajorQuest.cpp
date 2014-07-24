//
//  MajorQuest.cpp
//  koumeChan
//
//  Created by 上野　彰三 on 2014/03/25.
//
//
#include "JsonKeyString.h"
#include "MajorQuest.h"
#include "DirectionQuest.h"
#include "DirectionManager.h"
#include "KoumeChan.h"

using namespace cocos2d;
using namespace std;

MajorQuest::MajorQuest()
{
	
}

MajorQuest::~MajorQuest()
{
	m_minorQuestNo.clear();
}

MajorQuest* MajorQuest::createWithJson(Json *json)
{
	MajorQuest* pRet = new MajorQuest();
	if(pRet && pRet->initWithJson(json)){
		pRet->autorelease();
	}
	else{
		CC_SAFE_DELETE(pRet);
		pRet = NULL;
	}
	return pRet;
}
void MajorQuest::registerToParent()
{
	DirectionQuest* direction = KoumeChan::getInstance()->getDirectionMaster(getDirectionNo());
	if(direction){
		direction->addMajorQuestNo(getMasterNo());
	}
}



bool MajorQuest::initWithJson(Json* json)
{
	if(BaseNamedMaster::initWithJson(json)){
		setDirectionNo(KoumeChan::getLong(json, JS_DIRECTION, -1));
		return true;
	}
	return false;
}

string MajorQuest::toJsonString()
{
	string baseStr = BaseNamedMaster::toJsonString();
	string jsonStr = StringUtils::format("{%s,%s}",
					baseStr.c_str(),jsLong(JS_DIRECTION,getDirectionNo()).c_str());
	return jsonStr;
}

void MajorQuest::addMinorQuestNo(long questNo)
{
	m_minorQuestNo.push_back(questNo);
}
void MajorQuest::clearChild(BaseMaster::MASTERNO masterNo)
{
	if(masterNo == BaseMaster::MINOR_QUEST_MASTER){
		m_minorQuestNo.clear();
	}
}