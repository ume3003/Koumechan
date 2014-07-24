//
//  CompetitionScene.h
//  Koumechan
//
//  Created by 上野　彰三 on 2014/07/07.
//
//

#ifndef __Koumechan__CompetitionScene__
#define __Koumechan__CompetitionScene__

#include "cocos2d.h"
#include "KoumeChan.h"
#include "PuzzleScene.h"

class CompetitionScene : public PuzzleScene
{
public:
	static CompetitionScene* create();
	virtual bool init();
	virtual MasterMap* getCurrentMap();
	virtual PuzzleTMXTiledMap* createTiledMap();
	virtual void userMove(cocos2d::Point pos1,cocos2d::Point pos2);
	virtual void userUnitLBCommand(cocos2d::Point pos);
	virtual void userAllLBCommand();
	virtual void userSelectUnit(cocos2d::Point pos);
	virtual long getSeed();
	virtual std::string getOwnUnitSpriteFrameName(int no) ;
	void setUnitSpriteName(int no,std::string name);

protected:
	enum COMMAND {
		NONE = -1,
		START = 0,
		MOVE,
		UNIT_LB,
		ALL_LB,
		SELECT_UNIT
	};
	virtual void closePuzzle();
	virtual ~CompetitionScene();

	virtual void player2();
	virtual void changePhaseDetail();
	virtual void finishGame();
	
	virtual void didPuzzleInit(Json* json);
	virtual void didPuzzleFinish(Json* json);
	virtual void doPuzzleInit();
	virtual void doPuzzleFinish();

	virtual long getPlayer2HitPoint();
	virtual int getCurrentMaxPhaseCount(PUZZLE_PHASE phase);
	
	void askSeed();
	void sioGameData(cocos2d::network::SIOClient *client, const std::string& data);
	void sioLeftRoom(cocos2d::network::SIOClient *client, const std::string& data);
	void sioGotSeed(cocos2d::network::SIOClient * client, const std::string& data);
	void sioGotReady(cocos2d::network::SIOClient * client, const std::string& data);
	void sioLinkedDown(cocos2d::network::SIOClient * client, const std::string& data);

	void startCommand(Json* json);
	void moveCommand(int idx1,int idx2);
	void unitLBCommand(int idx1);
	void allLBCommand();
	void selectUnit(int idx);
	
	void sendMessageToReady();
	
	std::vector<int> m_vecRateArray;
	CC_SYNTHESIZE(int, m_RatePos, RatePos);
	CC_SYNTHESIZE(std::string,m_unitSpriteName1,UnitSpriteName1);
	CC_SYNTHESIZE(std::string,m_unitSpriteName2,UnitSpriteName2);
};

#endif /* defined(__Koumechan__CompetitionScene__) */
