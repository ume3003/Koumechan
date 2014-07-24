//
//  QuestClear.h
//  koumeChan
//
//  Created by 上野　彰三 on 2014/04/01.
//
//

#ifndef __koumeChan__QuestClear__
#define __koumeChan__QuestClear__

#include "cocos2d.h"
#include "BaseConditionMaster.h"

class QuestClear : public BaseConditionMaster
{
protected:
	QuestClear();
	virtual ~QuestClear();
	
	
public:
	static QuestClear* createWithJson(Json* json);
	virtual std::string toJsonString();
	virtual void registerToParent();
};

#endif /* defined(__koumeChan__QuestClear__) */
