//
//  FriendMatch.h
//  Koumechan
//
//  Created by 上野　彰三 on 2014/07/08.
//
//

#ifndef __Koumechan__FriendMatch__
#define __Koumechan__FriendMatch__

#include "cocos2d.h"
#include "Friends.h"
#include "spine/json.h"

class FriendMatch : public cocos2d::Ref
{
protected:
	FriendMatch();
	virtual ~FriendMatch() {};
	
	CC_SYNTHESIZE(cocos2d::Value, m_uuid		,UUID);
	CC_SYNTHESIZE(int			, m_count		,Count);
	CC_SYNTHESIZE(long			, m_scenario	,Scenario);
	CC_SYNTHESIZE(bool			, m_owner		,Owner);
	CC_SYNTHESIZE(long long		, m_seed		,Seed);
	CC_SYNTHESIZE(cocos2d::Value, m_myUUID	,MyUUID);
	CC_SYNTHESIZE(cocos2d::Value, m_urUUID	,UrUUID);
	CC_SYNTHESIZE_RETAIN(Friends* ,m_myPlayer	,MyPlayer);
	CC_SYNTHESIZE_RETAIN(Friends* ,m_urPlayer	,UrPlayer);
	
	
public:
	static FriendMatch* createWithJson(Json* json,cocos2d::Value& myUUID);
	virtual bool loadFromSrv(Json* json,cocos2d::Value& myUUID);
	Friends* getFriends();
};

#endif /* defined(__Koumechan__FriendMatch__) */
