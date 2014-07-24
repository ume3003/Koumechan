//
//  PuzzleAction.cpp
//  koumeChan
//
//  Created by 上野　彰三 on 2014/04/03.
//
//

#include "PuzzleAction.h"
#include "KCDef.h"
#include "KoumeChan.h"
#include "JsonKeyString.h"

using namespace cocos2d;
using namespace std;

PuzzleAction* PuzzleAction::create(PZ_ACTION action,Point pos,float duration,BaseDamage::BD_TYPE nType)
{
	PuzzleAction* pRet = new PuzzleAction();
	if(pRet && pRet->init(action,pos,duration,nType)){
		pRet->autorelease();
	}
	else{
		CC_SAFE_DELETE(pRet);
		pRet = NULL;
	}
	return pRet;
};

PuzzleAction* PuzzleAction::createWithJson(Json* json)
{
	PuzzleAction* pRet = new PuzzleAction();
	if(pRet && pRet->initWithJson(json)){
		pRet->autorelease();
	}
	else{
		CC_SAFE_DELETE(pRet);
		pRet = NULL;
	}
	return pRet;
};

PuzzleAction::PuzzleAction()
{
	
};

PuzzleAction::~PuzzleAction()
{
	
};

bool PuzzleAction::init(PZ_ACTION action,Point pos,float duration,BaseDamage::BD_TYPE score)
{
	setAction(action);
	setPos(pos);
	setDuration(duration);
	setScoreType(score);
	return true;
};

bool PuzzleAction::initWithJson(Json* json)
{
	if(json){
		setAction((PZ_ACTION)KoumeChan::getInt(json,JS_ACTION_NO,PZ_CREATE));
		int nPos = KoumeChan::getInt(json,JS_POSITION,-1);
		if(nPos >= 0){
			setPos(idxToPos(nPos));
		}
		else{
			setPos(Point(-1,-1));
		}
		setDuration(KoumeChan::getFloat(json, JS_DURATION, 0.0f));
		setScoreType((BaseDamage::BD_TYPE)KoumeChan::getInt(json,JS_SCORE_TYPE,0));
		return true;
	}
	return false;
};
// {"ACTIONNO" : "0","POSITION" : "0","DURATION,"0.0"}
std::string PuzzleAction::toJsonString()
{
	return StringUtils::format("{%s,%s,%s,%s}",
			jsLong(JS_ACTION_NO,(long)getAction()).c_str(),
			jsInt(JS_POSITION, xyToIdx(getPos())).c_str(),
			jsFloat(JS_DURATION,getDuration()).c_str(),
			jsInt(JS_SCORE_TYPE,getScoreType()).c_str());
}
void PuzzleAction::extendEndPoint(cocos2d::Point pos,float duration)
{
	setDuration(getDuration() + duration);
	setPos(pos);
}

void PuzzleAction::extendDuration(float duration)
{
	setDuration(getDuration() + duration);	
}



