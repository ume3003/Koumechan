//
//  KoumeChan.cpp
//  koumeChan
//
//  Created by 上野　彰三 on 2014/03/11.
//
//

#include "KoumeChan.h"
#include "ConnectInfoDlgLoader.h"
#include "YNDlgLoader.h"
#include "StartScene.h"
#include "MainScene.h"
#include "PuzzleScene.h"
#include "QuestScene.h"
#include "CompetitionScene.h"
#include "LocalDatabase.h"
#include "JsonKeyString.h"

#include "DirectionManager.h"
#include "MajorQuestManager.h"
#include "MinorQuestManager.h"
#include "MasterMapManager.h"
#include "MasterUnitManager.h"
#include "ItemManager.h"
#include "ScenarioManager.h"
#include "CompetitionRuleManager.h"

#include "ConditionKindManager.h"
#include "CharacterColumnManager.h"
#include "RankManager.h"
#include "SkillManager.h"

#include "QuestUnitManager.h"
#include "QuestAppearanceManager.h"
#include "QuestClearManager.h"
#include "QuestRewardManager.h"

#include "ScenarioRuleManager.h"
#include "ScenarioUnitManager.h"

#include "MasterUnitSkillManager.h"
#include "ForceManager.h"
#include "MasterNPCManager.h"
#include "NPCWordsManager.h"
#include "WordsManager.h"
#include "BaseDamageManager.h"


using namespace cocos2d;
using namespace std;
using namespace cocosbuilder;
using namespace cocos2d::network;

KoumeChan* KoumeChan::m_singleton = NULL;

KoumeChan::KoumeChan() : m_gameCharacter(NULL),m_SocketIO(nullptr),m_friendList(NULL),m_friendMatchList(NULL),m_onConnectCallback(NULL),m_friendMatch(NULL)
{
	m_OpenSocket = false;
};
KoumeChan::~KoumeChan()
{
	destroySocketIO();
	CC_SAFE_RELEASE(m_gameCharacter);
	CC_SAFE_RELEASE(m_SocketIO);
	CC_SAFE_RELEASE(m_friendList);
	CC_SAFE_RELEASE(m_friendMatchList);
	CC_SAFE_RELEASE(m_friendMatch);
}
KoumeChan* KoumeChan::getInstance()
{
	if(m_singleton == NULL){
		m_singleton = new KoumeChan();
		m_singleton->initVersions();
	}
	return m_singleton;
};
void KoumeChan::initVersions()
{
	for(int i = 0 ; i < BaseMaster::MASTER_MAX;i++){
		setVersion(i, -1);
		setServerVersion(i, -1);
	}
	setMailAddress(Value(""));
	setDisplayName(Value(""));
	setProfileUrl(Value(""));
	setGPPUuid(Value(""));
	setSessionId(Value(""));
	loadPref();
	loadLocalMasterData();
};

