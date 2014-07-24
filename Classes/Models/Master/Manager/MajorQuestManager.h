//
//  MajorQuestManager.h
//  koumeChan
//
//  Created by 上野　彰三 on 2014/03/25.
//
//

#ifndef __koumeChan__MajorQuestManager__
#define __koumeChan__MajorQuestManager__

#include "cocos2d.h"
#include "KoumeChan.h"
#include "MajorQuest.h"
#include "BaseMasterManager.h"

class MajorQuestManager : public BaseMasterManager
{
protected:
	virtual void clearData();	
public:
	static MajorQuestManager* create(long version);
	virtual std::string getTableName();
	virtual BaseMaster* createMaster(Json* json);
	virtual int getTableNo()		{ return BaseMaster::MAJOR_QUEST_MASTER;};
	MajorQuest* getMajorQuest(long no);
};

#endif /* defined(__koumeChan__MajorQuestManager__) */
