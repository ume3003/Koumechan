//
//  QuestUnit.h
//  koumeChan
//
//  Created by 上野　彰三 on 2014/04/01.
//
//

#ifndef __koumeChan__QuestUnit__
#define __koumeChan__QuestUnit__

#include "cocos2d.h"
#include "BaseConditionMaster.h"

class QuestUnit : public BaseConditionMaster
{
protected:
	QuestUnit();
	virtual ~QuestUnit();
	
	
public:
	static QuestUnit* createWithJson(Json* json);
	virtual std::string toJsonString();
	virtual void registerToParent();
};

#endif /* defined(__koumeChan__QuestUnit__) */