////////////////////////////////////////////////////////////////////////////////////
//	method for local master data
///////////////////////////////////////////////////////////////////////////////////
void KoumeChan::clearLocalMasterData()
{
	// local Version will be -1
	// delete local data
	log("------------clear local data --------------------");
	for(int i = 0 ; i < BaseMaster::MASTER_MAX;i++){
		setVersion(i, -1);
		setServerVersion(i, -1);
	}
	LocalDatabase::getInstance()->clearAllMaster();
	log("------------clear local data --------------------");
	savePref();
}
void KoumeChan::loadLocalMasterData()
{
	DirectionManager* directionManager = DirectionManager::create(getVersion(BaseMaster::DIRECT_MASTER));
	if(directionManager){
		setMasterManager(BaseMaster::DIRECT_MASTER, directionManager);
	}
	MajorQuestManager* majorManager = MajorQuestManager::create(getVersion(BaseMaster::MAJOR_QUEST_MASTER));
	if(majorManager){
		setMasterManager(BaseMaster::MAJOR_QUEST_MASTER, majorManager);
		majorManager->registerToParentAll();
	}
	MinorQuestManager* minorManager = MinorQuestManager::create(getVersion(BaseMaster::MINOR_QUEST_MASTER));
	if(minorManager){
		setMasterManager(BaseMaster::MINOR_QUEST_MASTER, minorManager);
		minorManager->registerToParentAll();
	}
	MasterMapManager* mapManager = MasterMapManager::create(getVersion(BaseMaster::MAP_MASTER));
	if(mapManager){
		setMasterManager(BaseMaster::MAP_MASTER, mapManager);
	}

	MasterUnitManager* unitManager = MasterUnitManager::create(getVersion(BaseMaster::UNIT_MASTER));
	if(unitManager){
		setMasterManager(BaseMaster::UNIT_MASTER, unitManager);
	}
	ItemManager* itemManager = ItemManager::create(getVersion(BaseMaster::SPECIAL_ITEM_MASTER));
	if(itemManager){
		setMasterManager(BaseMaster::SPECIAL_ITEM_MASTER,itemManager);
	}
	ScenarioManager* scenarioManager = ScenarioManager::create(getVersion(BaseMaster::SCENARIO_MASTER));
	if(scenarioManager){
		setMasterManager(BaseMaster::SCENARIO_MASTER, scenarioManager);
	}
	CompetitionRuleManager* compManager = CompetitionRuleManager::create(getVersion(BaseMaster::COMPETITION_RULE_MASTER));
	if(compManager){
		setMasterManager(BaseMaster::COMPETITION_RULE_MASTER, compManager);
	}
	
	
	ConditionKindManager* kindManager = ConditionKindManager::create(getVersion(BaseMaster::CONDITION_KIND_MASTER));
	if(kindManager){
		setMasterManager(BaseMaster::CONDITION_KIND_MASTER, kindManager);
	}
	CharacterColumnManager* charaManager = CharacterColumnManager::create(getVersion(BaseMaster::CHARACTER_COL_MASTER));
	if(charaManager){
		setMasterManager(BaseMaster::CHARACTER_COL_MASTER, charaManager);
	}
	RankManager* rankManager = RankManager::create(getVersion(BaseMaster::RANK_MASTER));
	if(rankManager){
		setMasterManager(BaseMaster::RANK_MASTER, rankManager);
	}
	SkillManager* skillManager = SkillManager::create(getVersion(BaseMaster::SKILL_MASTER));
	if(skillManager){
		setMasterManager(BaseMaster::SKILL_MASTER,skillManager);
	}
	ForceManager* forceManager = ForceManager::create(getVersion(BaseMaster::FORCE_MASTER));
	if(forceManager){
		setMasterManager(BaseMaster::FORCE_MASTER,forceManager);
	}
	MasterNPCManager* npcManager = MasterNPCManager::create(getVersion(BaseMaster::NPC_MASTER));
	if(npcManager){
		setMasterManager(BaseMaster::NPC_MASTER,npcManager);
	}
		
	
	QuestUnitManager* quManager = QuestUnitManager::create(getVersion(BaseMaster::QUEST_UNIT_MASTER));
	if(quManager){
		setMasterManager(BaseMaster::QUEST_UNIT_MASTER, quManager);
		quManager->registerToParentAll();
	}
	QuestAppearanceManager* qaManager = QuestAppearanceManager::create(getVersion(BaseMaster::QUEST_APPEARANCE_MASTER));
	if(qaManager){
		setMasterManager(BaseMaster::QUEST_APPEARANCE_MASTER, qaManager);
		qaManager->registerToParentAll();
	}
	QuestRewardManager* qrManager = QuestRewardManager::create(getVersion(BaseMaster::QUEST_REWARD_MASTER));
	if(qrManager){
		setMasterManager(BaseMaster::QUEST_REWARD_MASTER, qrManager);
		qrManager->registerToParentAll();
	}
	QuestClearManager* qcManager = QuestClearManager::create(getVersion(BaseMaster::QUEST_CLEAR_MASTER));
	if(qcManager){
		setMasterManager(BaseMaster::QUEST_CLEAR_MASTER, qcManager);
		qcManager->registerToParentAll();
	}
	ScenarioRuleManager* srManager = ScenarioRuleManager::create(getVersion(BaseMaster::SCENARIO_RULE_MASTER));
	if(srManager){
		setMasterManager(BaseMaster::SCENARIO_RULE_MASTER, srManager);
		srManager->registerToParentAll();
	}
	ScenarioUnitManager* suManager = ScenarioUnitManager::create(getVersion(BaseMaster::SCENARIO_UNIT_MASTER));
	if(suManager){
		setMasterManager(BaseMaster::SCENARIO_UNIT_MASTER, suManager);
		suManager->registerToParentAll();
	}
	
	MasterUnitSkillManager* usManager = MasterUnitSkillManager::create(getVersion(BaseMaster::UNIT_SKILL_MASTER));
	if(usManager){
		setMasterManager(BaseMaster::UNIT_SKILL_MASTER,usManager);
		usManager->registerToParentAll();
	}
	NPCWordsManager* npcwManager = NPCWordsManager::create(getVersion(BaseMaster::NPC_WORDS_MASTER));
	if(npcwManager){
		setMasterManager(BaseMaster::NPC_WORDS_MASTER, npcwManager);
		npcwManager->registerToParentAll();
	}
	WordsManager* wManager = WordsManager::create(getVersion(BaseMaster::WORDS_MASTER));
	if(wManager){
		setMasterManager(BaseMaster::WORDS_MASTER, wManager);
	}
	BaseDamageManager* bdManager = BaseDamageManager::create(getVersion(BaseMaster::BASE_DAMAGE_MASTER));
	if(bdManager){
		setMasterManager(BaseMaster::BASE_DAMAGE_MASTER, bdManager);
	}
}
////////////////////////////////////////////////////////////////////////////////////
//	method for preference
///////////////////////////////////////////////////////////////////////////////////
void KoumeChan::loadPref()
{
	UserDefault* uDef = UserDefault::getInstance();
	setRescueString(Value(uDef->getStringForKey(PREF_RESCUESTRING,"")));
	setSignIn(uDef->getBoolForKey(PREF_ISSIGNIN, false));
	setUUID(Value(uDef->getStringForKey(PREF_UUID,"")));
	for(int i = 0; i < BaseMaster::MASTER_MAX; i++){
		setVersion(i, uDef->getIntegerForKey(StringUtils::format(PREF_VERSION,i).c_str(),-1));
	}
};

