//
//  FriendMatchLayer.cpp
//  Koumechan
//
//  Created by 上野　彰三 on 2014/07/08.
//
//

#include "FriendMatchLayer.h"
#include "KoumeChan.h"
#include "MainScene.h"
#include "KCDef.h"
#include "JsonKeyString.h"
#include "KcListCell.h"

using namespace cocos2d;
using namespace std;
using namespace cocos2d::extension;
using namespace cocos2d::network;

FriendMatchLayer::FriendMatchLayer()
{
	
}

FriendMatchLayer::~FriendMatchLayer()
{
	
}

bool FriendMatchLayer::init()
{
	if(KcListLayer::init()){
		return true;
	}
	return false;
};

void FriendMatchLayer::onEnter()
{
	KcListLayer::onEnter();
	getFriendMatchList();
	
}

void FriendMatchLayer::onExit()
{
	log("============FriendMatchlayer onExit================");
	KcListLayer::onExit();
}

std::string FriendMatchLayer::getHeaderString()
{
	return string("フレンドマッチ");
};
bool FriendMatchLayer::enable(long loginId)
{
	FriendMatchList* fMList = KoumeChan::getInstance()->getFriendMatchList();
	FriendList* fList = KoumeChan::getInstance()->getFriendList();
	if(fList) {
		long index = fList->findFriendIdx(loginId);
		if(index >= 0){
			Friends* f = fList->getFriend(index);
			if(fMList){
				if(fMList->hasOwnMatch()){
					FriendMatch* fM = fMList->getFriendMatch(f->getLoginId());
					if(fM){
						return fM->getOwner();
					}
				}
			}			
		}
	}
	return true;
};

long FriendMatchLayer::numberOfCellsInTableView(cocos2d::extension::TableView* table)
{
	FriendList* fList = KoumeChan::getInstance()->getFriendList();
	if(fList){
		return fList->size();
	}
	return 0L;
};

bool FriendMatchLayer::isSameCell(cocos2d::extension::TableViewCell* preCell,long index)
{
	FriendList* fList = KoumeChan::getInstance()->getFriendList();
	if(fList){
		KcListCell* preListCell = (KcListCell*)preCell;
		Friends* f = fList->getFriend(index);
		if(f){
			return preListCell->getId() == f->getLoginId();
		}
	}
	return false;
};

cocos2d::extension::TableViewCell* FriendMatchLayer::getNewCell(long index)
{
	FriendList* fList = KoumeChan::getInstance()->getFriendList();
	FriendMatchList* fMList = KoumeChan::getInstance()->getFriendMatchList();
	if(fList) {
		Friends* f = fList->getFriend(index);
		if(fMList && f){
			FriendMatch* fM = fMList->getFriendMatch(f->getLoginId());
			if(fM){
				string str = StringUtils::format("○ %s",V2C(f->getName()));
				return KcListCell::create(f->getLoginId(),Value(str),Value(""),Size(getCellWidth(),getCellHeight()));
			}
		}
		return KcListCell::create(f->getLoginId(),f->getName(),Value(""),Size(getCellWidth(),getCellHeight()));
	}
	KcListCell* cell = KcListCell::create(index, Value(StringUtils::format("No %ld",index)), Value(""), Size(getCellWidth(),getCellHeight()));
	return cell;
};
void FriendMatchLayer::onTouchCell(long id)
{
	FriendMatchList* fMList = KoumeChan::getInstance()->getFriendMatchList();
	if(fMList){
		FriendMatch* fM = fMList->getFriendMatch(id);
		if(fM){
			if(!fM->getOwner()){
				setGuestPlay(false);
				setGuestNode(false);
				startSocketIO(fM);
			}
			return ;
		}
	}
	createFriendMatch(id);
}

void FriendMatchLayer::tappedRenew(cocos2d::Ref* pSender,cocos2d::extension::Control::EventType pCCControlEvent)
{
	getFriendMatchList(true);
}

Control::Handler FriendMatchLayer::onResolveCCBCCControlSelector(cocos2d::Ref *pTarget, const char *pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "tappedBack"		, FriendMatchLayer::tappedRenew);
	return NULL;
}

