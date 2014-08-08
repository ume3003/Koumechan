//
//  CompetitionScene.cpp
//  Koumechan
//
//  Created by 上野　彰三 on 2014/07/07.
//
//

#include "CompetitionScene.h"
#include "PuzzleUnitManager.h"
#include "JsonKeyString.h"
#include "CompetitionTMXMap.h"

using namespace cocos2d;
using namespace std;

CompetitionScene::~CompetitionScene()
{
	m_vecRateArray.clear();
}

bool CompetitionScene::init()
{
	setComPlayer(false);
	if( PuzzleScene::init()){
		SpriteFrameCache* cache = SpriteFrameCache::getInstance();
		///////////////////////////////////////////////;
		FriendMatch* fm = KoumeChan::getInstance()->getFriendMatch();
		if(fm){
			Scenario* sce = KoumeChan::getInstance()->getScenarioMaster(fm->getScenario());
			if(sce){
				setState(PUZZLE_INIT);
				setPhase(PHASE_NONE);
				setDlgState(CONNECT);
				setNeutralForce(KoumeChan::getInstance()->getForceMaster(0));
				
				setPlayer1Force(KoumeChan::getInstance()->getForceMaster(fm->getOwner() ? 3 : 4));
				setPlayer2Force(KoumeChan::getInstance()->getForceMaster(fm->getOwner() ? 4 : 3));
				setPlayer1(fm->getOwner() ? fm->getMyPlayer() : fm->getUrPlayer());
				setPlayer2(fm->getOwner() ? fm->getUrPlayer() : fm->getMyPlayer());
				
				long cnt = sce->getUnitCount();
				for(long l = 0;l < cnt ;l++){
					ScenarioUnit* scenarioUnit = (ScenarioUnit*)sce->getUnit(l);
					MasterUnit* unit = KoumeChan::getInstance()->getUnitMaster(scenarioUnit->getKeyNo());
					if(unit){
						if(unit->getForceNo() == getPlayer1Force()->getMasterNo()){
							addOwnUnitFrameName(unit->getTextureName());
							if(scenarioUnit->getVal() == 0){
								addShikigami(unit->getMasterNo(), PuzzleScene::PHASE_PLAYER_1);
							}
						}
						else if(scenarioUnit->getVal() == 0){
							addShikigami(unit->getMasterNo(), PuzzleScene::PHASE_PLAYER_2);
						}
						for(int i = 0;i < unit->getSkillCount();i++){
							BaseConditionMaster* unitSkill = unit->getSkill(i);
							Skill* skill = KoumeChan::getInstance()->getSkillMaster(unitSkill->getKeyNo());
							if(skill){
								cache->addSpriteFramesWithFile(skill->getPLIST(), skill->getPNG());
							}
						}
						
					}
				}
				
				//////////////////////////////
				Value url = KoumeChan::getInstance()->getProfileUrl();
				sendImageHttpRequest(KcScene::MY_GOOGLE_PLUS,url);
				Friends* f = fm->getFriends();
				if(f){
					Value tomoUrl = f->getURL();
					sendImageHttpRequest(KcScene::TOMOPEN, tomoUrl);
				}
				
				KoumeChan::getInstance()->registerIOEvent(NR_RECEIVE_ROOM	,CC_CALLBACK_2(CompetitionScene::sioGameData,this));
				KoumeChan::getInstance()->registerIOEvent(NR_LEAVE_ROOM		,CC_CALLBACK_2(CompetitionScene::sioLeftRoom,this));
				KoumeChan::getInstance()->registerIOEvent(NR_SEED			,CC_CALLBACK_2(CompetitionScene::sioGotSeed ,this));
				KoumeChan::getInstance()->registerIOEvent(NR_READY			,CC_CALLBACK_2(CompetitionScene::sioGotReady ,this));
				KoumeChan::getInstance()->registerIOEvent(NR_LINK_DOWN		,CC_CALLBACK_2(CompetitionScene::sioLinkedDown ,this));
				
				return true;
				
			}
		}
		///////////////////////////////////////////////
		
		
	}
	return false;
}
CompetitionScene* CompetitionScene::create()
{
	CompetitionScene* pRet = new CompetitionScene();
	if(pRet && pRet->init()){
		pRet->autorelease();
	}
	else{
		CC_SAFE_DELETE(pRet);
		pRet = NULL;
	}
	return pRet;
	
}


void CompetitionScene::player2()
{
	PuzzleScene::player2();
	// 対戦相手のコマンドを末
}

