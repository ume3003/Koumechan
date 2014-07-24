//
//  Friends.h
//  Koumechan
//
//  Created by 上野　彰三 on 2014/07/08.
//
//

#ifndef __Koumechan__Friends__
#define __Koumechan__Friends__

#include "cocos2d.h"
#include "spine/json.h"

class Friends : public cocos2d::Ref
{
protected:
	Friends();
	virtual ~Friends() {};
	
	CC_SYNTHESIZE(long, m_id, Id);	// not use
	CC_SYNTHESIZE(long, m_loginId,LoginId);
	CC_SYNTHESIZE(cocos2d::Value,m_UUID,UUID);
	CC_SYNTHESIZE(cocos2d::Value,m_name,Name);
	CC_SYNTHESIZE(cocos2d::Value,m_url,URL);
	CC_SYNTHESIZE(cocos2d::Value,m_email,Email);
	
	
public:
	static Friends* createWithJson(Json* json);
	virtual bool loadFromSrv(Json* json);
};

#endif /* defined(__Koumechan__Friends__) */
