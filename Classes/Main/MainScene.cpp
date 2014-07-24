//
//  MainScene.cpp
//  koumeChan
//
//  Created by 上野　彰三 on 2014/03/12.
//
//

#include "MainScene.h"
#include "Modal.h"
#include "JsonKeyString.h"
#include "MainUILayer.h"
#include "MainUILayerLoader.h"
#include "MajorQuestLayerLoader.h"
#include "MinorQuestLayerLoader.h"
#include "FriendMatchLayer.h"
#include "FriendMatchLayerLoader.h"

using namespace cocos2d;
using namespace cocosbuilder;

MainScene::MainScene() : m_Node(NULL)
{
}

MainScene::~MainScene()
{
	log("main scene destructor");
	CC_SAFE_RELEASE(m_Node);
}

MainScene* MainScene::create()
{
	MainScene* pRet = new MainScene();
	if(pRet && pRet->init()){
		pRet->autorelease();
	}
	else{
		CC_SAFE_DELETE(pRet);
		pRet = NULL;
	}
	return pRet;
}
const char* MainScene::getConnectInfoDlgTitleMessage()
{
	return "通信中・・・";
};
const char* MainScene::getConnectInfoDlgBodyMessage()
{
	switch(getCommandNo()){
		case KcScene::FRIEND_MATCH_CREATE:
			return "セッションを作成中";
		case KcScene::FRIEND_MATCH_GET:
			return "フレンドリストを取得中";
		case KcScene::FRIEND_MATCH_START:
			if(getWaiting()){
				return "相手の応答を待っています";
			}
			return "セッションサーバに接続中";
		case KcScene::FRIEND_MATCH_CANCELL:
		case KcScene::FRIEND_MATCH_LIST:
			break;
		default:
			break;
	}
	return "通信中・・・";
};
const char* MainScene::getConnectInfoCancelButtonText()
{
	switch(getCommandNo()){
		case KcScene::FRIEND_MATCH_CREATE:
		case KcScene::FRIEND_MATCH_GET:
		case KcScene::FRIEND_MATCH_LIST:
		case KcScene::FRIEND_MATCH_START:
		case KcScene::FRIEND_MATCH_CANCELL:
			break;
		default:
			break;
	}
	return "CANCEL";
};
void MainScene::onConnectInfoCancel()
{
	FriendMatchLayer* matchLayer = (FriendMatchLayer*)getNode();
	switch(getCommandNo()){
		case KcScene::FRIEND_MATCH_START:
			// TODO:キャンセル処理を呼ぶ
			matchLayer->cancelFriendMatch();
			break;
		case KcScene::FRIEND_MATCH_CREATE:
		case KcScene::FRIEND_MATCH_GET:
		case KcScene::FRIEND_MATCH_LIST:
		case KcScene::FRIEND_MATCH_CANCELL:
			break;
		default:
			break;
	}
	// TODO:ダウンロードを中止しました　アプリを終了すべし
};
bool MainScene::init()
{
	if(Scene::init()){
		log("MainScene init");
		
		NodeLoaderLibrary* NodeLoaderLibrary = NodeLoaderLibrary::newDefaultNodeLoaderLibrary();
		NodeLoaderLibrary->registerNodeLoader(MAIN_UILAYER_CLASS, MainUILayerLoader::loader());
		CCBReader* ccbReader = new CCBReader(NodeLoaderLibrary);
		Node* node = ccbReader->readNodeGraphFromFile(MAIN_UILAYER_FILE);
		if(node != NULL){
			this->addChild(node, LZ_MAIN,LTAG_MAIN);
			ccbReader->release();
			long quest = KoumeChan::getInstance()->getMajorQuest();
			long direct = KoumeChan::getInstance()->getDirection();
			if(quest >= 0 ){
				showMinorQuestLayer();
			}
			else if(direct >= 0){
				showMajorQuestLayer();
			}

			
			
			return true;
		}
	}
	return false;
}
void MainScene::getServerTime()
{
	std::string sendJson = StringUtils::format("{%s}",KoumeChan::getInstance()->getSessionJsonString().c_str());
	KcScene::sendHttpRequest(KcScene::GET_SERVERTIME, sendJson.c_str());
}
bool MainScene::gotServerTime(Json *json)
{
	if(checkBasicResponse(json)){
//		std::string serverTime = Json_getString(json, JS_UNIX_TIME, "");
		long long serverTime = KoumeChan::getLLong(json, JS_UNIX_TIME, 0LL);

		log("%lld" ,serverTime);
//		time_t localTime = time(NULL);
//		log("check server time server %s %d",serverTime.c_str(),v.asInt());
	}
	return false;
};



