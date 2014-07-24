//
//  QuestClearManager.h
//  koumeChan
//
//  Created by 上野　彰三 on 2014/04/01.
//
//

#ifndef __koumeChan__QuestClearManager__
#define __koumeChan__QuestClearManager__

#include "cocos2d.h"
#include "KoumeChan.h"
#include "QuestClear.h"
#include "BaseMasterManager.h"

class QuestClearManager : public BaseMasterManager
{
protected:
	virtual void clearData();		
public:
	static QuestClearManager* create(long version);
	virtual std::string getTableName();
	virtual BaseMaster* createMaster(Json* json);
	virtual int getTableNo()		{ return BaseMaster::QUEST_CLEAR_MASTER;};
	QuestClear* getQuestClear(long no);
};

#endif /* defined(__koumeChan__QuestClearManager__) */
