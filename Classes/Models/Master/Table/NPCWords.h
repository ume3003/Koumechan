//
//  NPCWords.h
//  Koumechan
//
//  Created by 上野　彰三 on 2014/06/25.
//
//

#ifndef __Koumechan__NPCWords__
#define __Koumechan__NPCWords__

#include "cocos2d.h"
#include "KoumeChan.h"
#include "BaseConditionMaster.h"

class NPCWords : public BaseConditionMaster
{
protected:
	NPCWords();
	virtual ~NPCWords();
	virtual bool initWithJson(Json* json);
	
	CC_SYNTHESIZE(cocos2d::Value, m_word, Word);
	CC_SYNTHESIZE(cocos2d::Value, m_image,Image);
	
public:
	static NPCWords* createWithJson(Json* json);
	virtual std::string toJsonString();
	virtual void registerToParent();
	
};

#endif /* defined(__Koumechan__NPCWords__) */
