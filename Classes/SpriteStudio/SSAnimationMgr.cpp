//
//  SSAnimationMgr.cpp
//  Koumechan
//
//  Created by 上野　彰三 on 2014/07/31.
//
//

#include "SSAnimationMgr.h"

using namespace cocos2d;
using namespace std;

SSAnimationMgr* SSAnimationMgr::m_instance = NULL;

SSAnimationMgr::SSAnimationMgr()
{
	
};

SSAnimationMgr::~SSAnimationMgr()
{
	m_animations.clear();
	m_counter.clear();
};

SSAnimationMgr* SSAnimationMgr::getInstance()
{
	if(!m_instance){
		m_instance = new SSAnimationMgr();
	}
	return m_instance;
};

SSAnimationData* SSAnimationMgr::loadAnimation(long lNo,int tag,cocos2d::Value& fName,cocos2d::Value& path)
{
	long key = lNo * 100 + tag;
	SSAnimationData* pData = getAnimation(lNo,tag);
	if(pData == NULL){
		pData = SSAnimationData::createWithFilePath(fName,path);
		if(pData ){
			m_counter[key] = 0;
			m_animations.insert(key,pData);
		}
	}
	m_counter[key] = m_counter[key] + 1;
	return pData;
}

SSAnimationData* SSAnimationMgr::getAnimation(long lNo,int tag)
{
	long key = lNo * 100 + tag;
	return m_animations.at(key);
}

void SSAnimationMgr::releaseAnimation(long lNo,int tag)
{
	long key = lNo * 100 + tag;
	if(m_animations.find(key) != m_animations.end()){
		m_counter[key] = m_counter[key] - 1;
		m_animations.erase(key);
	}
}