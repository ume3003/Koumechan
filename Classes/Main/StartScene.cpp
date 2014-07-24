//
//  StartScene.cpp
//  koumeChan
//
//  Created by 上野　彰三 on 2014/03/11.
//
//
#include <time.h>
#include "StartScene.h"
#include "Modal.h"
#include "JsonKeyString.h"
#include "StartLayer.h"
#include "StartLayerLoader.h"
#include "LocalDatabase.h"
#include "GameCharacter.h"

using namespace cocos2d;
using namespace cocosbuilder;

StartScene::StartScene() : m_layer(NULL)
{
	setStartState(SIGNINING);
}

StartScene::~StartScene()
{
	CC_SAFE_RELEASE(m_layer);
}

StartScene* StartScene::create()
{
	StartScene* pRet = new StartScene();
	if(pRet && pRet->init()){
		pRet->autorelease();
	}
	else{
		CC_SAFE_DELETE(pRet);
		pRet = NULL;
	}
	return pRet;
}
const char* StartScene::getConnectInfoDlgTitleMessage()
{
	return "通信中・・・";
};
const char* StartScene::getConnectInfoDlgBodyMessage()
{
	
	switch(getStartState()){
		case NOTHING:
			break;
		case SIGNINING:
			return "サインインしています";
		case SIGNOUTING:
			return "サインアウトしています";
		case LOGINING:
			return "ログインしています";
		case LOADVER:
			return "バージョンデータを取得しています";
		case LOADMASTER:
			return getLoadingString().c_str();
		case LOADING:
			return "データを取得しています";
		default:
			break;
	}
	return "通信中・・・";
};
const char* StartScene::getConnectInfoCancelButtonText()
{
	return "CANCEL";
};
void StartScene::onConnectInfoCancel()
{
	// TODO:ダウンロードを中止しました　アプリを終了すべし
};
void StartScene::login()
{
	setStartState(LOGINING);
	KoumeChan::getInstance()->showConnectInfoDialog(this);
	std::string str =KoumeChan::getInstance()->getLoginJsonString();
	log("%s",str.c_str());
	sendHttpRequest(KcScene::LOGIN,str.c_str());
};

void StartScene::signin()
{
	KoumeChan* chan = KoumeChan::getInstance();
	if(NativeCall::isSignIn()){
		setStartState(SIGNOUTING);
		NativeCall::GPPSSingOut();
		chan->setSignIn(false);
		chan->savePref();
	}
	else{
		KoumeChan::getInstance()->showConnectInfoDialog(this);
		setStartState(SIGNINING);
		NativeCall::GPPSSignIn();
		KoumeChan::getInstance()->setUUID(Value(""));
	}
}
bool StartScene::init()
{
	if(Scene::init()){
		log("init");
		NativeCall::addDelegate(this);
		
		NodeLoaderLibrary* NodeLoaderLibrary = NodeLoaderLibrary::newDefaultNodeLoaderLibrary();
		NodeLoaderLibrary->registerNodeLoader(START_LAYER_CLASS, StartLayerLoader::loader());
		CCBReader* ccbReader = new CCBReader(NodeLoaderLibrary);
		Node* node = ccbReader->readNodeGraphFromFile(START_LAYER_FILE);
		setLayer(node);
		if(node != NULL){
			this->addChild(node, 99);
			ccbReader->release();
			LocalDatabase::getInstance()->init();
//////////////////////////
//			KoumeChan::getInstance()->clearLocalMasterData();
//////////////////////////
			KoumeChan::getInstance()->setMinorQuest(-1);
			KoumeChan::getInstance()->setMajorQuest(-1);
			KoumeChan::getInstance()->setDirection(-1);
			return true;
		}
	}
	return false;
}
bool StartScene::loadedMasterData(Json* json)
{
	KoumeChan* chan = KoumeChan::getInstance();
	if(!checkBasicResponse(json)){
		return false;
	}
	long long version = KoumeChan::getLLong(json, JS_VERSION, -1);
	log("version is %lld",version);
	int masterNo = KoumeChan::getInt(json,JS_MASTER_NO,-1);
	log("loaded master data %d ",masterNo);
	if(masterNo >= 0){
		if(version >= 0){
			chan->setVersion(masterNo, version);
			Json* data = Json_getItem(json, JS_DATA);
			BaseMasterManager* manager = chan->getMasterManager((BaseMaster::MASTERNO)masterNo);
			if(manager != NULL){
				manager->setVersion(version);
				manager->loadFromServer(data);
				loadMaster();
			}
			else{
				log("error manager is null");
				return false;
			}
		}
		else{
			log("error version invalid");
			return false;
		}
	}
	else{
		log("error masterNo invalid");
		return false;
	}
	return true;
	
};
bool StartScene::loadedMasterVersion(Json *json)
{
	if(!checkBasicResponse(json)){
		return false;
	}
	Json* data = Json_getItem(json,JS_DATA);
	if(data == NULL){
		log("error version data is null");
		return false;
	}
	log("loadedMasterVersion");
	KoumeChan::getInstance()->loadServerVersion(data);
	loadMaster();
	return true;
}
void StartScene::loadMaster()
{
	KoumeChan* chan = KoumeChan::getInstance();
	ConnectInfoDlg* dlg = KoumeChan::getInstance()->getConnectInfoDialog(this);
	std::string appJsonString = KoumeChan::getInstance()->getSessionJsonString();
	setCurrentLoading(0);
	for(int i = 0 ; i < BaseMaster::MASTERNO::MASTER_MAX;i++){
		if(chan->checkNewVersion(i)){
			log("load new master data %d",i);
			std::string masterJsonString = jsInt(JS_MASTER_NO, i);
			std::string jsonString = StringUtils::format("{%s,%s}",appJsonString.c_str(),masterJsonString.c_str());
				sendHttpRequest(KcScene::MASTER,jsonString.c_str());
			setStartState(LOADMASTER);
			setCurrentLoading(i);
			setLoadingString(StringUtils::format(
									   "データ取得中 %d/%d",
									   getCurrentLoading(),
									   BaseMaster::MASTER_MAX));
			
			if(dlg != NULL){
				dlg->updateTTF();
			}
			return;
		}
		else{
			log("use current master data %d",i);
		}
	}
	log("masterdata check and load finish");
	chan->savePref();
	if(dlg != NULL){
		dlg->ExitDlg();
	}
	NativeCall::addDelegate(NULL);
	KoumeChan::getInstance()->showMainScene();
}