void KoumeChan::savePref()
{
	UserDefault* uDef = UserDefault::getInstance();
	uDef->setStringForKey(PREF_UUID, getUUID().asString());
	uDef->setStringForKey(PREF_RESCUESTRING, getRescueString().asString());
	uDef->setBoolForKey(PREF_ISSIGNIN, getSignIn());
	for(int i = 0; i < BaseMaster::MASTER_MAX; i++){
		uDef->setIntegerForKey(StringUtils::format(PREF_VERSION,i).c_str(),getVersion(i));
	}
	
	uDef->flush();
};
////////////////////////////////////////////////////////////////////////////////////
//	method for jsonstring
///////////////////////////////////////////////////////////////////////////////////
std::string KoumeChan::getSessionJsonString()
{
	return StringUtils::format("%s,%s",
							   jsStr(JS_SESSION_ID,getSessionId().asString().c_str()).c_str(),
							   jsStr(JS_UUID,getUUID().asString().c_str()).c_str());
}
std::string KoumeChan::getLoginJsonString()
{
	if(getSignIn()){// gppあり
		if(getUUID().asString().length() > 0){
			return StringUtils::format(
								   "{\"%s\":\"%s\",\"%s\":\"%s\",\"%s\":\"%s\",\"%s\":\"%s\",\"%s\":\"%s\"}",
								   JS_UUID,getUUID().asString().c_str(),
								   JS_GPP_UUID,getGPPUuid().asString().c_str(),
								   JS_DISPLAY_NAME,getDisplayName().asString().c_str(),
								   JS_MAIL_ADDRESS,getMailAddress().asString().c_str(),
								   JS_IMAGE_URL,getProfileUrl().asString().c_str()
								  );
		}
		else{
			return StringUtils::format(
								"{\"%s\":\"%s\",\"%s\":\"%s\",\"%s\":\"%s\",\"%s\":\"%s\"}",
									   JS_GPP_UUID,getGPPUuid().asString().c_str(),
									   JS_DISPLAY_NAME,getDisplayName().asString().c_str(),
									   JS_MAIL_ADDRESS,getMailAddress().asString().c_str(),
									   JS_IMAGE_URL,getProfileUrl().asString().c_str()
									   );
			
		}
	}
	// gppなし
	return StringUtils::format("{\"%s\":\"%s\"}",JS_UUID,getUUID().asString().c_str());
};
////////////////////////////////////////////////////////////////////////////////////
//	method for date time
///////////////////////////////////////////////////////////////////////////////////
string KoumeChan::getCurrentTimeString()
{
	time_t now = time(NULL);
	struct tm* date = localtime(&now);
	
	return StringUtils::format("%04d%02d%02d%02d%02d%02d",date->tm_year + 1900,date->tm_mon + 1,date->tm_mday,date->tm_hour,date->tm_min,date->tm_sec );
}

