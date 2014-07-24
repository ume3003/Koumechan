//
//  Scenario.h
//  koumeChan
//
//  Created by 上野　彰三 on 2014/04/01.
//
//

#ifndef __koumeChan__Scenario__
#define __koumeChan__Scenario__

#include "cocos2d.h"
#include "BaseNamedMaster.h"
#include "BaseConditionMaster.h"

class Scenario : public BaseNamedMaster
{
protected:
	Scenario();
	virtual ~Scenario();
	virtual bool initWithJson(Json* json);
	cocos2d::Vector<BaseConditionMaster*> m_ScenarioRule;
	cocos2d::Vector<BaseConditionMaster*> m_ScenarioUnit;
	
	CC_SYNTHESIZE(long, m_mapNo,MapNo);
	
public:
	static Scenario* createWithJson(Json* json);
	virtual std::string toJsonString();
	virtual void registerToParent() {};
	void addRule(BaseConditionMaster* master);
	void addUnit(BaseConditionMaster* master);
	virtual void clearChild(MASTERNO masterNo);	
	long getUnitCount()			{return m_ScenarioUnit.size();};
	BaseConditionMaster*	getUnit(long l);

};

#endif /* defined(__koumeChan__Scenario__) */
