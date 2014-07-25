//
//  QuestScene.cpp
//  Koumechan
//
//  Created by 上野　彰三 on 2014/07/07.
//
//
#include "MinorQuest.h"
#include "PuzzleUnitManager.h"
#include "JsonKeyString.h"
#include "QuestScene.h"
#include "MasterNPC.h"
#include "MinorQuest.h"
#include "PuzzleUILayer.h"
#include "QuestTMXMap.h"

using namespace cocos2d;
using namespace std;

QuestScene* QuestScene::create()
{
	QuestScene* pRet = new QuestScene();
	if(pRet && pRet->init()){
		pRet->autorelease();
	}
	else{
		CC_SAFE_DELETE(pRet);
		pRet = NULL;
	}
	return pRet;
}

bool QuestScene::init()
{
	setComPlayer(true);
	if(PuzzleScene::init()){
		setNeutralForce(KoumeChan::getInstance()->getForceMaster(0));
		setPlayer1Force(KoumeChan::getInstance()->getForceMaster(1));
		setPlayer2Force(KoumeChan::getInstance()->getForceMaster(2));
		
		setPlayer1(Friends::createMyData());
		setPlayer2(Friends::createNPC(getCurrentNPC()));

		SpriteFrameCache* cache = SpriteFrameCache::getInstance();
		///////////////////////////////////////////////;
		MinorQuest* minor = getCurrentMinorQuest();
		long cnt = minor->getUnitCount();
		for(long l = 0;l < cnt ;l++){
			QuestUnit* questUnit = (QuestUnit*)minor->getUnit(l);
			MasterUnit* unit = KoumeChan::getInstance()->getUnitMaster(questUnit->getKeyNo());
			if(unit){
				if(unit->getForceNo() == getPlayer1Force()->getMasterNo()){
					addOwnUnitFrameName(unit->getFrameName());
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
		///////////////////////////////////////////////
		
		
		setState(PUZZLE_INIT);
		setPhase(PHASE_NONE);
		setDlgState(CONNECT);
		
		//////////////////////////////
		Value url = KoumeChan::getInstance()->getProfileUrl();
		sendImageHttpRequest(KcScene::MY_GOOGLE_PLUS,url);
		Value tomoUrl = getCurrentNPC()->getImage();
		sendImageHttpRequest(KcScene::TOMOPEN, tomoUrl);
		return true;
	}
	return false;
}
// COMのユニット操作
void QuestScene::player2()
{
	PuzzleScene::player2();
	PuzzleUnitManager* mgr = PuzzleUnitManager::getInstance();
	if(mgr){
		if(comUseSkill()){
			skillAttackAnimation();
		}
		else{
			mgr->doComScan();
			int nEval = mgr->getComChainCandidate();
			if(nEval >  0){
				int nTarget1 = candidateIdx(candidateInt(nEval));
				bool vh = candidateVH(nEval);
				Point pos1 = idxToPos(nTarget1);
				Point pos2 = Point(vh ? pos1.x : pos1.x + 1,vh ? pos1.y + 1 : pos1.y);
				if(mgr->doSwitch(pos1, pos2)){
					mgr->executeChain();
					addTask(COM_CHAIN_ANIMATION);
					mgr->unitAction(CallFunc::create([this]{
						this->finishTask(COM_CHAIN_ANIMATION);
						this->phaseEnd();
					}));
				}
			}
		}
	}
}
long QuestScene::getPlayer2HitPoint()
{
	MasterNPC* npc = getCurrentNPC();
	if(npc){
		return npc->getHP();
	}
	return 0;
}
int QuestScene::getCurrentMaxPhaseCount(PUZZLE_PHASE phase)
{
	MinorQuest* q = getCurrentMinorQuest();
	if(phase == PHASE_PLAYER_1){
		if(q){
			return q->getAttackCount();
		}
	}
	if(phase == PHASE_PLAYER_2){
		if(q){
			return q->getAttackCount();
		}
	}
	return 1;
};


bool QuestScene::comUseSkill()
{
	PuzzleUnitManager* mgr = PuzzleUnitManager::getInstance();
	if(mgr){
		if(getPlayer2Power() >= LBLEVEL1){
			int tgt = mgr->comFindEliteUnit();
			if(tgt > 0){
				mgr->setCurrentFrameIdx(tgt);
				mgr->showLimitBreakTarget(tgt);
				return true;
			}
		}
		if(getPlayer2Power() >= LBLEVLE3){
			return true;
		}
	}
	return false;
};

// フェイズ切り替わりの演出など
void QuestScene::changePhaseDetail()
{
	if(getPhase() == PHASE_PLAYER_1){
		setPlayable(false);
		setPhase(PHASE_PLAYER_2);
		sayWords(Words::STARTTURN);
	}
	else if(getPhase() == PHASE_PLAYER_2){
		if(getComPlayer()){
			sayWords(Words::ENDTURN);
		}
		setPhase(PHASE_PLAYER_1);
	}
	else{
		setPhase(getBattleFirst());
	}
	
}
// NPCのの台詞
void QuestScene::sayWords(Words::WORDS word)
{
	PuzzleUILayer* ui = (PuzzleUILayer*)getUINode();
	if(ui){
		MasterNPC* npc = getCurrentNPC();
		NPCWords* words = (NPCWords*)npc->getWords(word);
		if(words){
			std::string str = V2C(words->getWord());
			log("say chat %s",str.c_str());
			Sprite* sp = ui->getFaceSprite();
			if(sp){
				sp->setTexture(getPlayer2Face());
			}
			ui->setChatMessage(str);
		}
		else{
			log("no words");
		}
	}
};

// 終了時の演出など
void QuestScene::finishGame()
{
	sayWords(getPlayer1HP() <= 0 ? Words::WIN : Words::LOSE);
	winLoseDlg();
}

void QuestScene::didPuzzleInit(Json *json)
{
	ConnectInfoDlg* pDlg = KoumeChan::getInstance()->getConnectInfoDialog(this);
	pDlg->ExitDlg();
	if(checkBasicResponse(json)){
		long long serverRandom = KoumeChan::getLLong(json, JS_RAMDOM_SEED, 0LL);
		
		log("randam seed %lld" ,serverRandom);
		srand((unsigned)serverRandom);
		// TODO: サーバとの初期化処理終了時の処理を呼ぶ
		PuzzleUnitManager* mgr = PuzzleUnitManager::getInstance();
		if(mgr){
			mgr->setSeed(serverRandom);
			addTask(TASK_UNIT_INIT_ANIME);
			setBattleFirst(serverRandom % 2 == 0 ? PHASE_PLAYER_1 : PHASE_PLAYER_2);
			setTurn(0);
			sayWords(Words::HELLO);
			mgr->dealUnit();
			mgr->unitAction(CallFunc::create([this]{
				this->finishTask(TASK_UNIT_INIT_ANIME);
				this->phaseEnd();
			}));
		}
		
	}
	log("*********************finish http");
}

void QuestScene::didPuzzleFinish(Json *json)
{
	ConnectInfoDlg* pDlg = KoumeChan::getInstance()->getConnectInfoDialog(this);
	pDlg->ExitDlg();
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

void QuestScene::doPuzzleInit()
{
	PuzzleUnitManager* mgr = PuzzleUnitManager::getInstance();
	if(mgr){
		mgr->initGame();
		setPhase(PHASE_NONE);
		setPhaseCount(0);
		
		gameInitAnimation();
		log("**********start http");
		std::string sendJson = StringUtils::format("{%s}",KoumeChan::getInstance()->getSessionJsonString().c_str());
		KcScene::sendHttpRequest(KcScene::PUZZLE_INIT, sendJson.c_str());
		KoumeChan::getInstance()->showConnectInfoDialog(this);
	}
}

void QuestScene::doPuzzleFinish()
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

MasterNPC* QuestScene::getCurrentNPC()
{
	MinorQuest* q = getCurrentMinorQuest();
	if(q){
		return KoumeChan::getInstance()->getNPCMaster(q->getNPCNo());
	}
	return NULL;
};
MinorQuest* QuestScene::getCurrentMinorQuest()
{
	return  KoumeChan::getInstance()->getMinorQuestMaster();
}

MasterMap* QuestScene::getCurrentMap()
{
	MinorQuest* q = getCurrentMinorQuest();
	if(q){
		return KoumeChan::getInstance()->getMapMaster(q->getMapNo());
	}
	return NULL;
}

PuzzleTMXTiledMap* QuestScene::createTiledMap()
{
	return QuestTMPMap::create();
}

