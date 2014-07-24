//
//  PuzzleChainManager.cpp
//  koumeChan
//
//  Created by 上野　彰三 on 2014/04/07.
//
//

#include "PuzzleChainManager.h"
#include "JsonKeyString.h"
using namespace cocos2d;
using namespace std;

PuzzleChainManager::PuzzleChainManager()
{
	
	
};

PuzzleChainManager::~PuzzleChainManager()
{
	m_chains.clear();
};

PuzzleChainManager* PuzzleChainManager::create()
{
	PuzzleChainManager* pRet = new PuzzleChainManager();
	if(pRet){
		pRet->autorelease();
	}
	else{
		CC_SAFE_DELETE(pRet);
		pRet = NULL;
	}
	return pRet;
};

PuzzleChainManager* PuzzleChainManager::createWithJson(Json* json)
{
	PuzzleChainManager* pRet = PuzzleChainManager::create();
	if(pRet){
		Json* data = Json_getItem(json, JS_DATA);
		Json* row = NULL;
		int i = 0;
		for (row = data->child,i = 0; row ; row = row->next, ++i) {
			PuzzleChain* chain = PuzzleChain::createWithJson(row);
			if(chain){
				pRet->addChain(chain);
			}
		}
	}
	return pRet;
};

PuzzleChain* PuzzleChainManager::getChain(int index)
{
	if(0 <= index && index < getChainSize()){
		return m_chains.at(index);
	}
	return NULL;
}

std::string PuzzleChainManager::toJsonString()
{
	string str = StringUtils::format("%s:{[",JS_DATA);
	for(int i = 0; i < getChainSize();i++){
		str = StringUtils::format("%s%s",str.c_str(),getChain(i)->toJsonString().c_str());
		if(i < getChainSize() -1){
			str = StringUtils::format("%s,",str.c_str());
		}
		
	}
	str = StringUtils::format("%s]}",str.c_str());
	return str;
}
void PuzzleChainManager::addChain(PuzzleChain* chain)
{
//	log("%s",chain->toJsonString().c_str());
	m_chains.pushBack(chain);
}