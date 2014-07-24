//
//  MasterNPCManager.h
//  Koumechan
//
//  Created by 上野　彰三 on 2014/06/23.
//
//

#ifndef __Koumechan__MasterNPCManager__
#define __Koumechan__MasterNPCManager__

#include "cocos2d.h"
#include "KoumeChan.h"
#include "MasterNPC.h"
#include "BaseMasterManager.h"

class MasterNPCManager : public BaseMasterManager
{
protected:

public:
	static MasterNPCManager* create(long version);
	virtual std::string getTableName();
	virtual BaseMaster* createMaster(Json* json);
	virtual int getTableNo()		{ return BaseMaster::NPC_MASTER;};
	MasterNPC* getMasterNPC(long no);
};

#endif /* defined(__Koumechan__MasterNPCManager__) */
