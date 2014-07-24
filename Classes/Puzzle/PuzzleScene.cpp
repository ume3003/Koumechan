//
//  PuzzleScene.cpp
//  koumeChan
//
//  Created by 上野　彰三 on 2014/03/25.
//
//

#include "PuzzleScene.h"
#include "Modal.h"
#include "KcDef.h"
#include "JsonKeyString.h"
#include "PuzzleUnitManager.h"
#include "PuzzleUILayer.h"
#include "PuzzleUILayerLoader.h"
#include "PuzzleMapLayer.h"
#include "PuzzleMapLayerLoader.h"
#include "PuzzleTMXTiledMap.h"

using namespace cocos2d;
using namespace cocosbuilder;

PuzzleScene::PuzzleScene() : m_UI(NULL),m_Map(NULL),m_player1Force(NULL),m_player2Force(NULL),m_NeutralForce(NULL),m_Player1Face(NULL),m_Player2Face(NULL)
{
	// TODO:for VS setfrom outside
	setBattleFirst(PHASE_PLAYER_2);
}

PuzzleScene::~PuzzleScene()
{
	CC_SAFE_RELEASE(m_UI);
	CC_SAFE_RELEASE(m_Map);
	CC_SAFE_RELEASE(m_NeutralForce);
	CC_SAFE_RELEASE(m_player1Force);
	CC_SAFE_RELEASE(m_player2Force);
	CC_SAFE_RELEASE(m_Player1Face);
	CC_SAFE_RELEASE(m_Player2Face);
}

const char* PuzzleScene::getConnectInfoDlgTitleMessage()
{
	switch(getDlgState()){
		case CONNECT:
			return "通信中・・・";
			break;
		case FINISH_GAME:
			return "パズル終了";
			break;
		default:
			break;
	}
	return "通信中・・・";
};
const char* PuzzleScene::getConnectInfoDlgBodyMessage()
{
	switch(getDlgState()){
		case CONNECT:
			return "通信中・・・";
			break;
		case FINISH_GAME:
			if(getPlayer1HP() <= 0){
				return "敗北！";
				
			}
			else{
				return "勝利！";
			}
			break;
		default:
			break;
	}
	return "通信中・・・";
};
const char* PuzzleScene::getConnectInfoCancelButtonText()
{
	switch(getDlgState()){
		case CONNECT:
			break;
		case FINISH_GAME:
			return "閉じる";
			break;
		default:
			break;
	}
	return "CANCEL";
};

void PuzzleScene::onConnectInfoCancel()
{
	// TODO:ダウンロードを中止しました　アプリを終了すべし
	switch(getDlgState()){
		case CONNECT:
			break;
		case FINISH_GAME:
			endPuzzle();
			break;
		default:
			break;
	}
};

bool PuzzleScene::init()
{
	if(Scene::init()){
		NodeLoaderLibrary* NodeLoaderLibrary = NodeLoaderLibrary::newDefaultNodeLoaderLibrary();
		NodeLoaderLibrary->registerNodeLoader(PUZZLE_UILAYER_CLASS, PuzzleUILayerLoader::loader());
		NodeLoaderLibrary->registerNodeLoader(PUZZLE_MAPLAYER_CLASS, PuzzleMapLayerLoader::loader());
		CCBReader* ccbReader = new CCBReader(NodeLoaderLibrary);
		ccbReader->autorelease();
		CCBReader* ccbReaderMap = new CCBReader(NodeLoaderLibrary);
		ccbReaderMap->autorelease();
		Node* nodeUI  = ccbReader->readNodeGraphFromFile(PUZZLE_UILAYER_FILE);
		Node* nodeMap = ccbReaderMap->readNodeGraphFromFile(PUZZLE_MAPLAYER_FILE);
		if(nodeUI != NULL && nodeMap != NULL){
			
			addChild(nodeUI, LZ_UI,LTAG_UI);
			addChild(nodeMap, LZ_MAP,LTAG_MAP);
			((PuzzleMapLayer*)nodeMap)->loadMap();
			setMapNode(nodeMap);
			setUINode(nodeUI);
			PuzzleUnitManager::getInstance()->initPuzzle(this, (PuzzleTMXTiledMap*)getTMXTiledMap());
			SpriteFrameCache* cache = SpriteFrameCache::getInstance();
			cache->addSpriteFramesWithFile("frame.plist", "frame.png");
			
			return true;
		}
	}
	return false;
}
///////////////////////////////////////////////////////////////////////////
void PuzzleScene::puzzleMainLoop()
{
	PuzzleTMXTiledMap* map = (PuzzleTMXTiledMap*)getTMXTiledMap();
	if(map){
		map->clearShadowCell();
		Node* frame = map->getFrameNode();
		if(frame){
			frame->removeFromParentAndCleanup(true);
		}
	}
	switch(getState()){
		case PUZZLE_INIT:
			updateCurrentPhaseCount();
			doPuzzleInit();
			break;
		case PUZZLE_INGAME:
			changePhase();
			break;
		case PUZZLE_END:
			endPuzzle();
			break;
	}
}

