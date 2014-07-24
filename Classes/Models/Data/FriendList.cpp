//
//  FriendList.cpp
//  Koumechan
//
//  Created by 上野　彰三 on 2014/07/08.
//
//

#include "FriendList.h"
#include "JsonKeyString.h"
#include "KoumeChan.h"
#include "KCDef.h"

using namespace cocos2d;
using namespace std;

FriendList::FriendList()
{
	
};

FriendList::~FriendList()
{
	m_data.clear();
};
bool FriendList::init()
{
	return true;
}

void FriendList::setFriend(Friends *friends)
{
	if(friends != NULL){
		m_data.pushBack(friends);
	}
}

void FriendList::clearData()
{
	m_data.clear();
}

bool FriendList::loadFromServer(Json *jsonObject)
{
	Json* json = Json_getItem(jsonObject,JS_FRIEND);
	if(json != NULL){
		Json* row = NULL;
		int i = 0;
		clearData();
		for (row = json->child,i = 0; row ; row = row->next, ++i) {
			Friends* master = Friends::createWithJson(row);
			setFriend(master);
		}
		return true;
	}
	return false;
};

FriendList* FriendList::createFriendList(Json* json)
{
	FriendList* pRet = new FriendList();
	if(pRet && pRet->loadFromServer(json)){
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}

long FriendList::findFriendIdx(long loginId)
{
	for(long i = 0; i < m_data.size();i++){
		Friends* f = m_data.at(i);
		if(f && f->getLoginId() == loginId){
			return i;
		}
	}
	return -1;
};



