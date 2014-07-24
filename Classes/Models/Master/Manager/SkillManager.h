//
//  SkillManager.h
//  koumeChan
//
//  Created by 上野　彰三 on 2014/04/01.
//
//

#ifndef __koumeChan__SkillManager__
#define __koumeChan__SkillManager__

#include "cocos2d.h"
#include "KoumeChan.h"
#include "Skill.h"
#include "BaseMasterManager.h"

class SkillManager : public BaseMasterManager
{
protected:
	
public:
	static SkillManager* create(long version);
	virtual std::string getTableName();
	virtual BaseMaster* createMaster(Json* json);
	virtual int getTableNo()		{ return BaseMaster::SKILL_MASTER;};
	Skill* getSkill(long no);
};




#endif /* defined(__koumeChan__SkillManager__) */
