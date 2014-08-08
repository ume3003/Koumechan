//
//  ShikigamiUnit.h
//  Koumechan
//
//  Created by 上野　彰三 on 2014/07/30.
//
//

#ifndef __Koumechan__ShikigamiUnit__
#define __Koumechan__ShikigamiUnit__


#include "cocos2d.h"
#include "PuzzleMapUnit.h"
#include "MasterUnit.h"

class ShikigamiUnit : public PuzzleMapUnit
{
public:
	
	static ShikigamiUnit* createWithData(long unitNo,cocos2d::Point pos,int actionOrder,cocos2d::Scene* scene,int rank,long shikigamiNo);
	
protected:
	virtual bool setupSprite();
	virtual cocos2d::FiniteTimeAction* appearAction(PuzzleAction* action);
	virtual cocos2d::FiniteTimeAction* desappearAction(PuzzleAction* action);
	virtual cocos2d::FiniteTimeAction* createAction(PuzzleAction* action);
	
	

};

#endif /* defined(__Koumechan__ShikigamiUnit__) */
