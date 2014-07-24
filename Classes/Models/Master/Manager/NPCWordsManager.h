//
//  NPCWordsManager.h
//  Koumechan
//
//  Created by 上野　彰三 on 2014/06/25.
//
//

#ifndef __Koumechan__NPCWordsManager__
#define __Koumechan__NPCWordsManager__

#include "cocos2d.h"
#include "KoumeChan.h"
#include "NPCWords.h"
#include "BaseMasterManager.h"

class NPCWordsManager : public BaseMasterManager
{
protected:
	virtual void clearData();
public:
	static NPCWordsManager* create(long version);
	virtual std::string getTableName();
	virtual BaseMaster* createMaster(Json* json);
	virtual int getTableNo()		{ return BaseMaster::NPC_WORDS_MASTER;};
	NPCWords* getNPCWords(long no);
};


#endif /* defined(__Koumechan__NPCWordsManager__) */