void CompetitionScene::changePhaseDetail()
{
	if(getPhase() == PHASE_PLAYER_1){
		setPlayable(false);
		setPhase(PHASE_PLAYER_2);
	}
	else if(getPhase() == PHASE_PLAYER_2){
		setPhase(PHASE_PLAYER_1);
	}
	else{
		setPhase(getBattleFirst());
	}
	
}


void CompetitionScene::finishGame()
{
	PuzzleUnitManager* mgr = PuzzleUnitManager::getInstance();
	FriendMatch* fm = KoumeChan::getInstance()->getFriendMatch();
	if(fm && mgr){
		Scenario* sce = KoumeChan::getInstance()->getScenarioMaster(fm->getScenario());
		if(sce){
			long cnt = sce->getUnitCount();
			log("++++++++++++++++++++++++++++++++++++++");
			for(long l = 0;l < cnt ;l++){
				ScenarioUnit* scenarioUnit = (ScenarioUnit*)sce->getUnit(l);
				MasterUnit* unit = KoumeChan::getInstance()->getUnitMaster(scenarioUnit->getKeyNo());
				long count = mgr->getUnitKOCount(scenarioUnit->getKeyNo());
				log("Unit %ld %s KO %ld",unit->getMasterNo(),V2C(unit->getName()),count);
			}
		}
		log("++++++++++++++++++++++++++++++++++++++");
	}
	winLoseDlg();
}

void CompetitionScene::doPuzzleInit()
{
	PuzzleUnitManager* mgr = PuzzleUnitManager::getInstance();
	if(mgr){
		mgr->initGame();
		setPhase(PHASE_NONE);
		setPhaseCount(0);
		setRatePos(0);
		addTask(TASK_UNIT_INIT_ANIME);			// これないと先にはじまることがある
		gameInitAnimation();
		
		KoumeChan::getInstance()->showConnectInfoDialog(this);
		sendMessageToReady();
	}
}

void CompetitionScene::didPuzzleInit(Json *json)
{
	ConnectInfoDlg* pDlg = KoumeChan::getInstance()->getConnectInfoDialog(this);
	if(pDlg){
		pDlg->ExitDlg();
	}
	assert(pDlg);
	FriendMatch* fMatch = KoumeChan::getInstance()->getFriendMatch();
	if(fMatch){
		long long serverRandom = fMatch->getSeed();
		PuzzleUnitManager* mgr = PuzzleUnitManager::getInstance();
		if(mgr){
			mgr->setSeed(serverRandom);
			PUZZLE_PHASE myPhase = fMatch->getOwner() ? PHASE_PLAYER_1 : PHASE_PLAYER_2;
			PUZZLE_PHASE urPhase = fMatch->getOwner() ? PHASE_PLAYER_2 : PHASE_PLAYER_1;
			setBattleFirst(serverRandom % 2 == 0 ? myPhase : urPhase);
			setTurn(0);
			mgr->dealUnit();
			mgr->unitAction(CallFunc::create([this]{
				this->finishTask(TASK_UNIT_INIT_ANIME);
				this->phaseEnd();
			}));
		}
	}
	log("*********************finish node");
}

void CompetitionScene::didPuzzleFinish(Json *json)
{
	ConnectInfoDlg* pDlg = KoumeChan::getInstance()->getConnectInfoDialog(this);
	if(pDlg){
		pDlg->ExitDlg();
	}
	if(checkBasicResponse(json)){
		// Receieve EXP
		// Receieve LV
		GameCharacter* chara = KoumeChan::getInstance()->getGameCharacter();
		long exp = KoumeChan::getLong(json,JS_EXPERIENCE,chara->getExp());
		int lv = KoumeChan::getInt(json,JS_LEVEL, chara->getLevel());
		long hp = KoumeChan::getLong(json, JS_HP, chara->getHP());
		log("recieve data EXP %ld Level %d HP %ld",exp,lv,hp);
		chara->setExp(exp);
		chara->setLevel(lv);
		chara->setHP(hp);
	}
	winLoseDlg();
	log("*********************finish http");
	
}

void CompetitionScene::sendMessageToReady()
{
	log("**********start node");
	Value myUUID = KoumeChan::getInstance()->getUUID();
	KoumeChan::getInstance()->sendSocketIOMessage(NS_READY, StringUtils::format("[{\"uuid\":\"%s\"}]",V2C(myUUID)));
	
};
void CompetitionScene::askSeed()
{
	log("*********** ask seed ****************");
	Value myUUID = KoumeChan::getInstance()->getUUID();
	KoumeChan::getInstance()->sendSocketIOMessage(NS_SEED, StringUtils::format("[{\"uuid\":\"%s\"}]",V2C(myUUID)));
}

