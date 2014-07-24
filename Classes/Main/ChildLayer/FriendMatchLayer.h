//
//  FriendMatchLayer.h
//  Koumechan
//
//  Created by 上野　彰三 on 2014/07/08.
//
//

#ifndef __Koumechan__FriendMatchLayer__
#define __Koumechan__FriendMatchLayer__

#include "cocos2d.h"
#include "KoumeChan.h"
#include "KcScene.h"
#include "FriendMatch.h"
#include "cocosbuilder/cocosbuilder.h"
#include "KcListLayer.h"

class FriendMatchLayer : public KcListLayer
{
protected:
    virtual void onEnter();
	virtual void onExit();
//	virtual void onEnterTransitionDidFinish();
	virtual bool init();
	
	
	virtual std::string getHeaderString() ;
	virtual bool enable(long index);
	
	virtual bool isSameCell(cocos2d::extension::TableViewCell* preCell,long index) ;
	virtual cocos2d::extension::TableViewCell* getNewCell(long index) ;
	virtual long numberOfCellsInTableView(cocos2d::extension::TableView* table) ;
	virtual void onTouchCell(long id);

	void gotFriendMatchList(Json* json);
	void createdFriendMatch(Json* json);
	void gotInvitedMatchList(Json* json);
	void startedFriendMatch(Json* json);
	void gotMyFriendMatch(Json* json);
	void canceledFriendMatch(Json* json);
	
	void getFriendMatchList(bool bRenew = false);
	void createFriendMatch(long index);
	void getInvitedFriendMatchList();
	void startFriendMatch(long index);
	void getMyFriendMatch();
	void startGuestPuzzleScene();
	
	CC_SYNTHESIZE(bool, m_guestNode,GuestNode);
	CC_SYNTHESIZE(bool, m_guestPlay,GuestPlay);
	
public:
	FriendMatchLayer() ;
	virtual ~FriendMatchLayer() ;
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(FriendMatchLayer, create);
	
	virtual cocos2d::extension::Control::Handler onResolveCCBCCControlSelector(cocos2d::Ref* pTarget,const char* pSelectorName);
	void tappedRenew(cocos2d::Ref* pSender,cocos2d::extension::Control::EventType pCCControlEvent);

	void startSocketIO(FriendMatch* pMatch);
	void stopSocketIO(FriendMatch* pMatch);
	
	void sioSystemEvent(cocos2d::network::SIOClient *client, const std::string& data);
	void sioJoinedRoom(cocos2d::network::SIOClient *client, const std::string& data);
	
	void sioCompeJoin(cocos2d::network::SIOClient *client, const std::string& data);
	
	void sioStartSession(cocos2d::network::SIOClient *client, const std::string& data);
	

	void delegateHttpResponse(KcScene::COMMAND_NO no, Json *recieveJson);
	
	void cancelFriendMatch();
	
};

#endif /* defined(__Koumechan__FriendMatchLayer__) */
