//
//  Rank.h
//  koumeChan
//
//  Created by 上野　彰三 on 2014/04/01.
//
//

#ifndef __koumeChan__Rank__
#define __koumeChan__Rank__


#include "cocos2d.h"
#include "BaseNamedMaster.h"

class Rank : public BaseNamedMaster
{
protected:
	Rank();
	virtual ~Rank();
	
	
public:
	static Rank* createWithJson(Json* json);
	virtual std::string toJsonString();
	virtual void registerToParent() {};
	
};


#endif /* defined(__koumeChan__Rank__) */
