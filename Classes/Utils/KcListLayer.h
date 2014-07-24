//
//  KcListLayer.h
//  koumeChan
//
//  Created by 上野　彰三 on 2014/03/19.
//
//

#ifndef __koumeChan__KcListLayer__
#define __koumeChan__KcListLayer__

#include "KcLayer.h"
#include "cocos2d.h"
#include "cocos-ext.h"
#include "cocosbuilder/cocosbuilder.h"

class KcListLayer : public KcLayer,public cocosbuilder::CCBSelectorResolver ,public cocosbuilder::CCBMemberVariableAssigner,public cocos2d::extension::TableViewDataSource,public cocos2d::extension::TableViewDelegate
{
public:
	enum K_TAG {
		KTAG_TABLE_VIEW
	};
	enum K_ZO {
		KZORDER_TABLE_VIEW
	};
	enum COL_TAG {
		CTAG_SPRITE = 1,
		CTAG_LABEL,
		CTAG_DETAIL
	};
	
	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::Ref* pTarget,const char* pSelectorName) {return NULL;}
	virtual cocos2d::extension::Control::Handler onResolveCCBCCControlSelector(cocos2d::Ref* pTarget,const char* pSelectorName) {return NULL;};
	virtual bool onAssignCCBMemberVariable(cocos2d::Ref* pTarget, const char* pMemberVariableName, cocos2d::Node* pNode);

	virtual bool onKCTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
	virtual void onKCTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) {};
	virtual void onKCTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) {};
	virtual void onKCTouchCancelled(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) {};
	
protected:
	KcListLayer();
	virtual ~KcListLayer();
	virtual bool init();
	virtual void onEnter();

	virtual void onTouchCell(long id) = 0;
	virtual std::string getHeaderString() = 0;
	virtual bool enable(long index) = 0;
	virtual bool isSameCell(cocos2d::extension::TableViewCell* preCell,long index) = 0;
	virtual cocos2d::extension::TableViewCell* getNewCell(long index) = 0;
	virtual long numberOfCellsInTableView(cocos2d::extension::TableView* table) = 0;

	virtual cocos2d::Size cellSizeForTable(cocos2d::extension::TableView* table);
	virtual void scrollViewDidScroll(cocos2d::extension::ScrollView* view) {};
	virtual void scrollViewDidZoom(cocos2d::extension::ScrollView* view) {};
	
	virtual void tableCellTouched(cocos2d::extension::TableView* table,cocos2d::extension::TableViewCell* cell);
	virtual cocos2d::extension::TableViewCell* tableCellAtIndex(cocos2d::extension::TableView* table,long index);
	
	CC_SYNTHESIZE_RETAIN(cocos2d::Sprite*, m_HeaderSprite, HeaderSprite);
	CC_SYNTHESIZE_RETAIN(cocos2d::Label*, m_HeaderTTF, HeaderTTF);
	CC_SYNTHESIZE_RETAIN(cocos2d::Node*, m_ListViewNode, ListViewNode);
	CC_SYNTHESIZE_RETAIN(cocos2d::Node*, m_tileBase, TileBase);
	CC_SYNTHESIZE_RETAIN(cocos2d::Node*, m_header, Header);
	
	CC_SYNTHESIZE_RETAIN(cocos2d::extension::TableView*, m_tableView, TableView);
	
	CC_SYNTHESIZE(float, m_cellHeight, CellHeight);
	CC_SYNTHESIZE(float, m_cellWidth , CellWidth);
};

#endif /* defined(__koumeChan__KcListLayer__) */
