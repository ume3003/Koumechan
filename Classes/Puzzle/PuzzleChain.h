//
//  PuzzleChain.h
//  koumeChan
//
//  Created by 上野　彰三 on 2014/04/07.
//
//

#ifndef __koumeChan__PuzzleChain__
#define __koumeChan__PuzzleChain__

#include "cocos2d.h"
#include "KoumeChan.h"

class PuzzleChain : public cocos2d::Ref
{
public:
	
	static PuzzleChain* create(int chainCount);
	static PuzzleChain* createWithJson(Json* json);
	
	long getChainCount()		{ return m_tags.size();};
	int getChain(int index);
	void addChain(int tag)	{ m_tags.push_back(tag);};
	void addChain(PuzzleChain* chain);
	std::string toJsonString();
	
	
protected:
	PuzzleChain();
	~PuzzleChain();
	std::vector<int> m_tags;
	CC_SYNTHESIZE(KoumeChan::CHAINTYPE, m_type, Type);
	CC_SYNTHESIZE(bool,m_bTop,Top);
	bool hasTag(int tag);
};

#endif /* defined(__koumeChan__PuzzleChain__) */