///////////////////////////////////////////////////////////////////////////
void PuzzleScene::phaseEnd()
{
	if(checkTaskFinished()){
		//log("--------- phase  end --------------------");
		clearTask();
		setState(PUZZLE_INGAME);
		puzzleMainLoop();
	}
}
void PuzzleScene::doShuffle()
{
	PuzzleUnitManager* mgr = PuzzleUnitManager::getInstance();
	if(mgr->shuffleUnits()){
		shuffleMessageAnimation();
		addTask(SHUFFLE_ANIMATION);
		mgr->unitAction(CallFunc::create([this]{
			this->finishTask(SHUFFLE_ANIMATION);
			this->phaseStart();
		}));
	}
	else{
		// TODO:シャッフルしてももうダメな場合
	}
	
}
void PuzzleScene::phaseStart()
{
	PuzzleUnitManager* mgr = PuzzleUnitManager::getInstance();
	if(checkTaskFinished()){
		clearTask();
		if(mgr->hasChain()){		// 本来はない。シャッフルの後だけ発生
			mgr->initPhase();
			mgr->executeChain();
			addTask(SHUFFLE_CHAIN_ANIMATION);
			mgr->unitAction(CallFunc::create([this]
											 {
												 PuzzleUnitManager::getInstance()->initPhase();
												 this->finishTask(SHUFFLE_CHAIN_ANIMATION);
												 this->phaseStart();
											 }));
		}
		else{
			if(!mgr->canChain()){
				doShuffle();
			}
			else{
				log("phase start %d",getPhase());
				if(getPhase() == PHASE_PLAYER_1){
					setPlayable(true);
				}
				else if(getPhase() == PHASE_PLAYER_2){
					player2();
				}
				else{
					log("フェイズがおかしい");
				}
			}
			
		}
	}
}



void PuzzleScene::cancelUserMove()
{
	setPlayable(true);
	PuzzleUnitManager* mgr = PuzzleUnitManager::getInstance();
	if(mgr){
		mgr->initPhase();
	}
	
};
void PuzzleScene::finishUserMove()
{
	finishTask(PuzzleScene::USER_CHAIN_ANIMATION);
	phaseEnd();
	
};
void PuzzleScene::updateCurrentPhaseCount()
{
	PuzzleUILayer* ui = (PuzzleUILayer*)getUINode();
	if(ui){
		if(getPhase() == PHASE_PLAYER_1){
			ui->showPayer1PhaseCount(getCurrentMaxPhaseCount(getPhase()),getPhaseCount());
		}
		if(getPhase() == PHASE_PLAYER_2){
			ui->showPayer2PhaseCount(getCurrentMaxPhaseCount(getPhase()),getPhaseCount());
			
		}
	}
}


