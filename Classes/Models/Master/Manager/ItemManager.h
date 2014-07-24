//
//  ItemManager.h
//  koumeChan
//
//  Created by 上野　彰三 on 2014/04/01.
//
//

#ifndef __koumeChan__ItemManager__
#define __koumeChan__ItemManager__

#include "cocos2d.h"
#include "KoumeChan.h"
#include "Item.h"
#include "BaseMasterManager.h"

class ItemManager : public BaseMasterManager
{
protected:
	
public:
	static ItemManager* create(long version);
	virtual std::string getTableName();
	virtual BaseMaster* createMaster(Json* json);
	virtual int getTableNo()		{ return BaseMaster::SPECIAL_ITEM_MASTER;};
	Item* getItem(long no);
};


#endif /* defined(__koumeChan__ItemManager__) */
