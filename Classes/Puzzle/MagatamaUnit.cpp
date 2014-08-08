//
//  MagatamaUnit.cpp
//  Koumechan
//
//  Created by 上野　彰三 on 2014/07/30.
//
//

#include "MagatamaUnit.h"
#include "SSPlayer.h"
#include "SSAnimationMgr.h"
#include "SSAnimationData.h"

using namespace cocos2d;

MagatamaUnit* MagatamaUnit::createWithData(long unitNo,Point pos,int actionOrder,Scene* scene)
{
	MagatamaUnit* pRet = new MagatamaUnit();
	if(pRet){
		if(pRet->initWithData(unitNo,pos,actionOrder,scene)){
			pRet->autorelease();
		}
		else{
			CC_SAFE_DELETE(pRet);
			pRet = NULL;
		}
	}
	return pRet;
}

bool MagatamaUnit::setupSprite()
{
	MasterUnit* unit = getUnit();
	SSAnimationData* pData = getAnimeData(WAIT_ANIME);
	if(unit && pData){
		setAnimation(pData->getSSData(), pData->getImageList(),0);
		Texture2D* pTex = pData->getTexture(TEX_UNIT);
//		setTexture(pTex);
		Rect rect = Rect::ZERO;
		rect.size = pTex->getContentSize();
		float scale = Director::getInstance()->getContentScaleFactor();
		rect.size.width = rect.size.width / scale;
		rect.size.height = rect.size.height / scale;
//		log("%3.2f/%3.2f",rect.size.width,rect.size.height);
//		setContentSize(rect.size);
//		setTextureRect(rect);
		setAnchorPoint(Point(0,0));
		setScale(0.1f);
		return true;
	}
	return false;
	
}
FiniteTimeAction* MagatamaUnit::appearAction(PuzzleAction* action)
{
	float scale = Director::getInstance()->getContentScaleFactor();
	return ScaleTo::create(action->getDuration(),1.0f / scale);
};

FiniteTimeAction* MagatamaUnit::desappearAction(PuzzleAction* action)
{
	return ScaleTo::create(action->getDuration(),0.0f);
};

void MagatamaUnit::doWaitingAnimation()
{
	SSAnimationData* pData = getAnimeData(WAIT_ANIME);
	if(pData){
		
	//	setAnchorPoint(Vec2(0,0));
	}
}

SSAnimationData* MagatamaUnit::getAnimeData(PuzzleMapUnit::ANIME_TYPE type)
{
	MasterUnit* unit = getUnit();
	SSAnimationMgr* aMgr = SSAnimationMgr::getInstance();
	if(unit && aMgr){
		return aMgr->getAnimation(unit->getMasterNo(), type);
	}
	return NULL;
}