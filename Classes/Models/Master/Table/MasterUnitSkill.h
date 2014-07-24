//
//  MasterUnitSkill.h
//  koumeChan
//
//  Created by 上野　彰三 on 2014/04/01.
//
//

#ifndef __koumeChan__MasterUnitSkill__
#define __koumeChan__MasterUnitSkill__

#include "cocos2d.h"
#include "BaseConditionMaster.h"

class MasterUnitSkill : public BaseConditionMaster
{
protected:
	MasterUnitSkill();
	virtual ~MasterUnitSkill();
	
	
public:
	static MasterUnitSkill* createWithJson(Json* json);
	virtual std::string toJsonString();
	virtual void registerToParent();
};

#endif /* defined(__koumeChan__MasterUnitSkill__) */
