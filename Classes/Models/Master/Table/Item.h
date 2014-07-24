//
//  Item.h
//  koumeChan
//
//  Created by 上野　彰三 on 2014/04/01.
//
//

#ifndef __koumeChan__Item__
#define __koumeChan__Item__

#include "cocos2d.h"
#include "BaseNamedMaster.h"

class Item : public BaseNamedMaster
{
protected:
	Item();
	virtual ~Item();
	
	
public:
	static Item* createWithJson(Json* json);
	virtual std::string toJsonString();
	virtual void registerToParent() {};
	
};


#endif /* defined(__koumeChan__Item__) */
