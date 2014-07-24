//
//  MasterNPC.h
//  Koumechan
//
//  Created by 上野　彰三 on 2014/06/23.
//
//

#ifndef __Koumechan__MasterNPC__
#define __Koumechan__MasterNPC__


#include "cocos2d.h"
#include "BaseNamedMaster.h"
#include "BaseConditionMaster.h"

class MasterNPC : public BaseNamedMaster
{
protected:
	MasterNPC();
	virtual ~MasterNPC();
	virtual bool initWithJson(Json* json);
	
	CC_SYNTHESIZE(long,m_level,Level);
	CC_SYNTHESIZE(long,m_hp,HP);
	cocos2d::Vector<BaseConditionMaster*> m_words;

public:
	static MasterNPC* createWithJson(Json* json);
	virtual std::string toJsonString();
	virtual void registerToParent() {};
	long getWordsCount()	{return m_words.size();};
	BaseConditionMaster* getWords(long l);
	void addWords(BaseConditionMaster* master);
	virtual void clearChild(MASTERNO masterNo);
	
};


#endif /* defined(__Koumechan__MasterNPC__) */