void FriendMatchLayer::startSocketIO(FriendMatch* fr)
{
	if(fr){
		CallFunc* func = CallFunc::create([this,fr]{
			Value myUUID = KoumeChan::getInstance()->getUUID();
			KoumeChan::getInstance()->registerIOEvent(NR_SYSTEM_MESSAGE, CC_CALLBACK_2(FriendMatchLayer::sioSystemEvent,this));
			KoumeChan::getInstance()->registerIOEvent(NR_JOIN_ROOM, CC_CALLBACK_2(FriendMatchLayer::sioJoinedRoom,this));
			KoumeChan::getInstance()->registerIOEvent(NR_COMPETITOR_JOIN, CC_CALLBACK_2(FriendMatchLayer::sioCompeJoin,this));
			KoumeChan::getInstance()->registerIOEvent(NR_START_SESSION, CC_CALLBACK_2(FriendMatchLayer::sioStartSession,this));
			KoumeChan::getInstance()->sendSocketIOMessage(NS_ADD_USER, StringUtils::format("[{\"userUUID\":\"%s\",\"roomUUID\":\"%s\"}]",V2C(myUUID),V2C(fr->getUUID())));
		});
		KoumeChan::getInstance()->setFriendMatch(fr);
		KoumeChan::getInstance()->setOnConnectCallback(func);
		KoumeChan::getInstance()->initSocketIO();
	}
	
}
void FriendMatchLayer::sioSystemEvent(cocos2d::network::SIOClient *client, const std::string& data)
{
	log("KoumeChan::systemEvent called with data: %s", data.c_str());
	
};
void FriendMatchLayer::sioJoinedRoom(cocos2d::network::SIOClient *client, const std::string& data)
{
	FriendMatchList* matchList = KoumeChan::getInstance()->getFriendMatchList();
	FriendList* friendList = KoumeChan::getInstance()->getFriendList();
	if(matchList && friendList){
		Json* j = Json_create(data.c_str());
		Json* j1 = Json_getItem(j,"args");
		Json* json = j1->child;
		int retCode = Json_getInt(json, "retCode", -1);
		if(retCode >= 0){
			Json* dJson = Json_getItem(json, "msg");
			if(dJson){
				Value myUUID = KoumeChan::getInstance()->getUUID();
				FriendMatch* fM = FriendMatch::createWithJson(dJson, myUUID);
				if(fM && !fM->getOwner()){
					Friends* owner = fM->getMyPlayer();
					if(owner){
						long index = friendList->findFriendIdx(owner->getLoginId());
						startFriendMatch(index);						
					}
				}
			}
		}
		Json_dispose(j);
		
	}
	log("KoumeChan::JoindRoom called with data: %s", data.c_str());
};

void FriendMatchLayer::sioCompeJoin(cocos2d::network::SIOClient *client, const std::string& data)
{
	log("KoumeChan::CompeJoin called with data: %s", data.c_str());
	// もらったデータで自分の入室か対戦相手の入室か確認
	FriendMatchList* matchList = KoumeChan::getInstance()->getFriendMatchList();
	FriendList* friendList = KoumeChan::getInstance()->getFriendList();
	if(matchList && friendList){
		FriendMatch* fMatch = matchList->getOwnFriendMatch();
		if(fMatch){ // HOST
			Friends* f = fMatch->getUrPlayer();
			if(f){
				long index =friendList->findFriendIdx(f->getLoginId());
				startFriendMatch(index);
				return;
			}
			// TODO:エラー処理
			ConnectInfoDlg* pDlg = KoumeChan::getInstance()->getConnectInfoDialog(getParent());
			if(pDlg){
				pDlg->ExitDlg();
			}
		}
	}
};

void FriendMatchLayer::sioStartSession(cocos2d::network::SIOClient *client, const std::string& data)
{
	// 自分のだったら
	ConnectInfoDlg* pDlg = KoumeChan::getInstance()->getConnectInfoDialog(getParent());
	if(pDlg){
		pDlg->ExitDlg();
	}
	log("KoumeChan::startSession called with data: %s", data.c_str());
	
	FriendMatchList* matchList = KoumeChan::getInstance()->getFriendMatchList();
	FriendList* friendList = KoumeChan::getInstance()->getFriendList();
	if(matchList && friendList){
		FriendMatch* fMatch = matchList->getOwnFriendMatch();
		if(fMatch){ // HOST
			Friends* you = fMatch->getFriends();
			if(you){
				matchList->clearMatchData(you->getLoginId());
			}
			KoumeChan::getInstance()->setFriendMatch(fMatch);
			KoumeChan::getInstance()->showFriendMatchScene();
		}
		else{
			setGuestNode(true);
			startGuestPuzzleScene();
		}
	}
};

