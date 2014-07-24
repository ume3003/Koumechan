//
//  PuzzleActionManager.cpp
//  koumeChan
//
//  Created by 上野　彰三 on 2014/04/03.
//
//

#include "PuzzleActionManager.h"

using namespace cocos2d;
using namespace std;

PuzzleActionManager::PuzzleActionManager()
{
	
}

PuzzleActionManager::~PuzzleActionManager()
{
	m_actions.clear();
}

PuzzleActionManager* PuzzleActionManager::create()
{
	PuzzleActionManager* pRet = new PuzzleActionManager();
	if(pRet && pRet->init()){
		pRet->autorelease();
	}
	else{
		CC_SAFE_DELETE(pRet);
		pRet = NULL;
	}
	return pRet;
}

bool PuzzleActionManager::init()
{
	m_actions.clear();
	return true;
}

PuzzleActionManager* PuzzleActionManager::createWithJson(Json* json)
{
	PuzzleActionManager* pRet = new PuzzleActionManager();
	if(pRet && pRet->initWithJson(json)){
		pRet->autorelease();
	}
	else{
		CC_SAFE_DELETE(pRet);
		pRet = NULL;
	}
	return pRet;
}

bool PuzzleActionManager::initWithJson(Json* json)
{
	// TODO: for network mode
	m_actions.clear();
	return true;
};
// {},{},{}
std::string PuzzleActionManager::toJsonString()
{
	std::string str = string("");
	for(int i = 0 ; i < getActionSize();i++){
		PuzzleAction* action = getAction(i);
		if(action){
			str = StringUtils::format("%s%s",str.c_str(),action->toJsonString().c_str());
			if(i < getActionSize() - 1){
				str = StringUtils::format("%s,",str.c_str());
			}
		}
	}
	return str;
};

void PuzzleActionManager::addAction(PuzzleAction* action)
{
	
	PuzzleAction* lastAction = getActionSize() == 0 ? NULL : m_actions.at(m_actions.size() - 1);
	if(lastAction &&
	   lastAction->getAction() == PuzzleAction::PZ_DOWN &&
	   action->getAction() == PuzzleAction::PZ_DOWN){
		lastAction->extendEndPoint(action->getPos(),action->getDuration());
	}
	else{
		m_actions.pushBack(action);
	}
};

void PuzzleActionManager::clear()
{
	m_actions.clear();
}