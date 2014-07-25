//
//  QuestScene.h
//  Koumechan
//
//  Created by 上野　彰三 on 2014/07/07.
//
//

#ifndef __Koumechan__QuestScene__
#define __Koumechan__QuestScene__

#include "cocos2d.h"
#include "KoumeChan.h"
#include "PuzzleScene.h"

class QuestScene : public PuzzleScene
{
public:
	static QuestScene* create();
	virtual bool init();
	virtual MasterMap* getCurrentMap();
	virtual PuzzleTMXTiledMap* createTiledMap();

protected:
	
	virtual void player2();
	virtual void changePhaseDetail();
	virtual void finishGame();
	
	virtual void didPuzzleInit(Json* json);
	virtual void didPuzzleFinish(Json* json);
	virtual void doPuzzleInit();
	virtual void doPuzzleFinish();
	
	virtual long getPlayer2HitPoint();
	virtual int getCurrentMaxPhaseCount(PUZZLE_PHASE phase);

	bool comUseSkill();
	void sayWords(Words::WORDS word);
	MasterNPC* getCurrentNPC();
	MinorQuest* getCurrentMinorQuest();

};

#endif /* defined(__Koumechan__QuestScene__) */
