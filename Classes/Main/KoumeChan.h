//
//  KoumeChan.h
//  koumeChan
//
//  Created by 上野　彰三 on 2014/03/11.
//
//

#ifndef __koumeChan__KoumeChan__
#define __koumeChan__KoumeChan__

#include "KCDef.h"
#include "cocos2d.h"
#include "cocosbuilder/CocosBuilder.h"
#include "network/HttpClient.h"
#include "network/SocketIO.h"
#include "ConnectInfoDlg.h"
#include "spine/json.h"
#include "BaseMasterManager.h"
#include "GameCharacter.h"
#include "FriendList.h"
#include "FriendMatchList.h"

#include "DirectionQuest.h"
#include "MajorQuest.h"
#include "MinorQuest.h"
#include "MasterMap.h"
#include "MasterUnit.h"
#include "Item.h"
#include "Scenario.h"
#include "CompetitionRule.h"
#include "ConditionKind.h"
#include "CharacterColumn.h"
#include "Rank.h"
#include "Skill.h"
#include "Force.h"
#include "NPCWords.h"
#include "MasterNPC.h"
#include "BaseDamage.h"

#include "QuestUnit.h"
#include "QuestAppearance.h"
#include "QuestClear.h"
#include "QuestReward.h"

#include "ScenarioUnit.h"
#include "ScenarioRule.h"

#include "MasterUnitSkill.h"


#define PREF_ISSIGNIN "ISSIGNIN"
#define PREF_VERSION "MASTERVERSION%d"
#define PREF_RESCUESTRING "RESCUESTRING"
#define PREF_UUID "LOCALUUID"


class KoumeChan : public cocos2d::network::SocketIO::SIODelegate
{
public:

	enum DLGTAG {
		CONNECTINFODLG = 1001,
		YNDLG
	};
	enum CHAINTYPE {
		NO_CHAIN = 0,
		CHAIN_THREE,
		CHAIN_FOUR,
		CHAIN_FIVE,
		CHAIN_T_1R,
		CHAIN_T_2R,
		CHAIN_T_2L,
		CHAIN_T_3R,
		CHAIN_T_3L,
		CHAIN_T_3C,
		CHAIN_Y_2T,
		CHAIN_Y_3T
	};
	
private:
	KoumeChan();
	~KoumeChan();
	static KoumeChan* m_singleton;
	// unsavedValue
	CC_SYNTHESIZE(float, m_diffHeight, DiffHeight);
	CC_SYNTHESIZE(float, m_smallFont, SmallFont);
	CC_SYNTHESIZE(float, m_midFont, MidFont);
	CC_SYNTHESIZE(float, m_largeFont, LargeFont);
	CC_SYNTHESIZE(bool,m_OpenSocket,OpenSocket);
	
	CC_SYNTHESIZE(long , m_direction,Direction);
	CC_SYNTHESIZE(long , m_majorQuest,MajorQuest);
	CC_SYNTHESIZE(long , m_minorQuest,MinorQuest);
	
	CC_SYNTHESIZE(cocos2d::Value, m_mailAddress	,MailAddress);
	CC_SYNTHESIZE(cocos2d::Value, m_displayName	,DisplayName);
	CC_SYNTHESIZE(cocos2d::Value, m_profileUrl	,ProfileUrl);
	CC_SYNTHESIZE(cocos2d::Value, m_gppuid		,GPPUuid);
	CC_SYNTHESIZE(cocos2d::Value, m_sessionId,SessionId);
	
		// GameData
	CC_SYNTHESIZE_RETAIN(GameCharacter*	, m_gameCharacter	, GameCharacter);
	CC_SYNTHESIZE_RETAIN(FriendList*	, m_friendList		, FriendList);
	CC_SYNTHESIZE_RETAIN(FriendMatchList*,m_friendMatchList , FriendMatchList);
	// savedValue
	CC_SYNTHESIZE(cocos2d::Value, m_rescueString, RescueString); // TODO: make and show
	CC_SYNTHESIZE(cocos2d::Value, m_UUID, UUID);
	CC_SYNTHESIZE(long,m_loginId,LoginId);
	CC_SYNTHESIZE(bool, m_signIn, SignIn);

	CC_SYNTHESIZE_RETAIN(FriendMatch*,m_friendMatch,FriendMatch);
	
	CC_SYNTHESIZE_RETAIN(cocos2d::CallFunc*, m_onConnectCallback, OnConnectCallback);

	CC_SYNTHESIZE_RETAIN(cocos2d::network::SIOClient* ,m_SocketIO,SocketIO);


