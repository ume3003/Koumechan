//
//  ScenarioManager.h
//  koumeChan
//
//  Created by 上野　彰三 on 2014/04/01.
//
//

#ifndef __koumeChan__ScenarioManager__
#define __koumeChan__ScenarioManager__

#include "cocos2d.h"
#include "KoumeChan.h"
#include "Scenario.h"
#include "BaseMasterManager.h"

class ScenarioManager : public BaseMasterManager
{
protected:
	virtual void clearData();	
public:
	static ScenarioManager* create(long version);
	virtual std::string getTableName();
	virtual BaseMaster* createMaster(Json* json);
	virtual int getTableNo()		{ return BaseMaster::SKILL_MASTER;};
	Scenario* getScenario(long no);
};


#endif /* defined(__koumeChan__ScenarioManager__) */
