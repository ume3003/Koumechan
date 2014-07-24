//
//  RankManager.h
//  koumeChan
//
//  Created by 上野　彰三 on 2014/04/01.
//
//

#ifndef __koumeChan__RankManager__
#define __koumeChan__RankManager__


#include "cocos2d.h"
#include "KoumeChan.h"
#include "Rank.h"
#include "BaseMasterManager.h"

class RankManager : public BaseMasterManager
{
protected:
	
public:
	static RankManager* create(long version);
	virtual std::string getTableName();
	virtual BaseMaster* createMaster(Json* json);
	virtual int getTableNo()		{ return BaseMaster::RANK_MASTER;};
	Rank* getRank(long no);
};



#endif /* defined(__koumeChan__RankManager__) */