////////////////////////////////////////////////////////////////////////////////////
//	method for master version control
///////////////////////////////////////////////////////////////////////////////////
bool KoumeChan::loadServerVersion(Json *json)
{
	if(json){
		Json* row = NULL;
		int i = 0;
		for (row = json->child,i = 0; row ; row = row->next, ++i) {
			int masterNo = KoumeChan::getInt(row, JS_MASTER_NO, -1);
			long long version = KoumeChan::getLLong(row, JS_VERSION, -1);
			if(masterNo >= 0 && version >= 0){
				setServerVersion(masterNo, version);
			}
		}
		return true;
	}
	return false;
}

long long KoumeChan::getVersion(int masterNo)
{
	long long val = m_versions[masterNo];
	return val;
};
long long KoumeChan::getServerVersion(int masterNo)
{
	long long val = m_serverVersions[masterNo];
	return val;
}
void KoumeChan::setVersion(int masterNo, long long version)
{
	m_versions[masterNo]= version;
};
void KoumeChan::setServerVersion(int masterNo, long long version)
{
	m_serverVersions[masterNo]= version;
};
bool KoumeChan::checkNewVersion(int masterNo)
{
//	log("check masterVersion master is %d local %lld server %lld",masterNo,getVersion(masterNo),getServerVersion(masterNo));
	return getServerVersion(masterNo) > getVersion(masterNo);
};
////////////////////////////////////////////////////////////////////////////////////
//	show scenes
///////////////////////////////////////////////////////////////////////////////////
void KoumeChan::showMainScene()
{
	MainScene* pScene = MainScene::create();
	Scene* pS = CCTransitionZoomFlipX::create(1.0f,pScene);
	if(pS){
		if(Director::getInstance()->getRunningScene()){
			Director::getInstance()->replaceScene(pS);
		}
		else{
			Director::getInstance()->runWithScene(pS);
		}
	}
	
};

void KoumeChan::showStartScene()
{
	StartScene* pScene = StartScene::create();
	Scene* pS = CCTransitionZoomFlipY::create(1.0f,pScene);
	if(pS){
		if(Director::getInstance()->getRunningScene()){
			destroySocketIO();
			Director::getInstance()->replaceScene(pS);
		}
		else{
			Director::getInstance()->runWithScene(pS);
		}
	}
};

void KoumeChan::showPuzzleScene()
{
//	PuzzleScene* pScene = PuzzleScene::create();
	QuestScene* pScene = QuestScene::create();
	Scene* pS = CCTransitionZoomFlipY::create(1.0f,pScene);
	if(pS){
		if(Director::getInstance()->getRunningScene()){
			Director::getInstance()->replaceScene(pS);
		}
		else{
			Director::getInstance()->runWithScene(pS);
		}
	}
	
};
void KoumeChan::showFriendMatchScene()
{
	CompetitionScene* pScene = CompetitionScene::create();
	Scene* pS = CCTransitionZoomFlipY::create(1.0f,pScene);
	if(pS){
		if(Director::getInstance()->getRunningScene()){
			Director::getInstance()->replaceScene(pS);
		}
		else{
			Director::getInstance()->runWithScene(pS);
		}
	}
	
};
////////////////////////////////////////////////////////////////////////////////////
//	screen shot method
///////////////////////////////////////////////////////////////////////////////////
void KoumeChan::takeScreenShot(std::string strFileName)
{
	Size size = CCDirector::getInstance()->getWinSize();
	
	RenderTexture* texture = RenderTexture::create((int)size.width, (int)size.height);
	texture->setPosition(Point(size.width/2, size.height/2));
	texture->begin();
	Director::getInstance()->getRunningScene()->visit();
	texture->end();
	texture->saveToFile(strFileName.c_str(), Image::Format::PNG);
	
};
////////////////////////////////////////////////////////////////////////////////////
//	Helper for dialog
///////////////////////////////////////////////////////////////////////////////////
void KoumeChan::loadModal(cocos2d::Node* pParent,const char* className,NodeLoader* loader,const char* layoutName,int tag,bool bMove)
{
	Node* cNode = pParent->getChildByTag(tag);
	if(cNode != NULL){
		return;
	}
	NodeLoaderLibrary* NodeLoaderLibrary = NodeLoaderLibrary::newDefaultNodeLoaderLibrary();
	NodeLoaderLibrary->registerNodeLoader(className, loader);
	CCBReader* ccbReader = new CCBReader(NodeLoaderLibrary);
	Node* node = ccbReader->readNodeGraphFromFile(layoutName);
	Point endPoint = Point(pParent->getContentSize().width / 2 - node->getContentSize().width / 2,pParent->getContentSize().height / 2 - node->getContentSize().height / 2);
	Point startPos = Point(0 - node->getContentSize().width / 2,pParent->getContentSize().height / 2 - node->getContentSize().height / 2);
	if(bMove){
		node->setPosition(startPos);
		pParent->addChild(node, 100, tag);
		MoveTo* move = MoveTo::create(0.2f, endPoint);
		Sequence* act =  Sequence::create(move,NULL);
		node->runAction(act);
	}
	else{
		node->setPosition(endPoint);
		pParent->addChild(node, 100, tag);
	}
	ccbReader->release();
};