bool StartScene::loadedLogin(Json *json)
{
	if(!checkBasicResponse(json)){
		return false;
	}
	long long unix_time = KoumeChan::getLLong(json, JS_UNIX_TIME, 0);
	time_t ios_time = time(NULL);
	log("unix = %lld,ios = %ld",unix_time,ios_time);
	
	std::string sessionid = Json_getString(json,JS_SESSION_ID,"");
	std::string uuid = Json_getString(json,JS_UUID,"");
	if(uuid.length() == 0){
		log("error uuid is null");
		return false;
	}
	Json* gameCharacter = Json_getItem(json,JS_GAMECHARACTER);
	if(!gameCharacter){
		log("error gameCharacter is null");
		return false;
	}
	GameCharacter* gc = GameCharacter::createWithJson(gameCharacter);
	KoumeChan::getInstance()->setGameCharacter(gc);
	KoumeChan::getInstance()->setSessionId(Value(sessionid));
	KoumeChan::getInstance()->setUUID(Value(uuid));
	KoumeChan::getInstance()->savePref();
	log("+++++++++uuid = %s sesionid = %s ",uuid.c_str(),sessionid.c_str());
	std::string appJsonString = KoumeChan::getInstance()->getSessionJsonString();
	std::string jsonString = StringUtils::format("{%s}",appJsonString.c_str());

	setStartState(LOADVER);
	ConnectInfoDlg* dlg = KoumeChan::getInstance()->getConnectInfoDialog(this);
	if(dlg != NULL){
		dlg->updateTTF();
	}
	sendHttpRequest(KcScene::MASTER_VERSION,jsonString.c_str());
	return true;
};



void StartScene::onRecieve(KcScene::COMMAND_NO no, Json *recieveJson)
{
	bool bSuccess = true;
	switch(no){
		case KcScene::LOGIN:
			bSuccess = loadedLogin(recieveJson);
			break;
		case KcScene::MASTER:
			bSuccess = loadedMasterData(recieveJson);
			break;
		case KcScene::MASTER_VERSION:
			bSuccess = loadedMasterVersion(recieveJson);
			break;
		default:
			break;
	}
	if(!bSuccess){
		ConnectInfoDlg* dlg = KoumeChan::getInstance()->getConnectInfoDialog(this);
		if(dlg != NULL){
			dlg->ExitDlg();
		}
	}
};

bool StartScene::onResult(int resultType,const char* gguid,const char* gmail,const char* gurl,const char* username)
{
	StartLayer* layer = (StartLayer*)getLayer();
	KoumeChan* chan = KoumeChan::getInstance();
	log("signin result:%d %s %s %s %s ",resultType,gguid,gmail,gurl,username);
	if(resultType == 0 || resultType == 1){
		
		chan->setSignIn(true);
		chan->setGPPUuid(Value(gguid));
		chan->setMailAddress(Value(gmail));
		chan->setProfileUrl(Value(gurl));
		chan->setDisplayName(Value(username));
		chan->savePref();
		layer->refreshSignInButton();
	}
	if(resultType < 0){
		chan->setSignIn(false);
		chan->savePref();
		Value uuid = chan->getUUID();
		
		layer->refreshSignInButton();
	}
	ConnectInfoDlg* dlg = KoumeChan::getInstance()->getConnectInfoDialog(this);
	if(dlg != NULL){
		dlg->ExitDlg();
	}
	return true;
};