void PuzzleScene::changePhase()
{
	PuzzleUnitManager* mgr = PuzzleUnitManager::getInstance();
	setBreak(false);
	if(mgr){
		// TODO:Game over check
		// if continue game
		log("=============== turn %d player %d=================",getTurn(),getPhase());
		if(getPlayer1HP() <= 0 || getPlayer2HP() <= 0){
			finishGame();
		}
		else{
			setPhaseCount(MAX(0,getPhaseCount() - 1));
			updateCurrentPhaseCount();
			log("============phase count %d",getPhaseCount());
			if(getPhaseCount() == 0){
				////////////////////////////
				changePhaseDetail();
				////////////////////////////
				setPhaseCount(getCurrentMaxPhaseCount(getPhase()));
				updateCurrentPhaseCount();
				if(getPhase() != getBattleFirst()){
					setTurn(getTurn() + 1);
					mgr->initTurn();
				}
			}
			mgr->initPhase();
			phaseChangeAnimation();
		}
		
	}
};

void PuzzleScene::player2()
{
	log("========================================");
	log("========== Player 2 ====================");
	log("========================================");
};

void PuzzleScene::winLoseDlg()
{
	setDlgState(FINISH_GAME);
	KoumeChan::getInstance()->showConnectInfoDialog(this);
}

void PuzzleScene::endPuzzle()
{
	setState(PUZZLE_END);
	KoumeChan::getInstance()->showYNDialog(this);
}
void PuzzleScene::closePuzzle()
{
	KoumeChan::getInstance()->showMainScene();
}
//////////////////////////////////////////////////////////////////////////////////////////
//
//		せりふ処理
//
//////////////////////////////////////////////////////////////////////////////////////////
void PuzzleScene::sayPhase()
{
	PuzzleUILayer* ui = (PuzzleUILayer*)getUINode();
	if(ui){
		Sprite* sp = ui->getFaceSprite();
		if(sp){
			if(getPhase() == PHASE_PLAYER_1){
				sp->setTexture(getPlayer1Face());
			}
			else{
				sp->setTexture(getPlayer2Face());
			}
		}
	}
}
void PuzzleScene::saySkill(long skillNo)
{
	PuzzleUILayer* ui = (PuzzleUILayer*)getUINode();
	if(ui){
		Skill* skill = KoumeChan::getInstance()->getSkillMaster(skillNo);
		if(skill){
			std::string str = V2C(skill->getName());
			ui->setChatMessage(str);
		}
		else{
			log("no skill name");
		}
	}
	
};

void PuzzleScene::sayComboCount(int count)
{
	PuzzleUILayer* ui = (PuzzleUILayer*)getUINode();
	if(ui){
		std::string str = StringUtils::format("%d コンボ！",count);
//		ui->setChatMessage(str);
		
	}
	
}
void PuzzleScene::changeOwnHP(int df)
{
	if(getPhase() == PHASE_PLAYER_1){
		setPlayer1HP(MIN(getHitpoit(PHASE_PLAYER_1),getPlayer1HP() + df));
	}
	if(getPhase() == PHASE_PLAYER_2){
		setPlayer2HP(MIN(getHitpoit(PHASE_PLAYER_2),getPlayer2HP() + df));
	}
}
void PuzzleScene::changeEnemyHP(int df)
{
	if(getPhase() == PHASE_PLAYER_1){
		setPlayer2HP(MIN(getHitpoit(PHASE_PLAYER_2),getPlayer2HP() + df));
	}
	if(getPhase() == PHASE_PLAYER_2){
		setPlayer1HP(MIN(getHitpoit(PHASE_PLAYER_1),getPlayer1HP() + df));
	}
}
void PuzzleScene::changeOwnPW(int df)
{
	if(getPhase() == PHASE_PLAYER_1){
		setPlayer1Power(MAX(0,MIN(MAXPOWER,getPlayer1Power() + df)));
	}
	if(getPhase() == PHASE_PLAYER_2){
		setPlayer2Power(MAX(0,MIN(MAXPOWER,getPlayer2Power() + df)));
	}
}
void PuzzleScene::changeEnemyPW(int df)
{
	if(getPhase() == PHASE_PLAYER_1){
		setPlayer2Power(MAX(MIN(MAXPOWER,getPlayer2Power() + df),0));
	}
	if(getPhase() == PHASE_PLAYER_2){
		setPlayer1Power(MAX(MIN(MAXPOWER,getPlayer1Power() + df),0));
	}
}
int PuzzleScene::getLBLevel(int power)
{
	if(power >= LBLEVEL1){
		if(power >= LBLEVEL2){
			if(power >= LBLEVLE3){
				return 3;
			}
			return 2;
		}
		return 1;
	}
	return 0;
}
int PuzzleScene::getLBPower(int level)
{
	switch(level){
		case 0:
			break;
		case 1:
			return LBLEVEL1;
		case 2:
			return LBLEVEL2;
		case 3:
			return LBLEVLE3;
		default:
			break;
	}
	return 0;
}