void FriendMatchLayer::stopSocketIO(FriendMatch* fr)
{
	if(fr){
		Value myUUID = KoumeChan::getInstance()->getUUID();
		KoumeChan::getInstance()->sendSocketIOMessage(NS_LEAVE_ROOM, StringUtils::format("[{\"userUUID\":\"%s\",\"roomUUID\":\"%s\"}]",V2C(myUUID),V2C(fr->getUUID())));
	}
	KoumeChan::getInstance()->destroySocketIO();
}



// フレンドとフレンドマッチのリストもらう
void FriendMatchLayer::getFriendMatchList(bool bRenew)
{
	std::string sendJson = StringUtils::format("{%s}",KoumeChan::getInstance()->getSessionJsonString().c_str());
	FriendList* fList = KoumeChan::getInstance()->getFriendList();
	if(bRenew || fList == NULL || (fList != NULL && fList->size() == 0)){
		MainScene* pScene = (MainScene*)getParent();
		pScene->setCommandNo(KcScene::FRIEND_MATCH_GET);
		KoumeChan::getInstance()->showConnectInfoDialog(pScene);
		((MainScene*)getParent())->sendHttpRequest(KcScene::FRIEND_MATCH_LIST, sendJson.c_str());
	}
};
// フレンドマッチつくる
void FriendMatchLayer::createFriendMatch(long loginId)
{
	FriendList* fList = KoumeChan::getInstance()->getFriendList();
	if(fList){
		long index = fList->findFriendIdx(loginId);
		if(index >= 0){
			Friends* f = fList->getFriend(index);
			std::string sendJson =
			StringUtils::format("{%s,%s,%s}",
								KoumeChan::getInstance()->getSessionJsonString().c_str(),
								jsStr(JS_FRIEND_COM,V2C(f->getEmail())).c_str(),
								jsLong(JS_SCENARIO, 0L).c_str());
			MainScene* pScene = (MainScene*)getParent();
			pScene->setWaiting(false);
			pScene->setCommandNo(KcScene::FRIEND_MATCH_CREATE);
			KoumeChan::getInstance()->showConnectInfoDialog(pScene);
			((MainScene*)getParent())->sendHttpRequest(KcScene::FRIEND_MATCH_CREATE, sendJson.c_str());
		}
		else{
			assert(false);
		}
	}
	else{
		assert(false);
	}
}
// 自分が招待されてるリストもらう
void FriendMatchLayer::getInvitedFriendMatchList()
{
	std::string sendJson =
	StringUtils::format("{%s}",
						KoumeChan::getInstance()->getSessionJsonString().c_str());
	// TODO:ここでダイアログ
	((MainScene*)getParent())->sendHttpRequest(KcScene::FRIEND_MATCH_LIST, sendJson.c_str());
	
}
// フレンドマッチを始める宣言
void FriendMatchLayer::startFriendMatch(long index)
{
	FriendList* fList = KoumeChan::getInstance()->getFriendList();
	FriendMatchList* matchList = KoumeChan::getInstance()->getFriendMatchList();
	if(index >= 0 && fList && matchList){
		Friends* f = fList->getFriend(index);
		if(f){
			std::string sendJson;
			FriendMatch* fM = matchList->getFriendMatch(f->getLoginId());
			if(fM->getOwner()){
				sendJson = StringUtils::format("{%s,%s,%s}",
					KoumeChan::getInstance()->getSessionJsonString().c_str(),
					jsStr(JS_FRIEND_COM,"").c_str(),
					jsStr(JS_FRIEND_COM_ID,V2C(fM->getUUID())).c_str()
				);
				
			}
			else{
				sendJson =	StringUtils::format("{%s,%s,%s}",
					KoumeChan::getInstance()->getSessionJsonString().c_str(),
					jsStr(JS_FRIEND_COM,V2C(f->getEmail())).c_str(),
					jsStr(JS_FRIEND_COM_ID,V2C(fM->getUUID())).c_str()
				);
			}
			((MainScene*)getParent())->sendHttpRequest(KcScene::FRIEND_MATCH_START, sendJson.c_str());
		}
	}
}


