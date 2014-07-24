//
//  ScenarioRuleManager.h
//  koumeChan
//
//  Created by 上野　彰三 on 2014/04/01.
//
//

#ifndef __koumeChan__ScenarioRuleManager__
#define __koumeChan__ScenarioRuleManager__

#include "cocos2d.h"
#include "KoumeChan.h"
#include "ScenarioRule.h"
#include "BaseMasterManager.h"

class ScenarioRuleManager : public BaseMasterManager
{
protected:
	virtual void clearData();		
public:
	static ScenarioRuleManager* create(long version);
	virtual std::string getTableName();
	virtual BaseMaster* createMaster(Json* json);
	virtual int getTableNo()		{ return BaseMaster::SCENARIO_RULE_MASTER;};
	ScenarioRule* getScenarioRule(long no);
};



#endif /* defined(__koumeChan__ScenarioRuleManager__) */