void PuzzleScene::updateScore()
{
	PuzzleUILayer* ui = (PuzzleUILayer*)getUINode();
	
	if(ui){
		ui->changePlayer1HP(getPlayer1HP());
		ui->changePlayer2HP(getPlayer2HP());
		ui->changePlayer1Power(getPlayer1Power());
		ui->changePlayer2Power(getPlayer2Power());
		int level = getLBLevel(getPlayer1Power());
		if(level > 0){
			ui->setLBEnable(level);
		}
	}
}

bool PuzzleScene::canUnitUseLB(int index)
{
	int rank = getLBLevel(getCurrentPlayerPower());
	PuzzleUnitManager* mgr = PuzzleUnitManager::getInstance();
	if(mgr){
		PuzzleMapUnit* pTarget = mgr->getUnit(index);
		if(rank > 0 && pTarget && pTarget->getRank() > 0){
			return true;
		}
	}
	return false;
}
//////////////////////////////////////////////////////////////////////////////////////////
//
//		アニメーション処理
//
//////////////////////////////////////////////////////////////////////////////////////////
void PuzzleScene::skillAttackAnimation()
{
	PuzzleUnitManager* mgr = PuzzleUnitManager::getInstance();
	Size winSize = Director::getInstance()->getWinSize();
	int rank = getLBLevel(getCurrentPlayerPower());
	if(rank == 0){
		return;
	}
	assert(mgr);
	if(mgr){
		int idx = mgr->getCurrentFrameIdx();
		PuzzleMapUnit* pTarget = mgr->getUnit(idx);
		if(pTarget && pTarget->getRank() > 0){
			MasterUnit* mUnit = pTarget->getUnit();
			Skill* skill = pTarget->getSkill(rank);
			if(mUnit && skill){
				Sprite* sp = Sprite::createWithSpriteFrameName(mUnit->getFrameName());
				Size spSize = sp->getContentSize();
				sp->setPosition(Point(winSize.width,winSize.height/ 2));
				sp->setScale(2.0f);
				sp->setVisible(true);
				addChild(sp,LZ_EFFECT,LTAG_EFFECT);
				Sequence* seq = Sequence::create(
												 MoveTo::create(0.4f, Vec2(winSize.width - spSize.width,winSize.height / 2)),
												 DelayTime::create(1.0f),
												 ScaleTo::create(0.4f,0.1f),
												 RemoveSelf::create(),
												 CallFunc::create([this]{ this->limitBreak();}),
												 NULL);
				sp->runAction(seq);
				
				Sprite* ttf = Sprite::createWithSpriteFrameName(V2C(skill->getImage()));
				Size tSize = ttf->getContentSize();
				ttf->setScale(winSize.width / tSize.width);
				ttf->setAnchorPoint(Vec2(0.5f,0.5f));
				ttf->setPosition(Point(0 - tSize.width,winSize.height/ 3 * 2));
				addChild(ttf,LZ_EFFECT,LTAG_EFFECT);
				Sequence* seqT = Sequence::create(
												 MoveTo::create(0.4f, Vec2(winSize.width / 2,winSize.height / 3 * 2)),
												 DelayTime::create(1.0f),
												 ScaleTo::create(0.4f,0.1f),
												 RemoveSelf::create(),
												 NULL);
				ttf->runAction(seqT);
				
			}
		}
		else{
			fullAttackAnimation();
		}
	}
}

