//
//  BaseNamedMaster.h
//  koumeChan
//
//  Created by 上野　彰三 on 2014/03/17.
//
//

#ifndef __koumeChan__BaseNamedMaster__
#define __koumeChan__BaseNamedMaster__

#include "cocos2d.h"
#include "BaseMaster.h"

class BaseNamedMaster : public BaseMaster
{
protected:
	virtual bool initWithJson(Json* json);
	CC_SYNTHESIZE(cocos2d::Value,m_Name,Name);
	CC_SYNTHESIZE(cocos2d::Value,m_Detail,Detail);
	CC_SYNTHESIZE(cocos2d::Value,m_Image,Image);
	
public:
	virtual std::string toJsonString();
};

#endif /* defined(__koumeChan__BaseNamedMaster__) */
