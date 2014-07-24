//
//  ScenarioUnitManager.h
//  koumeChan
//
//  Created by 上野　彰三 on 2014/04/01.
//
//

#ifndef __koumeChan__ScenarioUnitManager__
#define __koumeChan__ScenarioUnitManager__

#include "cocos2d.h"
#include "KoumeChan.h"
#include "ScenarioUnit.h"
#include "BaseMasterManager.h"

class ScenarioUnitManager : public BaseMasterManager
{
protected:
	virtual void clearData();		
public:
	static ScenarioUnitManager* create(long version);
	virtual std::string getTableName();
	virtual BaseMaster* createMaster(Json* json);
	virtual int getTableNo()		{ return BaseMaster::SCENARIO_UNIT_MASTER;};
	ScenarioUnit* getScenarioUnit(long no);
};



#endif /* defined(__koumeChan__ScenarioUnitManager__) */
