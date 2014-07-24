//
//  MasterUnitSkillManager.h
//  koumeChan
//
//  Created by 上野　彰三 on 2014/04/01.
//
//

#ifndef __koumeChan__MasterUnitSkillManager__
#define __koumeChan__MasterUnitSkillManager__

#include "cocos2d.h"
#include "KoumeChan.h"
#include "MasterUnitSkill.h"
#include "BaseMasterManager.h"

class MasterUnitSkillManager : public BaseMasterManager
{
protected:
	virtual void clearData();		
public:
	static MasterUnitSkillManager* create(long version);
	virtual std::string getTableName();
	virtual BaseMaster* createMaster(Json* json);
	virtual int getTableNo()		{ return BaseMaster::UNIT_SKILL_MASTER;};
	MasterUnitSkill* getMasterUnitSkill(long no);
};




#endif /* defined(__koumeChan__MasterUnitSkillManager__) */
