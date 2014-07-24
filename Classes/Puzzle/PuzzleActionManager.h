//
//  PuzzleActionManager.h
//  koumeChan
//
//  Created by 上野　彰三 on 2014/04/03.
//
//

#ifndef __koumeChan__PuzzleActionManager__
#define __koumeChan__PuzzleActionManager__

#include "cocos2d.h"
#include "PuzzleAction.h"

class PuzzleActionManager : public cocos2d::Ref
{
public:
	static PuzzleActionManager* create();
	static PuzzleActionManager* createWithJson(Json* json);
	
	void addAction(PuzzleAction* action);
	PuzzleAction* getAction(int index)	{return m_actions.at(index);};
	long getActionSize()	{ return m_actions.size();};
	void clear();
	std::string toJsonString();
	
protected:
	PuzzleActionManager();
	virtual ~PuzzleActionManager();
	virtual bool init();
	virtual bool initWithJson(Json* json);
	cocos2d::Vector<PuzzleAction*> m_actions;
};

#endif /* defined(__koumeChan__PuzzleActionManager__) */
