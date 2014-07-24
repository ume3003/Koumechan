//
//  QuestAppearance.h
//  koumeChan
//
//  Created by 上野　彰三 on 2014/04/01.
//
//

#ifndef __koumeChan__QuestAppearance__
#define __koumeChan__QuestAppearance__

#include "cocos2d.h"
#include "BaseConditionMaster.h"

class QuestAppearance : public BaseConditionMaster
{
protected:
	QuestAppearance();
	virtual ~QuestAppearance();
	
	
public:
	static QuestAppearance* createWithJson(Json* json);
	virtual std::string toJsonString();
	virtual void registerToParent();
};

#endif /* defined(__koumeChan__QuestAppearance__) */
