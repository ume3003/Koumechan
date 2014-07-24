//
//  Skill.cpp
//  koumeChan
//
//  Created by 上野　彰三 on 2014/04/01.
//
//

#include "Skill.h"
#include "JsonKeyString.h"
#include "KoumeChan.h"

using namespace cocos2d;
using namespace std;


Size Skill::m_Areas[] =
{
	Size(1,1),
	
	Size(1,4),
	Size(3,3),
	Size(3,3),
	Size(3,3),
	Size(4,3),
	
	Size(5,3),
	Size(3,3),
	Size(5,5),
	Size(3,5),
	Size(6,5),
	
	Size(5,5),
	Size(5,5),
	Size(7,7),
	Size(4,7),
	Size(8,7)
	
};

Skill::Skill()
{
	
}

Skill::~Skill()
{
}

Skill* Skill::createWithJson(Json *json)
{
	Skill* pRet = new Skill();
	if(pRet && pRet->initWithJson(json)){
		pRet->autorelease();
	}
	else{
		CC_SAFE_DELETE(pRet);
		pRet = NULL;
	}
	return pRet;
}

bool Skill::initWithJson(Json* json)
{
	if(BaseNamedMaster::initWithJson(json)){
		setSkillDamage((BaseDamage::BD_TYPE)KoumeChan::getInt(json, JS_BASE_DAMAGE, BaseDamage::ELITE_DPS));
		setAreaType((AREA_TYPE)KoumeChan::getInt(json,JS_AREA_TYPE,AREA_TYPE::NONE));
		setFrameName(Value(Json_getString(json, JS_FRAME, "")));
		return true;
	}
	return false;
}
std::string Skill::getPNG()
{
	return StringUtils::format("skill/%s.png",V2C(getFrameName()));
}
std::string Skill::getPLIST()
{
	return StringUtils::format("skill/%s.plist",V2C(getFrameName()));
}


string Skill::toJsonString()
{
	string baseStr = BaseNamedMaster::toJsonString();
	string jsonStr = StringUtils::format("{%s,%s,%s,%s}",baseStr.c_str(),
					jsInt(JS_BASE_DAMAGE,(int)getSkillDamage()).c_str(),
					jsInt(JS_AREA_TYPE,(int)getAreaType()).c_str(),
					jsStr(JS_FRAME,V2C(getFrameName())).c_str()
										 );
	return jsonStr;
}
Size Skill::getAreaSize()
{
	return m_Areas[m_areType];
}

vector<int> Skill::getArea(DIRECT direct,int baseIdx)
{
	Point basePos = idxToPos(baseIdx);
	vector<int> areVec;
	switch (getAreaType()) {
		case NONE:
			break;
		case DPS_1:
		case DPS_2:
		case DPS_3:
			areVec = getDPSArea(direct, baseIdx);
			break;
		case HEAL_1:
		case HEAL_2:
		case HEAL_3:
			areVec = getHealArea(direct, baseIdx);
			break;
		case BUFF_1:
		case BUFF_2:
		case BUFF_3:
			areVec = getBuffArea(direct, baseIdx);
			break;
		case TANK_1:
		case TANK_2:
		case TANK_3:
			areVec = getTankArea(direct, baseIdx);
			break;
		case MAGIC_1:
		case MAGIC_2:
		case MAGIC_3:
			areVec = getMagicArea(direct, baseIdx);
			break;
		default:
			break;
	}
	return areVec;
};


