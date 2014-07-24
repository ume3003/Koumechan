//
//  FriendMatchList.cpp
//  Koumechan
//
//  Created by 上野　彰三 on 2014/07/08.
//
//

#include "FriendMatchList.h"
#include "JsonKeyString.h"
#include "KoumeChan.h"
#include "KCDef.h"

using namespace cocos2d;
using namespace std;

FriendMatchList::FriendMatchList()
{
	
};

FriendMatchList::~FriendMatchList()
{
	m_data.clear();
};
bool FriendMatchList::init()
{
	return true;
}

void FriendMatchList::setFriendMatch(FriendMatch *friends)
{
	if(friends != NULL){
		Friends* ur = NULL;
		if(friends->getOwner()){
			ur = friends->getUrPlayer();
		}
		else{
			ur = friends->getMyPlayer();
		}
		if(ur){
			m_data.insert(ur->getLoginId(),friends);
		}
	}
}

void FriendMatchList::clearData()
{
	m_data.clear();
}

void FriendMatchList::clearMatchData(long id)
{
	m_data.erase(id);
}

bool FriendMatchList::loadFromServer(Json *json,Value myUUID)
{
	if(json != NULL){
		Json* row = NULL;
		int i = 0;
		clearData();
		for (row = json->child,i = 0; row ; row = row->next, ++i) {
			FriendMatch* master = FriendMatch::createWithJson(row,myUUID);
			setFriendMatch(master);
		}
		return true;
	}
	return false;
};

FriendMatchList* FriendMatchList::createFriendMatchList(Json* json,Value myUUID)
{
	FriendMatchList* pRet = new FriendMatchList();
	if(pRet && pRet->loadFromServer(json,myUUID)){
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}

bool FriendMatchList::hasOwnMatch()
{
	Map<long,FriendMatch*>::iterator it = m_data.begin();
	while(it != m_data.end()){
		FriendMatch* match = (FriendMatch*)(*it).second;
		if(match->getOwner()){
			return true;
		}
		++it;
	}
	return false;
}
FriendMatch* FriendMatchList::getOwnFriendMatch()
{
	Map<long,FriendMatch*>::iterator it = m_data.begin();
	while(it != m_data.end()){
		FriendMatch* match = (FriendMatch*)(*it).second;
		if(match->getOwner()){
			return match;
		}
		++it;
	}
	return NULL;
};




