//
//  KcListLayer.cpp
//  koumeChan
//
//  Created by 上野　彰三 on 2014/03/19.
//
//

#include "KcListLayer.h"
#include "KcListCell.h"
#include "KoumeChan.h"

using namespace cocos2d;
using namespace cocos2d::extension;
using namespace cocosbuilder;
using namespace std;

KcListLayer::KcListLayer() : m_HeaderSprite(NULL),m_HeaderTTF(NULL),m_ListViewNode(NULL),m_tileBase(NULL),m_header(NULL),m_tableView(NULL)
{
	
};
KcListLayer::~KcListLayer()
{
	CC_SAFE_RELEASE(m_ListViewNode);
	CC_SAFE_RELEASE(m_HeaderTTF);
	CC_SAFE_RELEASE(m_HeaderSprite);
	CC_SAFE_RELEASE(m_header);
	CC_SAFE_RELEASE(m_tableView);
}

bool KcListLayer::init()
{
	if(KcLayer::init()){
		return true;
	}
	return false;
}

void KcListLayer::onEnter()
{
	KcLayer::onEnter();
	initControl(m_header, true, true);
	Size size = m_ListViewNode->getContentSize();
	size.height = size.height - KoumeChan::getInstance()->getDiffHeight() * 2;
	m_ListViewNode->setContentSize(size);
	initControl(m_ListViewNode, false, true);
	m_HeaderTTF->setString(getHeaderString().c_str());
	
	setCellHeight(m_ListViewNode->getContentSize().height / 5);
	setCellWidth(m_ListViewNode->getContentSize().width);

	Size sizeN = m_ListViewNode->getContentSize();
	TableView* tableView = TableView::create(this,sizeN);
	tableView->setDirection(ScrollView::Direction::VERTICAL);
	tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
	tableView->setPosition(Point(0.0f,0.0f));
	tableView->setDelegate(this);
	tableView->setContentSize(sizeN);
	m_ListViewNode->addChild(tableView,KTAG_TABLE_VIEW,KZORDER_TABLE_VIEW);
	tableView->reloadData();
	setTableView(tableView);
	
};

Size KcListLayer::cellSizeForTable(cocos2d::extension::TableView* table)
{
	return Size(getCellWidth(),getCellHeight());
}

TableViewCell* KcListLayer::tableCellAtIndex(cocos2d::extension::TableView *table, long index)
{
	TableViewCell* cell = table->dequeueCell();
	if(cell){
		if(!isSameCell(cell,index)){				// cellがもっているアイテムの識別IDが同じかをチェック
			cell = getNewCell(index);
		}
	}
	else{
		cell = getNewCell(index);
	}
	return cell;
}

void KcListLayer::tableCellTouched(TableView *table, TableViewCell *cell)
{
	KcListCell* kcell = (KcListCell*)cell;
	if(enable(kcell->getId())){
		log("cell touch %ld",kcell->getId());
		onTouchCell(kcell->getId());
	}
}



bool KcListLayer::onAssignCCBMemberVariable(Ref* pTarget, const char* pMemberVariableName, Node* pNode)
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_tileBase"		, Node*		, m_tileBase);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_HeaderSprite"	, Sprite*	, m_HeaderSprite);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_HeaderTTF"		, Label*	, m_HeaderTTF);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_ListViewNode"	, Node*		, m_ListViewNode);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_header", Node*, m_header);
	
	return false;
}
bool KcListLayer::onKCTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)
{
	return false;
}
