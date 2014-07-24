//
//  BaseConditionMaster.h
//  koumeChan
//
//  Created by 上野　彰三 on 2014/04/01.
//
//

#ifndef __koumeChan__BaseConditionMaster__
#define __koumeChan__BaseConditionMaster__

#include "cocos2d.h"
#include "BaseMaster.h"

class BaseConditionMaster : public BaseMaster
{
protected:
	virtual bool initWithJson(Json* json);
	CC_SYNTHESIZE(long,m_parentNo,ParentNo);
	CC_SYNTHESIZE(long,m_conditionNo,ConditionNo);
	CC_SYNTHESIZE(long,m_Kind,Kind);
	CC_SYNTHESIZE(long,m_KeyNo,KeyNo);
	CC_SYNTHESIZE(long long,m_Val,Val);
	
public:
	virtual std::string toJsonString();
};
#endif /* defined(__koumeChan__BaseConditionMaster__) */
