//
//  QuestAppearanceManager.h
//  koumeChan
//
//  Created by 上野　彰三 on 2014/04/01.
//
//

#ifndef __koumeChan__QuestAppearanceManager__
#define __koumeChan__QuestAppearanceManager__

#include "cocos2d.h"
#include "KoumeChan.h"
#include "QuestAppearance.h"
#include "BaseMasterManager.h"

class QuestAppearanceManager : public BaseMasterManager
{
protected:
	virtual void clearData();		
public:
	static QuestAppearanceManager* create(long version);
	virtual std::string getTableName();
	virtual BaseMaster* createMaster(Json* json);
	virtual int getTableNo()		{ return BaseMaster::QUEST_APPEARANCE_MASTER;};
	QuestAppearance* getQuestAppearance(long no);
};




#endif /* defined(__koumeChan__QuestAppearanceManager__) */
