//
//  MasterUnit.h
//  koumeChan
//
//  Created by 上野　彰三 on 2014/04/01.
//
//

#ifndef __koumeChan__MasterUnit__
#define __koumeChan__MasterUnit__



#include "cocos2d.h"
#include "BaseNamedMaster.h"
#include "BaseConditionMaster.h"

class MasterUnit : public BaseNamedMaster
{
protected:
	MasterUnit();
	virtual ~MasterUnit();
	virtual bool initWithJson(Json* json);
	
	CC_SYNTHESIZE(long, m_DirectionNo, DirectionNo);
	CC_SYNTHESIZE(long, m_ForceNo,ForceNo);
	CC_SYNTHESIZE(cocos2d::Value,m_Flame,Frame);
	CC_SYNTHESIZE(cocos2d::Value,m_Color,Color);
	cocos2d::Vector<BaseConditionMaster*> m_Skills;
	
public:
	static MasterUnit* createWithJson(Json* json);
	virtual std::string toJsonString();
	virtual void registerToParent() {};
	void addSkill(BaseConditionMaster* master);
	std::string getPlistFileName();
	std::string getPNGFileName();
	std::string getFrameName();
	std::string getSpecialFrameName();
	virtual void clearChild(MASTERNO masterNo);
	
	BaseConditionMaster* getSkill(int idx);
	long getSkillCount()	{ return m_Skills.size();};
};

#endif /* defined(__koumeChan__MasterUnit__) */
