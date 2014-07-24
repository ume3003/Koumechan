//
//  MasterMapManager.h
//  koumeChan
//
//  Created by 上野　彰三 on 2014/04/01.
//
//

#ifndef __koumeChan__MasterMapManager__
#define __koumeChan__MasterMapManager__


#include "cocos2d.h"
#include "KoumeChan.h"
#include "MasterMap.h"
#include "BaseMasterManager.h"

class MasterMapManager : public BaseMasterManager
{
protected:
	
public:
	static MasterMapManager* create(long version);
	virtual std::string getTableName();
	virtual BaseMaster* createMaster(Json* json);
	virtual int getTableNo()		{ return BaseMaster::MAP_MASTER;};
	MasterMap* getMasterMap(long no);
};


#endif /* defined(__koumeChan__MasterMapManager__) */
