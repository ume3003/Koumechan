//
//  MajorQuest.h
//  koumeChan
//
//  Created by 上野　彰三 on 2014/03/25.
//
//

#ifndef __koumeChan__MajorQuest__
#define __koumeChan__MajorQuest__


#include "cocos2d.h"
#include "BaseNamedMaster.h"

class MajorQuest : public BaseNamedMaster
{
protected:
	MajorQuest();
	virtual ~MajorQuest();
	virtual bool initWithJson(Json* json);
	std::vector<long> m_minorQuestNo;
	
	CC_SYNTHESIZE(long, m_DirectionNo, DirectionNo);
	
public:
	static MajorQuest* createWithJson(Json* json);
	virtual std::string toJsonString();
	std::vector<long> getMinorQuestNos()	{ return m_minorQuestNo;};
	void addMinorQuestNo(long questNo);
	virtual void registerToParent();
	virtual void clearChild(MASTERNO masterNo);	
};

#endif /* defined(__koumeChan__MajorQuest__) */
