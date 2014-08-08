//
//  ShikigamiUnit.cpp
//  Koumechan
//
//  Created by 上野　彰三 on 2014/07/30.
//
//

#include "ShikigamiUnit.h"
#include "Emotion.h"
using namespace cocos2d;

ShikigamiUnit* ShikigamiUnit::createWithData(long unitNo,Point pos,int actionOrder,Scene* scene,int rank,long shikigamiNo)
{
	ShikigamiUnit* pRet = new ShikigamiUnit();
	if(pRet && pRet->initWithData(unitNo,pos,actionOrder,scene,rank,shikigamiNo)){
		pRet->autorelease();
	}
	else{
		CC_SAFE_DELETE(pRet);
		pRet = NULL;
	}
	return pRet;
}

bool ShikigamiUnit::setupSprite()
{
	MasterUnit* unit = getShikigamiUnit();
	if(unit ){
		setSpriteFrame(unit->getFrameName());
		setAnchorPoint(Point(0.5,0.5));
		setScale(0.0f);
		return true;
	}
	return false;
	
}

FiniteTimeAction* ShikigamiUnit::appearAction(PuzzleAction* action)
{
	return ScaleTo::create(action->getDuration(),getScaleToCell());
};

FiniteTimeAction* ShikigamiUnit::desappearAction(PuzzleAction* action)
{
	return ScaleTo::create(action->getDuration(),0.0f);
};
FiniteTimeAction* ShikigamiUnit::createAction(PuzzleAction *action)
{
	return CallFunc::create([this]{
		Sprite* sp = Emotion::getInstance()->getNumberSprite(this->getRank());
		Size s = this->getContentSize();
		sp->setScale(1 / this->getScaleToCell());
		sp->setPosition(Point(s.width - sp->getContentSize().width / this->getScaleToCell(),s.height - sp->getContentSize().height / this->getScaleToCell()));
		this->addChild(sp, 98, 98);
		this->setVisible(true);
	});
}
