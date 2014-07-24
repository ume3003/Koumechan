//
//  PuzzleChainManager.h
//  koumeChan
//
//  Created by 上野　彰三 on 2014/04/07.
//
//

#ifndef __koumeChan__PuzzleChainManager__
#define __koumeChan__PuzzleChainManager__

#include "cocos2d.h"
#include "KoumeChan.h"
#include "PuzzleChain.h"

class PuzzleChainManager : public cocos2d::Ref
{
public:

	static PuzzleChainManager* create();
	static PuzzleChainManager* createWithJson(Json* json);
	std::string toJsonString();
	
	PuzzleChain* getChain(int index);
	void addChain(PuzzleChain* chain);
	long getChainSize()	{ return m_chains.size();};
	
	void clearChains()	{ m_chains.clear();};
	
protected:
	PuzzleChainManager();
	virtual ~PuzzleChainManager();
	
	cocos2d::Vector<PuzzleChain*> m_chains;
};

#endif /* defined(__koumeChan__PuzzleChainManager__) */
