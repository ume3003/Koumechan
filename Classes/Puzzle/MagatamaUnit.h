//
//  MagatamaUnit.h
//  Koumechan
//
//  Created by 上野　彰三 on 2014/07/30.
//
//

#ifndef __Koumechan__MagatamaUnit__
#define __Koumechan__MagatamaUnit__

#include "cocos2d.h"
#include "PuzzleMapUnit.h"
#include "SSAnimationData.h"

class MagatamaUnit : public PuzzleMapUnit
{
public:
	enum MAGATAMA_TEXTURE {
		TEX_PLATE = 0,
		TEX_EFFECT,
		TEX_UNIT
	};
	static MagatamaUnit* createWithData(long unitNo,cocos2d::Point pos,int actionOrder,cocos2d::Scene* scene);
	virtual void doWaitingAnimation();

protected:
	virtual bool setupSprite();
	virtual cocos2d::FiniteTimeAction* desappearAction(PuzzleAction* action);
	virtual cocos2d::FiniteTimeAction* appearAction(PuzzleAction* action);
	virtual SSAnimationData* getAnimeData(PuzzleMapUnit::ANIME_TYPE type);
};


#endif /* defined(__Koumechan__MagatamaUnit__) */
