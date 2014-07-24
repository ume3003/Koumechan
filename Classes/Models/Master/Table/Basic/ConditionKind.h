//
//  ConditionKind.h
//  koumeChan
//
//  Created by 上野　彰三 on 2014/04/01.
//
//

#ifndef __koumeChan__ConditionKind__
#define __koumeChan__ConditionKind__


#include "cocos2d.h"
#include "BaseNamedMaster.h"

class ConditionKind : public BaseNamedMaster
{
protected:
	ConditionKind();
	virtual ~ConditionKind();
	
	
public:
	static ConditionKind* createWithJson(Json* json);
	virtual std::string toJsonString();
	virtual void registerToParent() {};
	
};


#endif /* defined(__koumeChan__ConditionKind__) */
