//
//  DirectionManager.h
//  koumeChan
//
//  Created by 上野　彰三 on 2014/03/17.
//
//

#ifndef __koumeChan__DirectionManager__
#define __koumeChan__DirectionManager__

#include "cocos2d.h"
#include "KoumeChan.h"
#include "DirectionQuest.h"
#include "BaseMasterManager.h"

class DirectionManager : public BaseMasterManager
{
protected:

public:
	static DirectionManager* create(long version);
	virtual std::string getTableName();
	virtual BaseMaster* createMaster(Json* json);
	virtual int getTableNo()		{ return BaseMaster::DIRECT_MASTER;};
	DirectionQuest* getDirection(long no);
	
};

#endif /* defined(__koumeChan__DirectionManager__) */