void MainScene::onRecieve(KcScene::COMMAND_NO no, Json *recieveJson)
{
	bool bSuccess = true;
	FriendMatchLayer* matchLayer = (FriendMatchLayer*)getNode();
	switch(no){
		case KcScene::GET_SERVERTIME:
			gotServerTime(recieveJson);
			break;
		case KcScene::FRIEND_MATCH_LIST:
		case KcScene::FRIEND_MATCH_CREATE:
		case KcScene::FRIEND_MATCH_GET:
		case KcScene::FRIEND_MATCH_START:
		case KcScene::FRIEND_MATCH_CHECK:
		case KcScene::FRIEND_MATCH_CANCELL:
			matchLayer->delegateHttpResponse(no,recieveJson);
			break;
		default:
			break;
	}
	if(bSuccess){
		
	}
};






void MainScene::showMajorQuestLayer(bool bShow)
{
	if(getNode()){
		getNode()->removeFromParentAndCleanup(true);
		setNode(NULL);
	}
	if(!getChildByTag(LTAG_MAJOR)){
		NodeLoaderLibrary* NodeLoaderLibrary = NodeLoaderLibrary::newDefaultNodeLoaderLibrary();
		NodeLoaderLibrary->registerNodeLoader(MAJOR_QUESTLAYER_CLASS, MajorQuestLayerLoader::loader());
		CCBReader* ccbReader = new CCBReader(NodeLoaderLibrary);
		Node* node = ccbReader->readNodeGraphFromFile(MAJOR_QUESTLAYER_FILE);
		if(node != NULL){
			this->addChild(node, LZ_CHILD,LTAG_MAJOR);
			ccbReader->release();
			

		}
		setNode(node);
	}
}

void MainScene::showFriendMatchLayer()
{
	if(getNode()){
		getNode()->removeFromParentAndCleanup(true);
		setNode(NULL);
	}
	if(!getChildByTag(LTAG_FRIEND_MATCH)){
		NodeLoaderLibrary* NodeLoaderLibrary = NodeLoaderLibrary::newDefaultNodeLoaderLibrary();
		NodeLoaderLibrary->registerNodeLoader(FRIEND_MATCHLAYER_CLASS, FriendMatchLayerLoader::loader());
		CCBReader* ccbReader = new CCBReader(NodeLoaderLibrary);
		Node* node = ccbReader->readNodeGraphFromFile(FRIEND_MATCHLAYER_FILE);
		if(node != NULL){
			this->addChild(node, LZ_CHILD,LTAG_FRIEND_MATCH);
			ccbReader->release();
		}
		setNode(node);
	}
}
void MainScene::showMinorQuestLayer(bool bShow)
{
	if(getNode()){
		getNode()->removeFromParentAndCleanup(true);
		setNode(NULL);
	}
	if(!getChildByTag(LTAG_MINOR)){
		NodeLoaderLibrary* NodeLoaderLibrary = NodeLoaderLibrary::newDefaultNodeLoaderLibrary();
		NodeLoaderLibrary->registerNodeLoader(MINOR_QUESTLAYER_CLASS, MinorQuestLayerLoader::loader());
		CCBReader* ccbReader = new CCBReader(NodeLoaderLibrary);
		Node* node = ccbReader->readNodeGraphFromFile(MINOR_QUESTLAYER_FILE);
		if(node != NULL){
			this->addChild(node, LZ_CHILD,LTAG_MINOR);
			ccbReader->release();
		}
		setNode(node);
	}
}

