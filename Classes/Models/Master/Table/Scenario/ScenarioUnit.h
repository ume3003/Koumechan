//
//  ScenarioUnit.h
//  koumeChan
//
//  Created by 上野　彰三 on 2014/04/01.
//
//

#ifndef __koumeChan__ScenarioUnit__
#define __koumeChan__ScenarioUnit__

#include "cocos2d.h"
#include "BaseConditionMaster.h"

class ScenarioUnit : public BaseConditionMaster
{
protected:
	ScenarioUnit();
	virtual ~ScenarioUnit();
	
	
public:
	static ScenarioUnit* createWithJson(Json* json);
	virtual std::string toJsonString();
	virtual void registerToParent();
};

#endif /* defined(__koumeChan__ScenarioUnit__) */