// 招待をとりけす
void FriendMatchLayer::cancelFriendMatch()
{
	FriendList* fList = KoumeChan::getInstance()->getFriendList();
	FriendMatchList* matchList = KoumeChan::getInstance()->getFriendMatchList();
	if(matchList && fList){
		FriendMatch* fM = matchList->getOwnFriendMatch();
		if(fM){
			Friends* f = fM->getUrPlayer();
			if(f){
				std::string sendJson =
				StringUtils::format("{%s,%s,%s}",
									KoumeChan::getInstance()->getSessionJsonString().c_str(),
									jsStr(JS_FRIEND_COM,V2C(f->getEmail())).c_str(),
									jsStr(JS_FRIEND_COM_ID,V2C(fM->getUUID())).c_str()
									);
				MainScene* pScene = (MainScene*)getParent();
				pScene->setCommandNo(KcScene::FRIEND_MATCH_CANCELL);
				KoumeChan::getInstance()->showConnectInfoDialog(pScene);
				((MainScene*)getParent())->sendHttpRequest(KcScene::FRIEND_MATCH_CANCELL, sendJson.c_str());
				stopSocketIO(fM);
			}
			
		}
	}
	
};
// 自分が招待してるか
void FriendMatchLayer::getMyFriendMatch()
{
	std::string sendJson =
	StringUtils::format("{%s}",
						KoumeChan::getInstance()->getSessionJsonString().c_str());
	// TODO:ここでダイアログ
	((MainScene*)getParent())->sendHttpRequest(KcScene::FRIEND_MATCH_CHECK, sendJson.c_str());
}

///////////////////////////////////////////////
//
//		ここからサーバ返答
//
//////////////////////////////////////////////////



void FriendMatchLayer::delegateHttpResponse(KcScene::COMMAND_NO no, Json *recieveJson)
{
	switch(no){
		case KcScene::FRIEND_MATCH_LIST:
			gotFriendMatchList(recieveJson);
			break;
		case KcScene::FRIEND_MATCH_CREATE:
			createdFriendMatch(recieveJson);
			break;
		case KcScene::FRIEND_MATCH_GET:
			gotFriendMatchList(recieveJson);
			break;
		case KcScene::FRIEND_MATCH_CANCELL:
			canceledFriendMatch(recieveJson);
			break;
		case KcScene::FRIEND_MATCH_START:
			startedFriendMatch(recieveJson);
			break;
		case KcScene::FRIEND_MATCH_CHECK:
			gotMyFriendMatch(recieveJson);
			break;
		default:
			break;
	}
	
}