cocos2d::Node* KoumeChan::getModal(cocos2d::Node* pParent,int tag)
{
	return pParent->getChildByTag(tag);
};

void KoumeChan::showYNDialog(Node* pParent)
{
	loadModal(pParent, YNDLG_LAYER_CLASS, YNDlgLoader::loader(), YNDLG_LAYER_FILE,YNDLG);
};
void KoumeChan::showConnectInfoDialog(Node* pParent)
{
	loadModal(pParent, CONNECTINFODLG_LAYER_CLASS, ConnectInfoDlgLoader::loader(), CONNECTINFODLG_LAYER_FILE,CONNECTINFODLG,false);
};
ConnectInfoDlg* KoumeChan::getConnectInfoDialog(cocos2d::Node *pParent)
{
	ConnectInfoDlg* dlg = (ConnectInfoDlg*)pParent->getChildByTag(CONNECTINFODLG);
	return dlg;
}
/////////////////////////////////////////////////////////////
//	helper for websocket access
////////////////////////////////////////////////////////////
void KoumeChan::onConnect(network::SIOClient* client)
{
	log("KoumeChan::onConnect called");
	if(client == getSocketIO()){
		m_OpenSocket = true;
//		sendSocketIOMessage("global", "[{\"name\":\"myname\",\"message\":\"this is message from cocos2d\"}]");
		if(getOnConnectCallback() != NULL){
			getOnConnectCallback()->execute();
		}
	}
	
}

void KoumeChan::onMessage(network::SIOClient* client, const std::string& data)
{
	log("KoumeChan::onMessage received: %s", data.c_str());
}

void KoumeChan::onClose(network::SIOClient* client)
{
	log("KoumeChan::onClose called");
	
	if(client == getSocketIO()) {
//		destroySocketIO();
	}
	
}

void KoumeChan::onError(network::SIOClient* client, const std::string& data)
{
	log("KoumeChan::onError received: %s", data.c_str());
	m_OpenSocket = false;
	
}
void KoumeChan::reconnectSocketIO()
{
	destroySocketIO();
	initSocketIO();
};
void KoumeChan::sendSocketIOMessage(std::string eventName,std::string message)
{
	if(m_OpenSocket && getSocketIO())
	{
		getSocketIO()->emit(eventName, message);
		log("send SocketIO %s:%s",eventName.c_str(),message.c_str() );
	}
}
void KoumeChan::globalIOEvent(cocos2d::network::SIOClient *client, const std::string& data)
{
	log("KoumeChan::globalIOEvent called with data: %s", data.c_str());
};


void KoumeChan::initSocketIO()
{
	if(!m_OpenSocket){
		setSocketIO(SocketIO::connect(SOCKETIO_URL, *this));
		m_OpenSocket = true;
		registerIOEvent("global",CC_CALLBACK_2(KoumeChan::globalIOEvent, this));
	}

};
void KoumeChan::registerIOEvent(std::string eventName,SIOEvent event)
{
	if(m_OpenSocket && getSocketIO()){
		getSocketIO()->on(eventName,event);
	}
};