void PuzzleScene::fullAttackAnimation()
{
	
	Size winSize = Director::getInstance()->getWinSize();
	Sprite* ttf = Sprite::createWithSpriteFrameName("limitbreak.png");
	ttf->setPosition(Point(winSize.width / 2,winSize.height/ 2));
	ttf->setScale(0.0f);
	ttf->setVisible(true);
	addChild(ttf,LZ_EFFECT,LTAG_EFFECT);
	CallFunc* cleanup = CallFunc::create([this]
										 {
											 this->limitBreak();
										 });
	Sequence* seq = Sequence::create(
									 ScaleTo::create(0.6f,3.0f),
									 DelayTime::create(1.0f),
									 ScaleTo::create(0.4f,0.1f),
									 RemoveSelf::create(),
									 cleanup,
									 NULL);
	ttf->runAction(seq);
	
}

void PuzzleScene::phaseChangeAnimation()
{
	std::string str = StringUtils::format("%s のこり%d回", V2C(getCurrentPhaseForce()->getName()),getPhaseCount());

	Size winSize = Director::getInstance()->getWinSize();
	Label* ttf = Label::createWithSystemFont(str.c_str(),DLG_FONT, DLG_LARGE_FONT_SIZE);
	ttf->setScale(0.0f);
	ttf->setTextColor(Color4B::BLACK);
	ttf->setPosition(Point(winSize.width / 2,winSize.height/ 2));
	addChild(ttf,LZ_EFFECT,LTAG_EFFECT);

	CallFunc* cleanup = CallFunc::create([this]
	{
		this->sayPhase();
		this->finishTask(PHASE_CHANGE_ANIMATION);
		if(this->getPhaseCount() == 0){
			this->phaseEnd();
		}
		else{
			this->phaseStart();
		}
	});
	Sequence* seq = Sequence::create(
			 ScaleTo::create(0.6f,3.0f),
			 DelayTime::create(1.0f),
			 ScaleTo::create(0.4f,0.1f),
			 RemoveSelf::create(),
			 cleanup,
			 NULL);
	addTask(PHASE_CHANGE_ANIMATION);
	ttf->runAction(seq);
	
}

void PuzzleScene::shuffleMessageAnimation()
{
	std::string str = "Shuffle!";
	
	Size winSize = Director::getInstance()->getWinSize();
	Label* ttf = Label::createWithSystemFont(str.c_str(),DLG_FONT, DLG_LARGE_FONT_SIZE);
	ttf->setScale(0.0f);
	ttf->setTextColor(Color4B::BLACK);
	ttf->setPosition(Point(winSize.width / 2,winSize.height/ 2));
	addChild(ttf,LZ_EFFECT,LTAG_EFFECT);
	log("*************start shuffle animation ");
	CallFunc* cleanup = CallFunc::create([this]
										 {
											 log("*************end shuffle animation ");
											 this->finishTask(SHUFFLE_ANIMATION);
											 this->phaseStart();
										 });
	Sequence* seq = Sequence::create(
									 ScaleTo::create(0.6f,3.0f),
									 DelayTime::create(1.5f),
									 ScaleTo::create(0.4f,0.1f),
									 RemoveSelf::create(),
									 cleanup,
									 NULL);
	addTask(SHUFFLE_ANIMATION);
	ttf->runAction(seq);
	
}

