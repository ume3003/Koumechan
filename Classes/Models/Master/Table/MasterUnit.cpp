//
//  MasterUnit.cpp
//  koumeChan
//
//  Created by 上野　彰三 on 2014/04/01.
//
//

#include "MasterUnit.h"
#include "JsonKeyString.h"
#include "DirectionQuest.h"
#include "DirectionManager.h"
#include "KoumeChan.h"

using namespace cocos2d;
using namespace std;

MasterUnit::MasterUnit()
{
	
}

MasterUnit::~MasterUnit()
{

}

MasterUnit* MasterUnit::createWithJson(Json *json)
{
	MasterUnit* pRet = new MasterUnit();
	if(pRet && pRet->initWithJson(json)){
		pRet->autorelease();
	}
	else{
		CC_SAFE_DELETE(pRet);
		pRet = NULL;
	}
	return pRet;
}


bool MasterUnit::initWithJson(Json* json)
{
	if(BaseNamedMaster::initWithJson(json)){
		setDirectionNo(KoumeChan::getLong(json, JS_DIRECTION, -1));
		setForceNo(KoumeChan::getLong(json, JS_FORCE, -1));
		setFrame(Value(Json_getString(json,JS_FRAME,"")));
		setColor(Value(Json_getString(json,JS_COLOR,"")));
		return true;
	}
	return false;
}

string MasterUnit::toJsonString()
{
	string baseStr = BaseNamedMaster::toJsonString();
	string jsonStr = StringUtils::format("{%s,%s,%s,%s,%s}",baseStr.c_str(),
										 jsStr(JS_COLOR,getColor().asString().c_str()).c_str(),
										 jsStr(JS_FRAME,getFrame().asString().c_str()).c_str(),
										 jsLong(JS_DIRECTION,getDirectionNo()).c_str(),
										 jsLong(JS_FORCE,getForceNo()).c_str());
	return jsonStr;
}

void MasterUnit::addSkill(BaseConditionMaster* master)
{
	m_Skills.pushBack(master);
}

std::string MasterUnit::getPlistFileName()
{
	return StringUtils::format("unit/%s.plist",V2C(getFrame()));
}
std::string MasterUnit::getPNGFileName()
{
	return StringUtils::format("unit/%s.png",V2C(getFrame()));
}
std::string MasterUnit::getFrameName()
{
	return StringUtils::format("%s%s0.png",V2C(getImage()),V2C(getColor()));
}
std::string MasterUnit::getTextureName()
{
	return StringUtils::format("%s%s.png",V2C(getImage()),V2C(getColor()));
}
std::string MasterUnit::getSpecialFrameName()
{
	return StringUtils::format("%s%s1.png",V2C(getImage()),V2C(getColor()));
}

void MasterUnit::clearChild(BaseMaster::MASTERNO masterNo)
{
	if(masterNo == BaseMaster::SKILL_MASTER){
		m_Skills.clear();
	}
}
BaseConditionMaster* MasterUnit::getSkill(int idx)
{
	if(0 <= idx && idx < m_Skills.size()){
		return m_Skills.at(idx);
	}
	return NULL;
}