void KoumeChan::destroySocketIO()
{
	if(m_OpenSocket && getSocketIO()){
		getSocketIO()->disconnect();
		CC_SAFE_DELETE(m_SocketIO);
		m_OpenSocket = false;
	}
};

////////////////////////////////////////////////////////////////////////////////////
//	Helper for http access
///////////////////////////////////////////////////////////////////////////////////
void KoumeChan::send(const char* pTag,const char* pData,const char* pURL,Ref* target,const cocos2d::network::ccHttpRequestCallback& httpcallback)
{
	std::vector<std::string> headers ;
	headers.push_back(JSON_HEADER);
	const char* pTargetURL = ccsf("%s%s",TARGET_URL,pURL);
	
	log("%s : %s",pTargetURL,pData);
	
	HttpRequest* request = new HttpRequest();
	request->setUrl(pTargetURL);
	request->setRequestType(HttpRequest::Type::POST);
	request->setHeaders(headers);
	
	request->setResponseCallback(httpcallback);
	request->setRequestData(pData, (int)strlen(pData));
	request->setTag(pTag);
	HttpClient::getInstance()->send(request);
	request->release();
};

const char* KoumeChan::getTag(HttpResponse *response)
{
	if(response != NULL && response->getHttpRequest() != NULL){
		return response->getHttpRequest()->getTag();
	}
	return NULL;
};

Json* KoumeChan::responseToJson(HttpClient *sender,HttpResponse *response)
{
    if (!response){
		log("response is null");
        return NULL;
    }
    
    if (!response->isSucceed()){
        log("response code:%ld error buffer: %s", response->getResponseCode(),response->getErrorBuffer());
        return NULL;
    }
    
    // dump data
	unsigned long nLen =response->getResponseData()->size();
	char szTmp[nLen];
    for (unsigned int i = 0; i < nLen; i++){
		szTmp[i] = (*(response->getResponseData()))[i];
    }
	
	std::string str = std::string(szTmp,nLen);
#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	log("recieve json:%ld %ld %s",nLen,str.length(),str.c_str());
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	log("recieve json:%ld %d %s",nLen,str.length(),str.c_str());
#endif
	Json* json = Json_create(str.c_str());
	return json;
};
////////////////////////////////////////////////////////////////////////////////////
//	Helper for json parse
///////////////////////////////////////////////////////////////////////////////////
int KoumeChan::getInt(Json* json,const char* tag,int defalutValue)
{
	Json* tgt = Json_getItem(json,tag);
	if(tgt != NULL){
		if(tgt->type == Json_Number){
			return Json_getInt(json, tag, defalutValue);
		}
		std::string s = Json_getString(json,tag,"");
		if(s.length() == 0){
			return defalutValue;
		}
		return atoi(s.c_str());
	}
	return defalutValue;
}

long KoumeChan::getLong(Json* json,const char* tag,long defalutValue)
{
	Json* tgt = Json_getItem(json,tag);
	if(tgt != NULL){
		if(tgt->type == Json_Number){
			return Json_getInt(json, tag, defalutValue);
		}
		std::string s = Json_getString(json,tag,"");
		if(s.length() == 0){
			return defalutValue;
		}
		return atol(s.c_str());
	}
	return defalutValue;
}

long long KoumeChan::getLLong(Json* json,const char* tag,long long defalutValue)
{
	Json* tgt = Json_getItem(json,tag);
	if(tgt != NULL){
		if(tgt->type == Json_Number){
			return Json_getInt(json, tag, defalutValue);
		}
		std::string s = Json_getString(json,tag,"");
		if(s.length() == 0){
			return defalutValue;
		}
		return atoll(s.c_str());
	}
	return defalutValue;
}
float KoumeChan::getFloat(Json* json,const char* tag,float defaultValue)
{
	Json* tgt = Json_getItem(json,tag);
	if(tgt != NULL){
		if(tgt->type == Json_Number){
			return Json_getFloat(json, tag, defaultValue);
		}
		std::string s = Json_getString(json,tag,"");
		if(s.length() == 0){
			return defaultValue;
		}
		return atof(s.c_str());
	}
	return defaultValue;
};