long CompetitionScene::getPlayer2HitPoint()
{
	long hp = 90;
	FriendMatch* fm = KoumeChan::getInstance()->getFriendMatch();
	if(fm){
		Friends* f = fm->getFriends();
		if(f){
			hp = MAX(hp, f->getHP());
		}
	}
	 return hp;
}
int CompetitionScene::getCurrentMaxPhaseCount(PUZZLE_PHASE phase)
{
	return 2;
}

void CompetitionScene::doPuzzleFinish()
{
	winLoseDlg();
	return;
	log("**********start http");
	
	// win / lose
	// win ENEMY HP
	// Win TURN
	int nWin = getPlayer2HP() <= 0 ? 1 : 0;
	std::string sendJson = StringUtils::format("{%s,%s,%s,%s}",
											   KoumeChan::getInstance()->getSessionJsonString().c_str(),
											   jsInt(JS_WIN_LOSE, nWin).c_str(),
											   jsLong(JS_WIN_CONDITION,getPlayer2HP()).c_str(),
											   jsInt(JS_TURN,getTurn()).c_str() );
	KcScene::sendHttpRequest(KcScene::PUZZLE_FINISH, sendJson.c_str());
	KoumeChan::getInstance()->showConnectInfoDialog(this);
}

MasterMap* CompetitionScene::getCurrentMap()
{
	FriendMatch* fm = KoumeChan::getInstance()->getFriendMatch();
	if(fm){
		Scenario* sce = KoumeChan::getInstance()->getScenarioMaster(fm->getScenario());
		if(sce){
			return KoumeChan::getInstance()->getMapMaster(sce->getMapNo());
		}
	}
	return NULL;
}

PuzzleTMXTiledMap* CompetitionScene::createTiledMap()
{
	return CompetitionTMXMap::create();
}

void CompetitionScene::userMove(cocos2d::Point pos1, cocos2d::Point pos2)
{
	log("%2.0f/%2.0f → %2.0f/%2.0f",pos1.x,pos1.y,pos2.x,pos2.y);
	Value myUUID = KoumeChan::getInstance()->getUUID();
	int idx1 = xyToIdx(pos1);
	int idx2 = xyToIdx(pos2);
	KoumeChan::getInstance()->sendSocketIOMessage(NS_SAY_ROOM,
	StringUtils::format("[{\"command\":%d,\"uuid\":\"%s\",\"index1\":%d,\"index2\":%d}]",MOVE,V2C(myUUID),idx1,idx2));
	
}

void CompetitionScene::userUnitLBCommand(cocos2d::Point pos)
{
	Value myUUID = KoumeChan::getInstance()->getUUID();
	int idx1 = xyToIdx(pos);
	KoumeChan::getInstance()->sendSocketIOMessage(NS_SAY_ROOM,
												  StringUtils::format("[{\"command\":%d,\"uuid\":\"%s\",\"index1\":%d}]",UNIT_LB,V2C(myUUID),idx1));
	
};
void CompetitionScene::userAllLBCommand()
{
	Value myUUID = KoumeChan::getInstance()->getUUID();
	KoumeChan::getInstance()->sendSocketIOMessage(NS_SAY_ROOM,
												  StringUtils::format("[{\"command\":%d,\"uuid\":\"%s\"}]",ALL_LB,V2C(myUUID)));
	
};
void CompetitionScene::userSelectUnit(cocos2d::Point pos)
{
	Value myUUID = KoumeChan::getInstance()->getUUID();
	int idx1 = xyToIdx(pos);
	KoumeChan::getInstance()->sendSocketIOMessage(NS_SAY_ROOM,
												  StringUtils::format("[{\"command\":%d,\"uuid\":\"%s\",\"index1\":%d}]",SELECT_UNIT,V2C(myUUID),idx1));
	
};

void CompetitionScene::sioGotReady(cocos2d::network::SIOClient *client, const std::string& data)
{
	FriendMatch* fm = KoumeChan::getInstance()->getFriendMatch();
	if(fm){
		if(fm->getOwner()){
			askSeed();
		}
	}
}
void CompetitionScene::sioLinkedDown(cocos2d::network::SIOClient *client, const std::string& data)
{
	KoumeChan::getInstance()->destroySocketIO();
	PuzzleScene::closePuzzle();
}


