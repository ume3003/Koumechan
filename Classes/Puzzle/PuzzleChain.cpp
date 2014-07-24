//
//  PuzzleChain.cpp
//  koumeChan
//
//  Created by 上野　彰三 on 2014/04/07.
//
//

#include "PuzzleChain.h"
#include "JsonKeyString.h"

using namespace cocos2d;
using namespace std;

PuzzleChain::PuzzleChain()
{
	m_bTop = false;
}

PuzzleChain::~PuzzleChain()
{
	m_tags.clear();
}

PuzzleChain* PuzzleChain::create(int chainCount)
{
	PuzzleChain* pRet = new PuzzleChain();
	if(pRet){
		pRet->autorelease();
		switch(chainCount){
			case 3:
				pRet->setType(KoumeChan::CHAIN_THREE);
				break;
			case 4:
				pRet->setType(KoumeChan::CHAIN_FOUR);
				break;
			case 5:
				pRet->setType(KoumeChan::CHAIN_FIVE);
				break;
			default:
				pRet->setType(KoumeChan::NO_CHAIN);
				break;
		}
	}
	else{
		CC_SAFE_DELETE(pRet);
		pRet = NULL;
	}
	return pRet;
}

PuzzleChain* PuzzleChain::createWithJson(Json *json)
{
	PuzzleChain* pRet = new PuzzleChain();
	if(pRet){
		pRet->autorelease();
		pRet->setType((KoumeChan::CHAINTYPE)KoumeChan::getInt(json, JS_KEY_NO, KoumeChan::CHAIN_THREE));
		Json* data = Json_getItem(json, JS_DATA);
		Json* row = NULL;
		int i = 0;
		for (row = data->child,i = 0; row ; row = row->next, ++i) {
			int rowData = KoumeChan::getInt(row, JS_ID, -1);
			pRet->addChain(rowData);
		}
	}
	else{
		CC_SAFE_DELETE(pRet);
		pRet = NULL;
	}
	return pRet;
	
}

int PuzzleChain::getChain(int index)
{
	if(0 <= index && index < getChainCount()){
		return m_tags.at(index);
	}
	return -1;
}
// "NO":"0","DATA":{[{"ID":0},{"ID":1}]}
std::string PuzzleChain::toJsonString()
{
	std::string str = StringUtils::format("%s,%s:{[",jsInt(JS_KEY_NO,getType()).c_str(),JS_DATA);
	for(int i = 0 ; i < getChainCount();i++){
		str = StringUtils::format("%s{%s}",str.c_str(),jsInt(JS_ID,getChain(i)).c_str()).c_str();
		if(i < getChainCount() - 1){
			str = StringUtils::format("%s,",str.c_str());
		}
	}
	str = StringUtils::format("%s]}",str.c_str());
	return str;
}

void PuzzleChain::addChain(PuzzleChain *chain)
{
	if(chain){
		for(int i = 0;i < chain->getChainCount();i++){
			int tag = chain->getChain(i);
			if(!hasTag(tag)){
				addChain(tag);
			}
		}
	}
};

bool PuzzleChain::hasTag(int tag)
{
	for(int i =0;i < getChainCount();i++){
		if(getChain(i) == tag){
			return false;
		}
	}
	return true;
}
