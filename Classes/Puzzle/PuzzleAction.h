//
//  PuzzleAction.h
//  koumeChan
//
//  Created by 上野　彰三 on 2014/04/03.
//
//

#ifndef __koumeChan__PuzzleAction__
#define __koumeChan__PuzzleAction__

#include "cocos2d.h"
#include "BaseDamage.h"
#include "Koumechan.h"

class PuzzleAction : public cocos2d::Ref
{
public:
	enum PZ_ACTION {
		PZ_CREATE = 0,
		PZ_APPEAR,
		PZ_WAIT,
		PZ_MOVE,
		PZ_DOWN,
		PZ_DOWNLEFT,
		PZ_DOWNRIGHT,
		PZ_MARK,
		PZ_MOVEOUT,
		PZ_DESAPPEAR,
		PZ_DOCALLBACK,
		PZ_CHAINCOUNT,
		PZ_WARP,
		PZ_ATTACK,
		PZ_EXPLOSION,
		PZ_SCORE,
		PZ_ELITE_SCORE,
		PZ_ELITE_APPREAR
	};
	static PuzzleAction* create(PZ_ACTION action,cocos2d::Point pos,float duration,BaseDamage::BD_TYPE nScore = BaseDamage::THREE_OWN);
	static PuzzleAction* createWithJson(Json* json);
	virtual std::string toJsonString();
	void extendEndPoint(cocos2d::Point pos,float duration);
	void extendDuration(float duration);
	
protected:
	PuzzleAction();
	virtual ~PuzzleAction();
	virtual bool init(PZ_ACTION action,cocos2d::Point pos,float duration,BaseDamage::BD_TYPE nScore);
	virtual bool initWithJson(Json* json);
	
	CC_SYNTHESIZE(PZ_ACTION,m_action,Action);
	CC_SYNTHESIZE(cocos2d::Point,m_pos,Pos);
	CC_SYNTHESIZE(float, m_duration, Duration);
	CC_SYNTHESIZE(BaseDamage::BD_TYPE, m_ScoreType, ScoreType);
};

#endif /* defined(__koumeChan__PuzzleAction__) */
