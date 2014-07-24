//
//  FriendMatchList.h
//  Koumechan
//
//  Created by 上野　彰三 on 2014/07/08.
//
//

#ifndef __Koumechan__FriendMatchList__
#define __Koumechan__FriendMatchList__

#include "cocos2d.h"
#include "FriendMatch.h"

class FriendMatchList : public cocos2d::Ref
{
protected:
	FriendMatchList();
	virtual ~FriendMatchList();
	virtual bool init();
	
	cocos2d::Map<long,FriendMatch*> m_data;
	
public:
	static FriendMatchList* createFriendMatchList(Json* json,cocos2d::Value myUUID);
	FriendMatch* getFriendMatch(long idx)		{return m_data.at(idx);};
	void setFriendMatch(FriendMatch* fr);
	long size()	{return m_data.size();};
	bool loadFromServer(Json* json,cocos2d::Value myUUID);
	virtual void clearData();
	void clearMatchData(long id);
	bool hasOwnMatch();
	FriendMatch* getOwnFriendMatch();
};


#endif /* defined(__Koumechan__FriendMatchList__) */
