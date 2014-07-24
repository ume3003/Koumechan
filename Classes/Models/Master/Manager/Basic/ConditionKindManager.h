//
//  ConditionKindManager.h
//  koumeChan
//
//  Created by 上野　彰三 on 2014/04/01.
//
//

#ifndef __koumeChan__ConditionKindManager__
#define __koumeChan__ConditionKindManager__


#include "cocos2d.h"
#include "KoumeChan.h"
#include "ConditionKind.h"
#include "BaseMasterManager.h"

class ConditionKindManager : public BaseMasterManager
{
protected:
	
public:
	static ConditionKindManager* create(long version);
	virtual std::string getTableName();
	virtual BaseMaster* createMaster(Json* json);
	virtual int getTableNo()		{ return BaseMaster::CONDITION_KIND_MASTER;};
	ConditionKind* getConditionKind(long no);
};




#endif /* defined(__koumeChan__ConditionKindManager__) */
