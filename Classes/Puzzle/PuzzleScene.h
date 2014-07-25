//
//  PuzzleScene.h
//  koumeChan
//
//  Created by 上野　彰三 on 2014/03/25.
//
//

#ifndef __koumeChan__PuzzleScene__
#define __koumeChan__PuzzleScene__

#include "cocos2d.h"
#include "KoumeChan.h"
#include "KcScene.h"
#include "Words.h"
#include "PuzzleTMXTiledMap.h"
#include "PuzzleMapUnit.h"
#include "PuzzleAction.h"
#include "PuzzleActionManager.h"
#include "PuzzleChainManager.h"
#include "IYNDlgReciever.h"
#include "IConnectInfoDlgReciever.h"

class PuzzleScene : public KcScene,public IConnectInfoDlgReciever,public IYNDlgReciever
{
	
public:
	enum LAYER_TAG {
		LTAG_UI = 1,
		LTAG_MAP,
		LTAG_EFFECT,
		LTAG_UNITBASE = 100
	};
	enum LAYER_ZORDER {
		LZ_MAP = 1,
		LZ_UNIT,
		LZ_UI = 99,
		LZ_EFFECT
	};
	enum PUZZLE_STATE {
		PUZZLE_INIT = 0,
		PUZZLE_INGAME,
		PUZZLE_END
	};
	enum PUZZLE_GAME_STATE {
		GAME_INGAME = 0,
		GAME_GIVEUP,
		GAME_OVER,
	};
	enum INFO_DLG_STATE {
		CONNECT = 0,
		FINISH_GAME
	};
	
	enum PUZZLE_PHASE {
		PHASE_NONE = 0,
		PHASE_PLAYER_1,
		PHASE_PLAYER_2
	};
	enum PUZZLE_TASK {
		TASK_UNIT_INIT_ANIME = 0,
		TASK_INIT_ANIMATION,
		PHASE_CHANGE_ANIMATION,
		USER_CHAIN_ANIMATION,
		COM_CHAIN_ANIMATION,
		SHUFFLE_ANIMATION,
		SHUFFLE_CHAIN_ANIMATION,
		RAILGUN_ACTION
	};
	
	virtual bool init();

	void addTask(PUZZLE_TASK task);
	void cancelUserMove();
	void finishUserMove();

	void puzzleMainLoop();
	cocos2d::TMXTiledMap* getTMXTiledMap();

	void doShuffle();
	void updateScore();
	void changeOwnHP(int df);
	void changeEnemyHP(int df);
	void changeOwnPW(int df);
	void changeEnemyPW(int df);
	
	Force* getCurrentPhaseForce();
	Friends* getCurrentPhasePlayer();
	virtual MasterMap* getCurrentMap() = 0;
	
	
	long getHitpoit(PUZZLE_PHASE phase);
	
	void fullAttackAnimation();
	void skillAttackAnimation();

	void sayComboCount(int count);
	void saySkill(long skillNo);
	
	virtual std::string getOwnUnitSpriteFrameName(int no);
	int getCurrentPlayerPower();
	int getLBPower(int level);
	int getLBLevel(int power);
	
	virtual PuzzleTMXTiledMap* createTiledMap() = 0;
	virtual void userMove(cocos2d::Point pos1,cocos2d::Point pos2) {};
	virtual void userUnitLBCommand(cocos2d::Point pos) {};
	virtual void userAllLBCommand() {};
	virtual void userSelectUnit(cocos2d::Point pos) {};
	virtual long getSeed();
	
	bool canUnitUseLB(int index);
	
protected:
	PuzzleScene();
	virtual ~PuzzleScene();
	
	
	// 接続ダイアログ用
	virtual const char* getConnectInfoDlgTitleMessage();
	virtual const char* getConnectInfoDlgBodyMessage();
	virtual const char* getConnectInfoCancelButtonText();
	virtual void onConnectInfoCancel();
	
