//
//  MasterUnitManager.h
//  koumeChan
//
//  Created by 上野　彰三 on 2014/04/01.
//
//

#ifndef __koumeChan__MasterUnitManager__
#define __koumeChan__MasterUnitManager__


#include "cocos2d.h"
#include "KoumeChan.h"
#include "MasterUnit.h"
#include "BaseMasterManager.h"

class MasterUnitManager : public BaseMasterManager
{
protected:

public:
	static MasterUnitManager* create(long version);
	virtual std::string getTableName();
	virtual BaseMaster* createMaster(Json* json);
	virtual int getTableNo()		{ return BaseMaster::UNIT_MASTER;};
	MasterUnit* getMasterUnit(long no);
};



#endif /* defined(__koumeChan__MasterUnitManager__) */