void PuzzleScene::gameInitAnimation()
{
	Size winSize = Director::getInstance()->getWinSize();
	Label* ttf = Label::createWithSystemFont("初期化",DLG_FONT, DLG_LARGE_FONT_SIZE);
	ttf->setScale(0.0f);
	ttf->setTextColor(Color4B::BLACK);
	ttf->setPosition(Point(winSize.width / 2,winSize.height/ 2));
	addChild(ttf,LZ_EFFECT,LTAG_EFFECT);
	addTask(TASK_INIT_ANIMATION);
	CallFuncN* cleanup = CallFuncN::create([this](Node* node)
	{
		if(node){
			this->finishTask(TASK_INIT_ANIMATION);
			this->phaseEnd();
			// 初期化アニメ終了時の処理を呼ぶ
		}
	});
	Sequence* seq = Sequence::create(
		ScaleTo::create(0.6f,3.0f),
		DelayTime::create(1.5f),
		ScaleTo::create(0.4f,0.1f),
		RemoveSelf::create(),
		cleanup,
		NULL);
	ttf->runAction(seq);
}
//////////////////////////////////////////////////////////////////////////////////////////
//
//		サーバ問い合わせ関数
//
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//
//		サーバアクセス用コールバック
//
//////////////////////////////////////////////////////////////////////////////////////////

void PuzzleScene::onRecieve(KcScene::COMMAND_NO no, Json *recieveJson)
{
	bool bSuccess = true;
	switch(no){
		case KcScene::PUZZLE_INIT:
			didPuzzleInit(recieveJson);
			break;
		case KcScene::PUZZLE_FINISH:
			didPuzzleFinish(recieveJson);
			break;
		default:
			break;
	}
	if(bSuccess){
		
	}
};

void PuzzleScene::onImageRecieve(KcScene::IMAGE_NO no, cocos2d::Image *image)
{
	PuzzleUILayer* ui = (PuzzleUILayer*)getUINode();
	if(ui && image){
		Texture2D* t = new Texture2D();
		t->initWithImage(image);
		if(no == KcScene::MY_GOOGLE_PLUS){
			setPlayer1Face(t);
			Sprite* sp = ui->getFaceSprite();
			Sprite* sp2 = ui->getPlayer1Face();
			if(sp &&  sp2){
				sp->setTexture(t);
				sp2->setTexture(t);
			}
		}
		else{
			setPlayer2Face(t);
			Sprite* sp3 = ui->getPlayer2Face();
			if(sp3){
				sp3->setTexture(t);
			}
		}
	}
}
//////////////////////////////////////////////////////////////////////////////////////////
//
//		YNDlg用メソッド
//
//////////////////////////////////////////////////////////////////////////////////////////

const char* PuzzleScene::getDlgTitleMessage()
{
	switch(getState()){
		case PUZZLE_INIT:
			break;
		case PUZZLE_INGAME:
			return "中断";
		case PUZZLE_END:
			return "ゲーム終了";
	}
	return "";
}

const char* PuzzleScene::getDlgBodyMessage()
{
	switch(getState()){
		case PUZZLE_INIT:
			break;
		case PUZZLE_INGAME:
			return "中断しますか？\nこのパズルで入手したものはすべて破棄されます";
		case PUZZLE_END:
			return "再度挑戦しますか？";
	}
	return "";
};

void PuzzleScene::onOk()
{
	switch(getState()){
		case PUZZLE_INIT:
			break;
		case PUZZLE_INGAME:
			setGameState(GAME_GIVEUP);
			setState(PUZZLE_END);
			puzzleMainLoop();
			break;
		case PUZZLE_END:
			setState(PUZZLE_INIT);
			setDlgState(CONNECT);
			puzzleMainLoop();
			break;
	}
	
}

void PuzzleScene::onCancel()
{
	switch(getState()){
		case PUZZLE_INIT:
			break;
		case PUZZLE_INGAME:
			break;
		case PUZZLE_END:
			closePuzzle();
			break;
	}
	
}

