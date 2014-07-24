//
//  MinorQuest.h
//  koumeChan
//
//  Created by 上野　彰三 on 2014/03/25.
//
//

#ifndef __koumeChan__MinorQuest__
#define __koumeChan__MinorQuest__


#include "cocos2d.h"
#include "BaseNamedMaster.h"
#include "BaseConditionMaster.h"

class MinorQuest : public BaseNamedMaster
{
protected:
	MinorQuest();
	virtual ~MinorQuest();
	virtual bool initWithJson(Json* json);
	
	CC_SYNTHESIZE(long, m_DirectionNo, DirectionNo);
	CC_SYNTHESIZE(long, m_MajorQuestNo, MajorQuestNo);
	CC_SYNTHESIZE(long, m_mapNo,MapNo);
	CC_SYNTHESIZE(long, m_npcNo,NPCNo);
	CC_SYNTHESIZE(int , m_attackCount, AttackCount);
	
	cocos2d::Vector<BaseConditionMaster*> m_appearances;
	cocos2d::Vector<BaseConditionMaster*> m_units;
	cocos2d::Vector<BaseConditionMaster*> m_clears;
	cocos2d::Vector<BaseConditionMaster*> m_rewards;
	
public:
	static MinorQuest* createWithJson(Json* json);
	virtual std::string toJsonString();
	virtual void registerToParent();
	
	long getAppearanceCount()	{return m_appearances.size();};
	long getUnitCount()			{return m_units.size();};
	long getClearCount()		{return m_clears.size();};
	long getRewardCount()		{return m_rewards.size();};
	
	BaseConditionMaster* getAppearance(long l);
	BaseConditionMaster* getUnit(long l);
	BaseConditionMaster* getClear(long l);
	BaseConditionMaster* getReward(long l);
	
	void addAppearance(BaseConditionMaster* master);
	void addUnit(BaseConditionMaster* master);
	void addClear(BaseConditionMaster* master);
	void addReward(BaseConditionMaster* master);
	virtual void clearChild(MASTERNO masterNo);
};


#endif /* defined(__koumeChan__MinorQuest__) */
