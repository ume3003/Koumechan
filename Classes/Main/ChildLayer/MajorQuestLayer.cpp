//
//  MajorQuestLayer.cpp
//  koumeChan
//
//  Created by 上野　彰三 on 2014/03/19.
//
//

#include "MajorQuestLayer.h"
#include "KoumeChan.h"
#include "MainScene.h"
#include "KCDef.h"
#include "JsonKeyString.h"
#include "KcListCell.h"
#include "DirectionQuest.h"
#include "MajorQuest.h"

using namespace cocos2d;
using namespace std;
using namespace cocos2d::extension;

MajorQuestLayer::MajorQuestLayer()
{
	
}

MajorQuestLayer::~MajorQuestLayer()
{
	
}

bool MajorQuestLayer::init()
{
	if(KcListLayer::init()){
		return true;
	}
	return false;
};

void MajorQuestLayer::onEnter()
{
	KcListLayer::onEnter();
}

std::string MajorQuestLayer::getHeaderString()
{
	DirectionQuest* direction = KoumeChan::getInstance()->getDirectionMaster();
	if(direction){
		return direction->getName().asString();
	}
	return string("メインクエスト");
};
bool MajorQuestLayer::enable(long index)
{
	return true;
};

long MajorQuestLayer::numberOfCellsInTableView(cocos2d::extension::TableView* table)
{
	DirectionQuest* direction = KoumeChan::getInstance()->getDirectionMaster();
	if(direction){
		vector<long > v =direction->getMajorQuestNos();
		return v.size();
	}
	return 0L;
};

bool MajorQuestLayer::isSameCell(cocos2d::extension::TableViewCell* preCell,long index)
{
	DirectionQuest* direction = KoumeChan::getInstance()->getDirectionMaster();
	if(direction){
		vector<long > v =direction->getMajorQuestNos();
		KcListCell* preListCell = (KcListCell*)preCell;
	
		return preListCell->getId() == v.at(index);
	}
	return false;
};

cocos2d::extension::TableViewCell* MajorQuestLayer::getNewCell(long index)
{
	DirectionQuest* direction = KoumeChan::getInstance()->getDirectionMaster();
	if(direction){
		vector<long > v =direction->getMajorQuestNos();
		long majorQuestNo = v.at(index);
		MajorQuest* major = KoumeChan::getInstance()->getMajorQuestMaster(majorQuestNo);
		return KcListCell::create(major->getMasterNo(),major->getName(),Value(""),Size(getCellWidth(),getCellHeight()));
	}
	KcListCell* cell = KcListCell::create(index, Value(StringUtils::format("No %ld",index)), Value(""), Size(getCellWidth(),getCellHeight()));
	return cell;
};
void MajorQuestLayer::onTouchCell(long id)
{
	KoumeChan::getInstance()->changeMajorQuest(id);
	((MainScene*)getParent())->showMinorQuestLayer();
}



