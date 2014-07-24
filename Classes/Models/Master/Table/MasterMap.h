//
//  MasterMap.h
//  koumeChan
//
//  Created by 上野　彰三 on 2014/04/01.
//
//

#ifndef __koumeChan__MasterMap__
#define __koumeChan__MasterMap__

#include "cocos2d.h"
#include "BaseNamedMaster.h"

class MasterMap : public BaseNamedMaster
{
protected:
	MasterMap();
	virtual ~MasterMap();
	
	
public:
	static MasterMap* createWithJson(Json* json);
	virtual std::string toJsonString();
	virtual void registerToParent() {};

};

#endif /* defined(__koumeChan__MasterMap__) */
