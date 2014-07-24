//
//  MinorQuestManager.h
//  koumeChan
//
//  Created by 上野　彰三 on 2014/03/25.
//
//

#ifndef __koumeChan__MinorQuestManager__
#define __koumeChan__MinorQuestManager__

#include "cocos2d.h"
#include "KoumeChan.h"
#include "MinorQuest.h"
#include "BaseMasterManager.h"

class MinorQuestManager : public BaseMasterManager
{
protected:
	virtual void clearData();	
public:
	static MinorQuestManager* create(long version);
	virtual std::string getTableName();
	virtual BaseMaster* createMaster(Json* json);
	virtual int getTableNo()		{ return BaseMaster::MINOR_QUEST_MASTER;};
	MinorQuest* getMinorQuest(long no);
};


#endif /* defined(__koumeChan__MinorQuestManager__) */