KoumeChan::CHAINTYPE KoumeChan::chainCountToType(int count)
{
	switch(count){
		case 3:
			return CHAIN_THREE;
		case 4:
			return CHAIN_FOUR;
		case 5:
			return CHAIN_FIVE;
		default:
			break;
	}
	return NO_CHAIN;
};

////////////////////////////////////////////////////////////////////////////////////
//	Helper for master data
///////////////////////////////////////////////////////////////////////////////////
DirectionQuest* KoumeChan::getDirectionMaster(long masterNo)
{
	if(masterNo < 0){
		masterNo = getDirection();
	}
	return (DirectionQuest*)getMasterManager(BaseMaster::DIRECT_MASTER)->getMaster(masterNo);
}
MajorQuest* KoumeChan::getMajorQuestMaster(long masterNo)
{
	if(masterNo < 0){
		masterNo = getMajorQuest();
	}
	return (MajorQuest*)getMasterManager(BaseMaster::MAJOR_QUEST_MASTER)->getMaster(masterNo);
	
}
MinorQuest* KoumeChan::getMinorQuestMaster(long masterNo)
{
	if(masterNo < 0){
		masterNo = getMinorQuest();
	}
	return (MinorQuest*)getMasterManager(BaseMaster::MINOR_QUEST_MASTER)->getMaster(masterNo);
}
MasterMap* KoumeChan::getMapMaster(long masterNo)
{
	return (MasterMap*)getMasterManager(BaseMaster::MAP_MASTER)->getMaster(masterNo);
}
MasterUnit* KoumeChan::getUnitMaster(long masterNo)
{
	return (MasterUnit*)getMasterManager(BaseMaster::UNIT_MASTER)->getMaster(masterNo);
}
long KoumeChan::getUnitForce(long masterNo)
{
	MasterUnit* pUnit = getUnitMaster(masterNo);
	if(pUnit){
		return pUnit->getForceNo();
	}
	return 0;
}

Item* KoumeChan::getItemMaster(long masterNo)
{
	return (Item*)getMasterManager(BaseMaster::SPECIAL_ITEM_MASTER)->getMaster(masterNo);
}
Scenario* KoumeChan::getScenarioMaster(long masterNo)
{
	return (Scenario*)getMasterManager(BaseMaster::SCENARIO_MASTER)->getMaster(masterNo);
}
CompetitionRule* KoumeChan::getCompetitionRuleMaster(long masterNo)
{
	return (CompetitionRule*)getMasterManager(BaseMaster::COMPETITION_RULE_MASTER)->getMaster(masterNo);
}

ConditionKind* KoumeChan::getConditionKindMaster(long masterNo)
{
	return (ConditionKind*)getMasterManager(BaseMaster::CONDITION_KIND_MASTER)->getMaster(masterNo);
}
CharacterColumn* KoumeChan::getCharacterColumnMaster(long masterNo)
{
	return (CharacterColumn*)getMasterManager(BaseMaster::CHARACTER_COL_MASTER)->getMaster(masterNo);
}
Rank* KoumeChan::getRankMaster(long masterNo)
{
	return (Rank*)getMasterManager(BaseMaster::RANK_MASTER)->getMaster(masterNo);
}
Skill* KoumeChan::getSkillMaster(long masterNo)
{
	return (Skill*)getMasterManager(BaseMaster::SKILL_MASTER)->getMaster(masterNo);
}
Force* KoumeChan::getForceMaster(long masterNo)
{
	return (Force*)getMasterManager(BaseMaster::FORCE_MASTER)->getMaster(masterNo);
}
MasterNPC* KoumeChan::getNPCMaster(long masterNo)
{
	return (MasterNPC*)getMasterManager(BaseMaster::NPC_MASTER)->getMaster(masterNo);
}
BaseDamage* KoumeChan::getBaseDamageMaster(long masterNo)
{
	return (BaseDamage*)getMasterManager(BaseMaster::BASE_DAMAGE_MASTER)->getMaster(masterNo);
}

void KoumeChan::changeDirection(long newDirection)
{
	long oldDirection = getDirection();
	if(oldDirection != newDirection){
		setDirection(newDirection);
		changeMajorQuest(-1);
	}
};
void KoumeChan::changeMajorQuest(long newQuest)
{
	long oldQuest = getMajorQuest();
	if(oldQuest != newQuest){
		setMajorQuest(newQuest);
		setMinorQuest(-1);
	}
};