const char* PuzzleScene::getOkButtonText()
{
	switch(getState()){
		case PUZZLE_INIT:
			break;
		case PUZZLE_INGAME:
			return "中断";
		case PUZZLE_END:
			return "挑戦する";
	}
	return "OK";
}

const char* PuzzleScene::getCancelButtonText()
{
	switch(getState()){
		case PUZZLE_INIT:
			break;
		case PUZZLE_INGAME:
			return "中断しない";
		case PUZZLE_END:
			return "終了する";
	}
	return "OK";
}
//////////////////////////////////////////////////////////////////////////////////////////
//		複数の非同期処理が終了したら次の処理をする、ためのヘルプメソッド
//////////////////////////////////////////////////////////////////////////////////////////
void PuzzleScene::addTask(PuzzleScene::PUZZLE_TASK task)
{
	m_taskMap[task] = false;
}
void PuzzleScene::finishTask(PuzzleScene::PUZZLE_TASK task)
{
	m_taskMap[task] = true;
}
bool PuzzleScene::checkTaskFinished()
{
	std::map<PUZZLE_TASK,bool>::iterator it = m_taskMap.begin();
	while(it != m_taskMap.end()){
		bool isFinish = (bool)(*it).second;
		if(!isFinish){
			return false;
		}
		++it;
	}
	return true;
}
//////////////////////////////////////////////////////////////////////////////////////////
//		ヘルプメソッド
//////////////////////////////////////////////////////////////////////////////////////////
TMXTiledMap* PuzzleScene::getTMXTiledMap()
{
	if(getMapNode() != NULL){
		return ((PuzzleMapLayer*)getMapNode())->getTMXMap();
	}
	return NULL;
}

Force* PuzzleScene::getCurrentPhaseForce()
{
	if(getPhase() == PHASE_PLAYER_1){
		return getPlayer1Force();
	}
	if(getPhase() == PHASE_PLAYER_2){
		return getPlayer2Force();
	}
	return getNeutralForce();
}


long PuzzleScene::getHitpoit(PuzzleScene::PUZZLE_PHASE phase)
{
	if(phase == PHASE_PLAYER_1){
		GameCharacter* chara = KoumeChan::getInstance()->getGameCharacter();
		if(chara){
			return chara->getHP();
		}
	}
	if (phase == PHASE_PLAYER_2){
		return getPlayer2HitPoint();
	}
	return 100;
}

void PuzzleScene::limitBreak()
{
	int lank = 0;
	PuzzleUnitManager* mgr = PuzzleUnitManager::getInstance();
	if(getPhase() == PHASE_PLAYER_1 && getPlayer1Power() >= LBLEVEL1){
		setBreak(true);
		lank = getLBLevel(getPlayer1Power());
		setPlayer1Power(getPlayer1Power() - getLBPower(lank));
		mgr->limitBreak(lank);
	}
	if(getPhase() == PHASE_PLAYER_2 && getPlayer2Power() >= LBLEVEL1){
		setBreak(true);
		lank = getLBLevel(getPlayer2Power());
		setPlayer2Power(getPlayer2Power() - getLBPower(lank));
		mgr->limitBreak(lank);
	}
	if(getBreak()){
		mgr->dealUnit();
		addTask(RAILGUN_ACTION);
		mgr->unitAction(CallFunc::create([this]{
			this->finishTask(RAILGUN_ACTION);
			this->changePhase();
		}));
	}
}

int PuzzleScene::getCurrentPlayerPower()
{
	if(getPhase() == PHASE_PLAYER_1){
		return getPlayer1Power();
	}
	if(getPhase() == PHASE_PLAYER_2){
		return getPlayer2Power();
	}

	return 0;
}
long PuzzleScene::getSeed()
{
	PuzzleTMXTiledMap* map = (PuzzleTMXTiledMap*)getTMXTiledMap();
	if(map){
		long rnd =rand() + 1;
		long subs = rnd % map->getAppearanceRate();
		long uNo = map->findUnitNoFromRate(subs);
		return uNo;
	}
	return 0L;
}


