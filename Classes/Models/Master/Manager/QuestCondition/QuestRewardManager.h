//
//  QuestRewardManager.h
//  koumeChan
//
//  Created by 上野　彰三 on 2014/04/01.
//
//

#ifndef __koumeChan__QuestRewardManager__
#define __koumeChan__QuestRewardManager__

#include "cocos2d.h"
#include "KoumeChan.h"
#include "QuestReward.h"
#include "BaseMasterManager.h"

class QuestRewardManager : public BaseMasterManager
{
protected:
	virtual void clearData();		
public:
	static QuestRewardManager* create(long version);
	virtual std::string getTableName();
	virtual BaseMaster* createMaster(Json* json);
	virtual int getTableNo()		{ return BaseMaster::QUEST_REWARD_MASTER;};
	QuestReward* getQuestReward(long no);
};

#endif /* defined(__koumeChan__QuestRewardManager__) */