	// YNダイアログ用
	const char* getDlgTitleMessage();
	const char* getDlgBodyMessage();
	const char* getOkButtonText();
	const char* getCancelButtonText();
	void onOk();
	void onCancel();

	
	void changePhase();
	virtual void player2();
	virtual void finishGame() = 0;
	
	virtual void closePuzzle();
	void endPuzzle();
	void winLoseDlg();
	
	// セリフ
	void sayPhase();
	
	void updateCurrentPhaseCount();
	
	
	void limitBreak();

	
	// 画面全体アニメーション
	void gameInitAnimation();
	void phaseChangeAnimation();
	void shuffleMessageAnimation();
	
	// サーバアクセス
	virtual void onRecieve(KcScene::COMMAND_NO no,Json* recieveJson);
	virtual void onImageRecieve(IMAGE_NO no,cocos2d::Image* image);

	virtual void doPuzzleInit() = 0;
	virtual void didPuzzleInit(Json* json) = 0;
	
	virtual void doPuzzleFinish() = 0;
	virtual void didPuzzleFinish(Json* json) = 0;
	
	
	void initEnd();
	void phaseStart();
	void phaseEnd();
	void finishTask(PUZZLE_TASK task);
	virtual void changePhaseDetail() = 0;
	virtual long getPlayer2HitPoint() = 0;
	virtual int getCurrentMaxPhaseCount(PUZZLE_PHASE phase) = 0;


	bool checkTaskFinished();
	
	// ヘルプ関数
	void addOwnUnitFrameName(std::string frameName);

	
	std::map<PUZZLE_TASK,bool> m_taskMap;
	std::vector<std::string> m_ownUnitFrameName;
	
	void clearTask()	{ m_taskMap.clear();};
	
	CC_SYNTHESIZE_RETAIN(cocos2d::Node*, m_UI, UINode);
	CC_SYNTHESIZE_RETAIN(cocos2d::Node*, m_Map, MapNode);
	
	CC_SYNTHESIZE(bool, m_playable, Playable);
	CC_SYNTHESIZE(PUZZLE_STATE, m_state, State);
	CC_SYNTHESIZE(PUZZLE_GAME_STATE,m_gameState,GameState);
	CC_SYNTHESIZE(int,m_turn,Turn);
	CC_SYNTHESIZE(INFO_DLG_STATE,m_dlgState,DlgState);
	CC_SYNTHESIZE(PUZZLE_PHASE, m_phase, Phase);
	CC_SYNTHESIZE(bool,m_break,Break);
	CC_SYNTHESIZE(int, m_PhaseCount, PhaseCount);
	CC_SYNTHESIZE(bool,m_ComPlayer,ComPlayer);
	CC_SYNTHESIZE(PUZZLE_PHASE, m_battleFirst, BattleFirst);
	
	CC_SYNTHESIZE(long,m_player1HP ,Player1HP);
	CC_SYNTHESIZE(long,m_player2HP ,Player2HP);
	CC_SYNTHESIZE(long,m_player1Power ,Player1Power);
	CC_SYNTHESIZE(long,m_player2Power ,Player2Power);
	CC_SYNTHESIZE_RETAIN(Friends*,m_Player1,Player1);
	CC_SYNTHESIZE_RETAIN(Friends*,m_Player2,Player2);
	
	CC_SYNTHESIZE_RETAIN(Force*, m_NeutralForce, NeutralForce);
	CC_SYNTHESIZE_RETAIN(Force*, m_player1Force, Player1Force);
	CC_SYNTHESIZE_RETAIN(Force*, m_player2Force, Player2Force);
	
	CC_SYNTHESIZE_RETAIN(cocos2d::Texture2D*, m_Player1Face, Player1Face);
	CC_SYNTHESIZE_RETAIN(cocos2d::Texture2D*, m_Player2Face, Player2Face);
	
};



#endif /* defined(__koumeChan__PuzzleScene__) */
