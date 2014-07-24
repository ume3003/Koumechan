//
//  BaseDamageManager.h
//  Koumechan
//
//  Created by 上野　彰三 on 2014/06/26.
//
//

#ifndef __Koumechan__BaseDamageManager__
#define __Koumechan__BaseDamageManager__

#include "cocos2d.h"
#include "KoumeChan.h"
#include "BaseDamage.h"
#include "BaseMasterManager.h"

class BaseDamageManager : public BaseMasterManager
{
protected:
	
public:
	static BaseDamageManager* create(long version);
	virtual std::string getTableName();
	virtual BaseMaster* createMaster(Json* json);
	virtual int getTableNo()		{ return BaseMaster::BASE_DAMAGE_MASTER;};
	BaseDamage* getBaseDamage(BaseDamage::BD_TYPE no);
};




#endif /* defined(__Koumechan__BaseDamageManager__) */
