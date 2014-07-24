//
//  ScenarioRule.h
//  koumeChan
//
//  Created by 上野　彰三 on 2014/04/01.
//
//

#ifndef __koumeChan__ScenarioRule__
#define __koumeChan__ScenarioRule__

#include "cocos2d.h"
#include "BaseConditionMaster.h"

class ScenarioRule : public BaseConditionMaster
{
protected:
	ScenarioRule();
	virtual ~ScenarioRule();
	
	
public:
	static ScenarioRule* createWithJson(Json* json);
	virtual std::string toJsonString();
	virtual void registerToParent();
};

#endif /* defined(__koumeChan__ScenarioRule__) */
