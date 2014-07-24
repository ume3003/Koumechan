//
//  FriendList.h
//  Koumechan
//
//  Created by 上野　彰三 on 2014/07/08.
//
//

#ifndef __Koumechan__FriendList__
#define __Koumechan__FriendList__

#include "Friends.h"

class FriendList : public cocos2d::Ref
{
protected:
	FriendList();
	virtual ~FriendList();
	virtual bool init();
	
	cocos2d::Vector<Friends*> m_data;

public:
	static FriendList* createFriendList(Json* json);
	Friends* getFriend(long idx)		{return m_data.at(idx);};
	long findFriendIdx(long loginId);
	void setFriend(Friends* fr);
	long size()	{return m_data.size();};
	bool loadFromServer(Json* json);
	virtual void clearData();
};


#endif /* defined(__Koumechan__FriendList__) */
