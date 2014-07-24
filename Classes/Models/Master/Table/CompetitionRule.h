//
//  CompetitionRule.h
//  koumeChan
//
//  Created by 上野　彰三 on 2014/04/01.
//
//

#ifndef __koumeChan__CompetitionRule__
#define __koumeChan__CompetitionRule__

#include "cocos2d.h"
#include "BaseNamedMaster.h"

class CompetitionRule : public BaseNamedMaster
{
protected:
	CompetitionRule();
	virtual ~CompetitionRule();
	
	
public:
	static CompetitionRule* createWithJson(Json* json);
	virtual std::string toJsonString();
	virtual void registerToParent() {};
	
};

#endif /* defined(__koumeChan__CompetitionRule__) */
