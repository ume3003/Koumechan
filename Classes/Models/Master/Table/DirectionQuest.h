//
//  DirectionQuest.h
//  koumeChan
//
//  Created by 上野　彰三 on 2014/03/17.
//
//

#ifndef __koumeChan__Direction__
#define __koumeChan__Direction__

#include "cocos2d.h"
#include "BaseNamedMaster.h"

class DirectionQuest : public BaseNamedMaster
{
protected:
	DirectionQuest();
	virtual ~DirectionQuest();
	std::vector<long> m_majorQuestNo;
	std::vector<long> m_minorQuestNo;
	
public:
	enum ENUM_DIRECTION {
		EAST = 0,
		WEST,
		SOUTH,
		NORTH,
		CENTER
	};
	
	virtual std::string toJsonString();
	static DirectionQuest* createWithJson(Json* json);
	std::vector<long> getMajorQuestNos()	{ return m_majorQuestNo;};
	std::vector<long> getMinorQuestNos()	{ return m_minorQuestNo;};
	void addMajorQuestNo(long questNo);
	void addMinorQuestNo(long questNo);
	virtual void registerToParent() {};
	virtual void clearChild(MASTERNO masterNo);
};

#endif /* defined(__koumeChan__Direction__) */
