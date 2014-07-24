//
//  CompetitionRuleManager.h
//  koumeChan
//
//  Created by 上野　彰三 on 2014/04/01.
//
//

#ifndef __koumeChan__CompetitionRuleManager__
#define __koumeChan__CompetitionRuleManager__

#include "cocos2d.h"
#include "KoumeChan.h"
#include "CompetitionRule.h"
#include "BaseMasterManager.h"

class CompetitionRuleManager : public BaseMasterManager
{
protected:
	
public:
	static CompetitionRuleManager* create(long version);
	virtual std::string getTableName();
	virtual BaseMaster* createMaster(Json* json);
	virtual int getTableNo()		{ return BaseMaster::COMPETITION_RULE_MASTER;};
	CompetitionRule* getCompetitionRule(long no);
};


#endif /* defined(__koumeChan__CompetitionRuleManager__) */