std::vector<int> Skill::getDPSArea(DIRECT direct,int baseIdx)
{
	Point bPos = idxToPos(baseIdx);
	int dx = xDiff(direct);
	int dy = yDiff(direct);
	vector<int> areVec;
	for(int i = 1 ; i < 5 ; i++){
		areVec.push_back(xyToIdx(Point(bPos.x + dx * i,bPos.y + dy * i)));			// 1,0 2,0 3,0 4,0
	}
	if(getAreaType() == DPS_2 || getAreaType() == DPS_3){
		areVec.push_back(xyToIdx(bPos.x + 3 * dx + dy	,bPos.y + 3 * dy + dx));	// 3,1
		areVec.push_back(xyToIdx(bPos.x + 3 * dx - dy	,bPos.y + 3 * dy - dx));	// 3,-1
		areVec.push_back(xyToIdx(bPos.x + 4 * dx + dy	,bPos.y + 4 * dy + dx));	// 4,1
		areVec.push_back(xyToIdx(bPos.x + 4 * dx - dy	,bPos.y + 4 * dy - dx));	// 4,-1
	}
	if(getAreaType() == DPS_3){
		areVec.push_back(xyToIdx(bPos.x + 1 * dx + dy	,bPos.y + 1 * dy + dx));	// 1,1
		areVec.push_back(xyToIdx(bPos.x + 1 * dx - dy	,bPos.y + 1 * dy - dx));	// 1,-1
		areVec.push_back(xyToIdx(bPos.x + 2 * dx + dy	,bPos.y + 2 * dy + dx));	// 2,1
		areVec.push_back(xyToIdx(bPos.x + 2 * dx - dy	,bPos.y + 2 * dy - dx));	// 2,-1
		
		areVec.push_back(xyToIdx(bPos.x + 3 * dx + 2 * dy,bPos.y + 3 * dy + 2 * dx));	// 3,2
		areVec.push_back(xyToIdx(bPos.x + 3 * dx - 2 * dy,bPos.y + 3 * dy - 2 * dx));	// 3,-2
		areVec.push_back(xyToIdx(bPos.x + 4 * dx + 2 * dy,bPos.y + 4 * dy + 2 * dx));	// 4,2
		areVec.push_back(xyToIdx(bPos.x + 4 * dx - 2 * dy,bPos.y + 4 * dy - 2 * dx));	// 4,-2
		
	}
	return areVec;
	
};

std::vector<int> Skill::getTankArea(DIRECT direct,int baseIdx)
{
	Point bPos = idxToPos(baseIdx);
	vector<int> areVec;
	int dx = xDiff(direct);
	int dy = yDiff(direct);

	areVec.push_back(xyToIdx(bPos.x +	  dx				,bPos.y +	  dy));			// 1,0
	areVec.push_back(xyToIdx(bPos.x + 2 * dx				,bPos.y + 2 * dy));			// 2,0
	areVec.push_back(xyToIdx(bPos.x + 2 * dx + 1 * dy		,bPos.y + 2 * dy + 1 * dx));	// 2,1
	areVec.push_back(xyToIdx(bPos.x + 2 * dx - 1 * dy		,bPos.y + 2 * dy - 1 * dx));	// 2,-1
	
	if(getAreaType() == TANK_2 || getAreaType() == TANK_3){
		areVec.push_back(xyToIdx(bPos.x + 1 * dx + 1 * dy	,bPos.y + 1 * dy + 1 * dx));			// 1,1
		areVec.push_back(xyToIdx(bPos.x + 1 * dx - 1 * dy	,bPos.y + 1 * dy - 1 * dx));			// 1,-1
		areVec.push_back(xyToIdx(bPos.x + 2 * dx + 2 * dy	,bPos.y + 2 * dy + 2 * dx));			// 2,2
		areVec.push_back(xyToIdx(bPos.x + 2 * dx - 2 * dy	,bPos.y + 2 * dy - 2 * dx));			// 2,-2
	}
	if(getAreaType() == TANK_3){
		areVec.push_back(xyToIdx(bPos.x + 2 * dx + 3 * dy	,bPos.y + 2 * dy + 3 * dx));			// 2,3
		areVec.push_back(xyToIdx(bPos.x + 2 * dx - 3 * dy	,bPos.y + 2 * dy - 3 * dx));			// 2,-3
		
		areVec.push_back(xyToIdx(bPos.x + 3 * dx + 1 * dy	,bPos.y + 3 * dy + 1 * dx));			// 3,1
		areVec.push_back(xyToIdx(bPos.x + 3 * dx - 1 * dy	,bPos.y + 3 * dy - 1 * dx));			// 3,-1
		areVec.push_back(xyToIdx(bPos.x + 3 * dx + 2 * dy	,bPos.y + 3 * dy + 2 * dx));			// 3,2
		areVec.push_back(xyToIdx(bPos.x + 3 * dx - 2 * dy	,bPos.y + 3 * dy - 2 * dx));			// 3,-2
		areVec.push_back(xyToIdx(bPos.x + 3 * dx + 3 * dy	,bPos.y + 3 * dy + 3 * dx));			// 3,3
		areVec.push_back(xyToIdx(bPos.x + 3 * dx - 3 * dy	,bPos.y + 3 * dy - 3 * dx));			// 3,-3
		
	}
	
	return areVec;
	
};

