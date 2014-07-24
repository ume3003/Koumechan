//
//  QuestUnitManager.h
//  koumeChan
//
//  Created by 上野　彰三 on 2014/04/01.
//
//

#ifndef __koumeChan__QuestUnitManager__
#define __koumeChan__QuestUnitManager__

#include "cocos2d.h"
#include "KoumeChan.h"
#include "QuestUnit.h"
#include "BaseMasterManager.h"

class QuestUnitManager : public BaseMasterManager
{
protected:
	virtual void clearData();		
public:
	static QuestUnitManager* create(long version);
	virtual std::string getTableName();
	virtual BaseMaster* createMaster(Json* json);
	virtual int getTableNo()		{ return BaseMaster::QUEST_UNIT_MASTER;};
	QuestUnit* getQuestUnit(long no);
};




#endif /* defined(__koumeChan__QuestUnitManager__) */