	std::map<int,long long> m_versions;
	std::map<int,long long> m_serverVersions;
	cocos2d::Map<int,BaseMasterManager*> m_managers;
	
	
	void initVersions();
	void setMasterManager(BaseMaster::MASTERNO masterNo,BaseMasterManager* manager) { m_managers.insert(masterNo, manager);};

public:

	static KoumeChan* getInstance();
	
	long long getVersion(int masterNo);
	long long getServerVersion(int masterNo);
	void setVersion(int masterNo,long long version);
	void setServerVersion(int masterNo,long long version);
	bool checkNewVersion(int masterNo);
	bool loadServerVersion(Json* json);
	
	BaseMasterManager* getMasterManager(BaseMaster::MASTERNO masterNo) { return m_managers.at(masterNo);};
	
	void loadPref();
	void savePref();
	
	void loadLocalMasterData();
	void clearLocalMasterData();
	
	void showMainScene();
	void showStartScene();
	void showPuzzleScene();
	void showFriendMatchScene();

	void takeScreenShot(std::string strFileName);
	
	void showYNDialog(cocos2d::Node* pParent);
	void showConnectInfoDialog(cocos2d::Node* pParent);
	ConnectInfoDlg* getConnectInfoDialog(cocos2d::Node* pParent);
	cocos2d::Node* getModal(cocos2d::Node* pParent,int tag = MODAL_TAG_NO);
	
	void loadModal(cocos2d::Node* pParent,const char* className,cocosbuilder::NodeLoader* loader,const char* layoutName,int tag = MODAL_TAG_NO,bool bMove = true);
	//////////////////////////////////////
	//	Help method to get master data
	//////////////////////////////////////
	DirectionQuest*		getDirectionMaster(long masterNo = -1);
	MajorQuest*			getMajorQuestMaster(long masterNo = -1);
	MinorQuest*			getMinorQuestMaster(long masterNo = -1);
	MasterMap*			getMapMaster(long masterNo = -1);
	MasterUnit*			getUnitMaster(long masterNo = -1);
	long				getUnitForce(long masterNo = -1);
	Item*				getItemMaster(long masterNo = -1);
	Scenario*			getScenarioMaster(long masterNo = -1);
	CompetitionRule*	getCompetitionRuleMaster(long masterNo = -1);

	ConditionKind*		getConditionKindMaster(long masterNo = -1);
	CharacterColumn*	getCharacterColumnMaster(long masterNo = -1);
	Rank*				getRankMaster(long masterNo = -1);
	Skill*				getSkillMaster(long masterNo = -1);
	Force*				getForceMaster(long masterNo = -1);
	MasterNPC*			getNPCMaster(long masterNo = -1);
	BaseDamage*			getBaseDamageMaster(long masterNo = -1);
	
	//////////////////////////////////////
	//	Public memory method
	//////////////////////////////////////
	void changeDirection(long newDirection);
	void changeMajorQuest(long newQuest);
	//////////////////////////////////////
	//	AccessToServer
	//////////////////////////////////////
	void	send(const char* pTag,const char* pData,const char* pURL,cocos2d::Ref* target,const cocos2d::network::ccHttpRequestCallback& callback);
	Json*	responseToJson(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response);
	const char* getTag(cocos2d::network::HttpResponse *response);
	
	
	///////////////////////////////////////
	//	Socket IO
	///////////////////////////////////////
	void initSocketIO();
	void destroySocketIO();
	void globalIOEvent(cocos2d::network::SIOClient *client, const std::string& data);

	virtual void onConnect(cocos2d::network::SIOClient* client);
    virtual void onMessage(cocos2d::network::SIOClient* client, const std::string& data);
    virtual void onClose(cocos2d::network::SIOClient* client);
    virtual void onError(cocos2d::network::SIOClient* client, const std::string& data);
	
	void sendSocketIOMessage(std::string eventName,std::string message);
	void registerIOEvent(std::string eventName,cocos2d::network::SIOEvent event);
	void reconnectSocketIO();
	
	
	//////////////////////////////////////
	//	JSON
	/////////////////////////////////////
	std::string getLoginJsonString();
	std::string getSessionJsonString();
	std::string getCurrentTimeString();
	
	static int getInt(Json* json,const char* tag,int defaultVal);
	static long getLong(Json* json,const char* tag,long defaultVal);
	static long long getLLong(Json* json,const char* tag,long long defaultVal);
	static float getFloat(Json* json,const char* tag,float defaultVal);
	
	///////////////////////////////////
	static CHAINTYPE chainCountToType(int count);
	
};

#endif /* defined(__koumeChan__KoumeChan__) */
