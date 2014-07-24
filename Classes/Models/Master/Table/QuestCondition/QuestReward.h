//
//  QuestReward.h
//  koumeChan
//
//  Created by 上野　彰三 on 2014/04/01.
//
//

#ifndef __koumeChan__QuestReward__
#define __koumeChan__QuestReward__

#include "cocos2d.h"
#include "BaseConditionMaster.h"

class QuestReward : public BaseConditionMaster
{
protected:
	QuestReward();
	virtual ~QuestReward();
	
	
public:
	static QuestReward* createWithJson(Json* json);
	virtual std::string toJsonString();
	virtual void registerToParent();
};

#endif /* defined(__koumeChan__QuestReward__) */
