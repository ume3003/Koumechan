//
//  Wordd.h
//  Koumechan
//
//  Created by 上野　彰三 on 2014/06/25.
//
//

#ifndef __Koumechan__Wordd__
#define __Koumechan__Wordd__


#include "cocos2d.h"
#include "BaseNamedMaster.h"

class Words : public BaseNamedMaster
{
public:
	enum WORDS {
		HELLO	= 0,
		LOSE,
		WIN,
		STARTTURN,
		ENDTURN
	};
protected:
	Words();
	virtual ~Words();
	
	
public:
	static Words* createWithJson(Json* json);
	virtual std::string toJsonString();
	virtual void registerToParent() {};
	
};


#endif /* defined(__Koumechan__Wordd__) */