// フレンドのリストと招待されてるリストもらった
// FriendList JS_FRIEND
// FriendMatchList JS_FRIEND_INVITE
void FriendMatchLayer::gotFriendMatchList(Json *json)
{
	ConnectInfoDlg* pDlg = KoumeChan::getInstance()->getConnectInfoDialog(getParent());
	if(pDlg){
		pDlg->ExitDlg();
	}

	if(json){
		Json* jList = Json_getItem(json,JS_FRIEND);
		Json* jMatch = Json_getItem(json,JS_FRIEND_INVITE);
		FriendList* list = KoumeChan::getInstance()->getFriendList();
		if(jList){
			if(list == NULL){
				list = FriendList::createFriendList(jList);
				KoumeChan::getInstance()->setFriendList(list);
			}
			else{
				list->clearData();
				list->loadFromServer(jList);
			}
		}
		if(jMatch){
			FriendMatchList* matchList = KoumeChan::getInstance()->getFriendMatchList();
			Value myUUID = KoumeChan::getInstance()->getUUID();
			if(matchList){
				matchList->clearData();
				matchList->loadFromServer(jMatch, myUUID);
			}
			else{
				matchList = FriendMatchList::createFriendMatchList(jMatch, myUUID);
				KoumeChan::getInstance()->setFriendMatchList(matchList);
			}
			FriendMatch* myMatch = matchList->getOwnFriendMatch();
			if(myMatch){
				MainScene* pScene = (MainScene*)getParent();
				pScene->setCommandNo(KcScene::FRIEND_MATCH_START);
				pScene->setWaiting(false);
				KoumeChan::getInstance()->showConnectInfoDialog(pScene);
				startSocketIO(myMatch);
			}
		}
		cocos2d::extension::TableView* pView = getTableView();
		if(pView){
			pView->reloadData();
		}
	}
}
// フレンドマッチの登録がすんだ
// FRIEND_COM
void FriendMatchLayer::createdFriendMatch(Json *json)
{
	ConnectInfoDlg* pDlg = KoumeChan::getInstance()->getConnectInfoDialog(getParent());
	if(pDlg){
		pDlg->ExitDlg();
	}
	FriendMatchList* matchList = KoumeChan::getInstance()->getFriendMatchList();
	Value myUUID = KoumeChan::getInstance()->getUUID();
	Json* jMatch = Json_getItem(json,JS_FRIEND_COM);
	if(jMatch){
		if(!matchList){
			matchList = FriendMatchList::createFriendMatchList(jMatch, myUUID);
			KoumeChan::getInstance()->setFriendMatchList(matchList);
		}
		FriendMatch* fr = FriendMatch::createWithJson(jMatch, myUUID);
		if(fr){
			matchList->setFriendMatch(fr);
			MainScene* pScene = (MainScene*)getParent();
			pScene->setCommandNo(KcScene::FRIEND_MATCH_START);
			pScene->setWaiting(false);
			KoumeChan::getInstance()->showConnectInfoDialog(pScene);
			
			startSocketIO(fr);
		}
	}
}
// 招待されてるリストもらった
// array FRIEND_INVITE
void FriendMatchLayer::gotInvitedMatchList(Json *json)
{
	ConnectInfoDlg* pDlg = KoumeChan::getInstance()->getConnectInfoDialog(getParent());
	if(pDlg){
		pDlg->ExitDlg();
	}
	FriendMatchList* matchList = KoumeChan::getInstance()->getFriendMatchList();
	Value myUUID = KoumeChan::getInstance()->getUUID();
	Json* jInvite = Json_getItem(json, JS_FRIEND_INVITE);
	if(matchList){
		matchList->clearData();
		matchList->loadFromServer(jInvite, myUUID);
	}
	else{
		matchList = FriendMatchList::createFriendMatchList(jInvite, myUUID);
		KoumeChan::getInstance()->setFriendMatchList(matchList);
	}
	cocos2d::extension::TableView* pView = getTableView();
	if(pView){
		pView->reloadData();
	}
	
}
// フレンドマッチをはじめちゃった
// FRIEND_COM
// FRIEND_ME or FRIEND_YOU
void FriendMatchLayer::startedFriendMatch(Json *json)
{
	ConnectInfoDlg* pDlg = KoumeChan::getInstance()->getConnectInfoDialog(getParent());
	if(pDlg){
		pDlg->ExitDlg();
	}
	Value myUUID = KoumeChan::getInstance()->getUUID();
	Json* jCom = Json_getItem(json,JS_FRIEND_COM);
	Json* jMe = Json_getItem(json,JS_FRIEND_ME);
	Json* jUr = Json_getItem(json,JS_FRIEND_YOU);
	if(jCom){
		FriendMatch* fM = FriendMatch::createWithJson(jCom, myUUID);
		MainScene* pScene = (MainScene*)getParent();
		pScene->setCommandNo(KcScene::FRIEND_MATCH_START);
		if(fM){
			if(jMe){
//				fr = fM->getUrPlayer();
				pScene->setWaiting(true);
			}
			else if(jUr){
//				fr = fM->getMyPlayer();
//				startSocketIO(fM);
				KoumeChan::getInstance()->setFriendMatch(fM);
				setGuestPlay(true);
				startGuestPuzzleScene();
			}
			
		}
		KoumeChan::getInstance()->showConnectInfoDialog(pScene);
		
	}
}
// 自分が招待してるマッチ
void FriendMatchLayer::gotMyFriendMatch(Json *json)
{
	
}
// フレンドマッチをキャンセルした
void FriendMatchLayer::canceledFriendMatch(Json *json)
{
	ConnectInfoDlg* pDlg = KoumeChan::getInstance()->getConnectInfoDialog(getParent());
	if(pDlg){
		pDlg->ExitDlg();
	}

	FriendMatchList* matchList = KoumeChan::getInstance()->getFriendMatchList();
	Value myUUID = KoumeChan::getInstance()->getUUID();
	Json* jCom = Json_getItem(json,JS_FRIEND_COM);
	if(matchList && jCom){
		FriendMatch* fM = FriendMatch::createWithJson(jCom, myUUID);
		if(fM){
			Friends* fr = fM->getUrPlayer();
			if(fr){
				matchList->clearMatchData(fr->getLoginId());
			}
		}
	}
}

void FriendMatchLayer::startGuestPuzzleScene()
{
	if(getGuestNode() && getGuestPlay()){
		FriendMatch* fMatch = KoumeChan::getInstance()->getFriendMatch();
		FriendMatchList* matchList = KoumeChan::getInstance()->getFriendMatchList();
		if(fMatch &&  matchList){
			Friends* you = fMatch->getFriends();
			if(you){
				matchList->clearMatchData(you->getLoginId());
			}
		}
		KoumeChan::getInstance()->showFriendMatchScene();
	}
}


