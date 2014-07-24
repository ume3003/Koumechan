//
//  MinorQuestLayer.cpp
//  koumeChan
//
//  Created by 上野　彰三 on 2014/03/19.
//
//

#include "MinorQuestLayer.h"
#include "KoumeChan.h"
#include "KCDef.h"
#include "JsonKeyString.h"
#include "MainScene.h"
#include "MajorQuest.h"
#include "MinorQuest.h"
#include "KcListCell.h"

using namespace cocos2d;
using namespace std;
using namespace cocos2d::extension;

MinorQuestLayer::MinorQuestLayer()
{
	
}

MinorQuestLayer::~MinorQuestLayer()
{
	
}

bool MinorQuestLayer::init()
{
	if(KcListLayer::init()){
		return true;
	}
	return false;
};

void MinorQuestLayer::onEnterTransitionDidFinish()
{
	//	KoumeChan* chan = KoumeChan::getInstance();
	KcListLayer::onEnterTransitionDidFinish();
};

void MinorQuestLayer::onEnter()
{
	KcListLayer::onEnter();
}

std::string MinorQuestLayer::getHeaderString()
{
	MajorQuest* quest = KoumeChan::getInstance()->getMajorQuestMaster();
	if(quest){
		return quest->getName().asString();
	}
	return string("");
};
bool MinorQuestLayer::enable(long index)
{
	return true;
};
long MinorQuestLayer::numberOfCellsInTableView(cocos2d::extension::TableView* table)
{
	MajorQuest* quest = KoumeChan::getInstance()->getMajorQuestMaster();
	if(quest){
		vector<long> v = quest->getMinorQuestNos();
		return v.size();
	}
	return 0L;
};
bool MinorQuestLayer::isSameCell(cocos2d::extension::TableViewCell* preCell,long index)
{
	MajorQuest* quest = KoumeChan::getInstance()->getMajorQuestMaster();
	if(quest){
		vector<long> v = quest->getMinorQuestNos();
		KcListCell* preListCell = (KcListCell*)preCell;
		return preListCell->getId() == v.at(index);
	}
	return false;
};
cocos2d::extension::TableViewCell* MinorQuestLayer::getNewCell(long index)
{
	MajorQuest* quest = KoumeChan::getInstance()->getMajorQuestMaster();
	if(quest){
		vector<long> v = quest->getMinorQuestNos();
		long minorQuestNo = v.at(index);
		MinorQuest* minor = KoumeChan::getInstance()->getMinorQuestMaster(minorQuestNo);
		return KcListCell::create(minor->getMasterNo(),minor->getName(),Value(""),Size(getCellWidth(),getCellHeight()));
	}
	KcListCell* cell = KcListCell::create(index, Value(StringUtils::format("No %ld",index)), Value(""), Size(getCellWidth(),getCellHeight()));
	return cell;
};
void MinorQuestLayer::onTouchCell(long id)
{
	KoumeChan* chan = KoumeChan::getInstance();
	chan->setMinorQuest(id);
	chan->showPuzzleScene();
}
void MinorQuestLayer::tappedBack(cocos2d::Ref* pSender,cocos2d::extension::Control::EventType pCCControlEvent)
{
	MainScene* scene = (MainScene*)getParent();
	scene->showMajorQuestLayer();
}

Control::Handler MinorQuestLayer::onResolveCCBCCControlSelector(cocos2d::Ref *pTarget, const char *pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "tappedBack"		, MinorQuestLayer::tappedBack);
	return NULL;
}
