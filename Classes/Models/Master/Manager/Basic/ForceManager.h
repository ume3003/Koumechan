//
//  ForceManager.h
//  koumeChan
//
//  Created by 上野　彰三 on 2014/04/01.
//
//

#ifndef __koumeChan__ForceManager__
#define __koumeChan__ForceManager__



#include "cocos2d.h"
#include "KoumeChan.h"
#include "Force.h"
#include "BaseMasterManager.h"

class ForceManager : public BaseMasterManager
{
protected:
	
public:
	static ForceManager* create(long version);
	virtual std::string getTableName();
	virtual BaseMaster* createMaster(Json* json);
	virtual int getTableNo()		{ return BaseMaster::FORCE_MASTER;};
	Force* getForce(long no);
};


#endif /* defined(__koumeChan__ForceManager__) */
