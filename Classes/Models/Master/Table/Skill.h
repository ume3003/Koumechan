//
//  Skill.h
//  koumeChan
//
//  Created by 上野　彰三 on 2014/04/01.
//
//

#ifndef __koumeChan__Skill__
#define __koumeChan__Skill__

#include "cocos2d.h"
#include "KCDef.h"
#include "BaseDamage.h"
#include "BaseNamedMaster.h"

class Skill : public BaseNamedMaster
{
protected:
	Skill();
	virtual ~Skill();
	virtual bool initWithJson(Json* json);
	static cocos2d::Size m_Areas[];
	std::vector<int> getDPSArea(DIRECT direct,int baseIdx);
	std::vector<int> getHealArea(DIRECT direct,int baseIdx);
	std::vector<int> getTankArea(DIRECT direct,int baseIdx);
	std::vector<int> getBuffArea(DIRECT direct,int baseIdx);
	std::vector<int> getMagicArea(DIRECT direct,int baseIdx);
	int xDiff(DIRECT direct);
	int yDiff(DIRECT direct);
	
public:
	
	enum SKILL_NAME {
		TAUNT = 0,
		ATTACK,
		BUFF,
		HEAL,
		MAGIC,
		
	};
	enum AREA_TYPE {
		NONE = 0,
		DPS_1	= 1,
		HEAL_1,
		BUFF_1,
		TANK_1,
		MAGIC_1,
		DPS_2	= 6,
		HEAL_2,
		BUFF_2,
		TANK_2,
		MAGIC_2,
		DPS_3	= 11,
		HEAL_3,
		BUFF_3,
		TANK_3,
		MAGIC_3
	};
	
	static Skill* createWithJson(Json* json);
	virtual std::string toJsonString();
	virtual void registerToParent() {};
	
	cocos2d::Size getAreaSize();
	std::vector<int> getArea(DIRECT direct,int baseIdx);
	
	std::string getPNG();
	std::string getPLIST();

	CC_SYNTHESIZE(BaseDamage::BD_TYPE, m_skillDamage, SkillDamage);
	CC_SYNTHESIZE(AREA_TYPE ,m_areType,AreaType);
	CC_SYNTHESIZE(cocos2d::Value,m_frameName,FrameName);

};

#endif /* defined(__koumeChan__Skill__) */
