//
//  Direction.cpp
//  koumeChan
//
//  Created by 上野　彰三 on 2014/03/17.
//
//

#include "DirectionQuest.h"

using namespace cocos2d;
using namespace std;

DirectionQuest::DirectionQuest()
{
	
}

DirectionQuest::~DirectionQuest()
{
	m_majorQuestNo.clear();
	m_minorQuestNo.clear();
}

DirectionQuest* DirectionQuest::createWithJson(Json *json)
{
	DirectionQuest* pRet = new DirectionQuest();
	if(pRet && pRet->initWithJson(json)){
		pRet->autorelease();
	}
	else{
		CC_SAFE_DELETE(pRet);
		pRet = NULL;
	}
	return pRet;
}

void DirectionQuest::addMajorQuestNo(long questNo)
{
	m_majorQuestNo.push_back(questNo);
}
void DirectionQuest::addMinorQuestNo(long questNo)
{
	m_minorQuestNo.push_back(questNo);
}
string DirectionQuest::toJsonString()
{
	string baseStr = BaseNamedMaster::toJsonString();
	string jsonStr = StringUtils::format("{%s}",baseStr.c_str());
	return jsonStr;
}

void DirectionQuest::clearChild(BaseMaster::MASTERNO masterNo)
{
	if(masterNo == BaseMaster::MAJOR_QUEST_MASTER){
		m_majorQuestNo.clear();
	}
	else if(masterNo == BaseMaster::MINOR_QUEST_MASTER){
		m_minorQuestNo.clear();
	}
}