void CompetitionScene::sioLeftRoom(cocos2d::network::SIOClient *client, const std::string& data)
{
	KoumeChan::getInstance()->destroySocketIO();
	PuzzleScene::closePuzzle();
}
void CompetitionScene::sioGotSeed(cocos2d::network::SIOClient *client, const std::string &data)
{
	Json* dJson = NULL;
	Json* j = Json_create(data.c_str());
	if(j){
		Json* j1 = Json_getItem(j,"args");
		if(j1){
			Json* json = j1->child;
			if(json){
				dJson = Json_getItem(json, "msg");
			}
		}
	}
	if(dJson){
		Json* row = NULL;
		int i ;
		for (row = dJson->child,i = 0; row ; row = row->next, ++i) {
			if(row){
				int seed = Json_getInt(row,"d",0);
				m_vecRateArray.push_back(seed);
			}
		}
		didPuzzleInit(dJson);
	}
	Json_dispose(j);
}
void CompetitionScene::sioGameData(cocos2d::network::SIOClient *client, const std::string& data)
{
	PuzzleUnitManager* mgr = PuzzleUnitManager::getInstance();
	Value myUUID = KoumeChan::getInstance()->getUUID();
	FriendMatch* fMatch = KoumeChan::getInstance()->getFriendMatch();
	Value youUUID = fMatch->getUrUUID();

	Json* dJson = NULL;
	Json* j = Json_create(data.c_str());
	if(j){
		Json* j1 = Json_getItem(j,"args");
		if(j1){
			Json* json = j1->child;
			if(json){
				dJson = Json_getItem(json, "msg");
			}
		}
	}
	if(dJson){
		COMMAND cmd = (COMMAND)KoumeChan::getInt(dJson, "command", NONE);
		if(mgr && cmd >= 0 ){
			Value uuid = Value(Json_getString(dJson, "uuid", ""));
			int idx1 = KoumeChan::getInt(dJson, "index1", -1);
			int idx2 = KoumeChan::getInt(dJson, "index2", -1);
			log("++++++++++++++++message from %s command %d mine? %s",uuid.asString().c_str(),cmd,uuid.asString() == myUUID.asString() ? "me" : "you");
			if(uuid.asString() != myUUID.asString()){
				switch(cmd){
					case START:
						startCommand(dJson);
						break;
					case MOVE:
						moveCommand(idx1, idx2);
						break;
					case UNIT_LB:
						unitLBCommand(idx1);
						break;
					case ALL_LB:
						allLBCommand();
						break;
					case SELECT_UNIT:
						selectUnit(idx1);
					default:
						break;
				}
						
			}
		}
	}
	Json_dispose(j);


}
void CompetitionScene::startCommand(Json* json)
{
	log("+++++++++++++++++++++++++++++++++++++++++++++++++");
	log("+++++ startCommand ready ++++++++++++++++++++++++");
	log("+++++++++++++++++++++++++++++++++++++++++++++++++");
	didPuzzleInit(json);
};
void CompetitionScene::moveCommand(int idx1,int idx2)
{
	PuzzleUnitManager* mgr = PuzzleUnitManager::getInstance();

	if(idx1 >= 0 && idx2 >= 0){
		Point pos1 = idxToPos(idx1);
		Point pos2 = idxToPos(idx2);
		if(mgr->doSwitch(pos1, pos2)){
			mgr->executeChain();
			addTask(COM_CHAIN_ANIMATION);
			mgr->unitAction(CallFunc::create([this]{
				this->finishTask(COM_CHAIN_ANIMATION);
				this->phaseEnd();
			}));
		}
		
	}
	
};
void CompetitionScene::unitLBCommand(int tgt)
{
	PuzzleUnitManager* mgr = PuzzleUnitManager::getInstance();
	if(mgr){
		if(tgt > 0){
			mgr->changeCurrentFrame(tgt);
			mgr->showLimitBreakTarget(tgt);
			skillAttackAnimation();
		}
	}
	
};
void CompetitionScene::allLBCommand()
{
	skillAttackAnimation();
};
void CompetitionScene::selectUnit(int idx)
{
	PuzzleUnitManager* mgr = PuzzleUnitManager::getInstance();
	mgr->changeCurrentFrame(idx);
}

void CompetitionScene::closePuzzle()
{
	KoumeChan::getInstance()->sendSocketIOMessage(NS_LEAVE_ROOM, StringUtils::format("[{\"command\":0}]"));
}

long CompetitionScene::getSeed()
{
	CompetitionTMXMap* map = (CompetitionTMXMap*)getTMXTiledMap();
	if(map){
		if(getRatePos() >= m_vecRateArray.size()){
			setRatePos(0);
		}
		int seed = m_vecRateArray.at(getRatePos());
		setRatePos(getRatePos() + 1);
		long subs = seed % ( map->getAppearanceRate() != 0 ? map->getAppearanceRate() : 1 );

		return map->findUnitNoFromRate(subs);
		
	}
	return -1;
};