std::vector<int> Skill::getMagicArea(DIRECT direct,int baseIdx)
{
	Point bPos = idxToPos(baseIdx);
	vector<int> areVec;
	int dx = xDiff(direct);
	int dy = yDiff(direct);
	
	// -----1-2-3
	areVec.push_back(xyToIdx(bPos.x +	  dx		,bPos.y +	  dy));			// 1,0
	areVec.push_back(xyToIdx(bPos.x + 2 * dx + dy	,bPos.y + 2 * dy + dx));	// 2,1
	areVec.push_back(xyToIdx(bPos.x + 2 * dx - dy	,bPos.y + 2 * dy - dx));	// 2,-1

	if(getAreaType() == MAGIC_1 || getAreaType() == MAGIC_3){// ----1-3
		areVec.push_back(xyToIdx(bPos.x + 3 * dx		,bPos.y + 3 * dy));				// 3,0
	}
	
	if(getAreaType() == MAGIC_2 || getAreaType() == MAGIC_3){	// ----2-3
		areVec.push_back(xyToIdx(bPos.x + 3 * dx + 2 * dy	,bPos.y + 3 * dy + 2 * dx));	// 3,2
		areVec.push_back(xyToIdx(bPos.x + 3 * dx - 2 * dy	,bPos.y + 3 * dy - 2 * dx));	// 3,-2
		areVec.push_back(xyToIdx(bPos.x + 4 * dx + 1 * dy	,bPos.y + 4 * dy + 1 * dx));	// 4,1
		areVec.push_back(xyToIdx(bPos.x + 4 * dx - 1 * dy	,bPos.y + 4 * dy - 1 * dx));	// 4,-1
		areVec.push_back(xyToIdx(bPos.x + 5 * dx + 0 * dy	,bPos.y + 5 * dy + 0 * dx));	// 5,0
	}
	if(getAreaType() == MAGIC_3){// ------3
		areVec.push_back(xyToIdx(bPos.x + 4 * dx + 3 * dy	,bPos.y + 4 * dy + 3 * dx));	// 4,3
		areVec.push_back(xyToIdx(bPos.x + 4 * dx - 3 * dy	,bPos.y + 4 * dy - 3 * dx));	// 4,-3
		areVec.push_back(xyToIdx(bPos.x + 5 * dx + 2 * dy	,bPos.y + 5 * dy + 2 * dx));	// 5,2
		areVec.push_back(xyToIdx(bPos.x + 5 * dx - 2 * dy	,bPos.y + 5 * dy - 2 * dx));	// 5,-2
		areVec.push_back(xyToIdx(bPos.x + 6 * dx + 1 * dy	,bPos.y + 6 * dy + 1 * dx));	// 6.1
		areVec.push_back(xyToIdx(bPos.x + 6 * dx - 1 * dy	,bPos.y + 6 * dy - 1 * dx));	// 6,-1
		areVec.push_back(xyToIdx(bPos.x + 7 * dx + 0 * dy	,bPos.y + 7 * dy + 0 * dx));	// 7,0
	}
	
	return areVec;
	
};
std::vector<int> Skill::getBuffArea(DIRECT direct,int baseIdx)
{
	Point bPos = idxToPos(baseIdx);
	vector<int> areVec;
	areVec.push_back(xyToIdx(bPos.x + 1	,bPos.y));
	areVec.push_back(xyToIdx(bPos.x - 1	,bPos.y));
	areVec.push_back(xyToIdx(bPos.x		,bPos.y + 1));
	areVec.push_back(xyToIdx(bPos.x		,bPos.y - 1));
	if(getAreaType() == BUFF_2 || getAreaType() == BUFF_3){
		areVec.push_back(xyToIdx(bPos.x + 2	,bPos.y));
		areVec.push_back(xyToIdx(bPos.x - 2	,bPos.y));
		areVec.push_back(xyToIdx(bPos.x		,bPos.y + 2));
		areVec.push_back(xyToIdx(bPos.x		,bPos.y - 2));
	}
	if(getAreaType() == BUFF_3){
		areVec.push_back(xyToIdx(bPos.x + 1	,bPos.y + 1));
		areVec.push_back(xyToIdx(bPos.x + 1	,bPos.y - 1));
		areVec.push_back(xyToIdx(bPos.x - 1	,bPos.y + 1));
		areVec.push_back(xyToIdx(bPos.x - 1	,bPos.y - 1));
		
		areVec.push_back(xyToIdx(bPos.x + 3	,bPos.y));
		areVec.push_back(xyToIdx(bPos.x - 3	,bPos.y));
		areVec.push_back(xyToIdx(bPos.x		,bPos.y + 3));
		areVec.push_back(xyToIdx(bPos.x		,bPos.y - 3));
	}
	return areVec;
	
};
std::vector<int> Skill::getHealArea(DIRECT direct,int baseIdx)
{
	Point bPos = idxToPos(baseIdx);
	vector<int> areVec;
	areVec.push_back(xyToIdx(bPos.x + 1	,bPos.y + 1));
	areVec.push_back(xyToIdx(bPos.x + 1	,bPos.y - 1));
	areVec.push_back(xyToIdx(bPos.x - 1	,bPos.y + 1));
	areVec.push_back(xyToIdx(bPos.x - 1	,bPos.y - 1));
	if(getAreaType() == HEAL_2 || getAreaType() == HEAL_3){
		areVec.push_back(xyToIdx(bPos.x + 1	,bPos.y));
		areVec.push_back(xyToIdx(bPos.x - 1	,bPos.y));
		areVec.push_back(xyToIdx(bPos.x		,bPos.y + 1));
		areVec.push_back(xyToIdx(bPos.x		,bPos.y - 1));
	}
	if(getAreaType() == HEAL_3){
		areVec.push_back(xyToIdx(bPos.x + 2	,bPos.y + 2));
		areVec.push_back(xyToIdx(bPos.x + 2	,bPos.y - 2));
		areVec.push_back(xyToIdx(bPos.x - 2	,bPos.y + 2));
		areVec.push_back(xyToIdx(bPos.x - 2	,bPos.y - 2));
		
		areVec.push_back(xyToIdx(bPos.x + 2	,bPos.y));
		areVec.push_back(xyToIdx(bPos.x - 2	,bPos.y));
		areVec.push_back(xyToIdx(bPos.x		,bPos.y + 2));
		areVec.push_back(xyToIdx(bPos.x		,bPos.y - 2));
	}
	return areVec;
	
};
int Skill::xDiff(DIRECT direct)
{
	switch(direct){
		case EAST:
			return  1;
		case WEST:
			return -1;
		case NORTH:
		case SOUTH:
		default:
			break;
	}
	return 0;
};
int Skill::yDiff(DIRECT direct)
{
	switch(direct){
		case SOUTH:
			return  -1;
		case NORTH:
			return 1;
		case EAST:
		case WEST:
		default:
			break;
	}
	return 0;
	
};




