//
//  MinorQuestLayer.h
//  koumeChan
//
//  Created by 上野　彰三 on 2014/03/19.
//
//

#ifndef __koumeChan__MinorQuestLayer__
#define __koumeChan__MinorQuestLayer__

#include "cocos2d.h"
#include "cocosbuilder/cocosbuilder.h"
#include "KcListLayer.h"

class MinorQuestLayer : public KcListLayer
{
protected:
    virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual bool init();
	

	virtual std::string getHeaderString() ;
	virtual bool enable(long index);
	
	virtual bool isSameCell(cocos2d::extension::TableViewCell* preCell,long index) ;
	virtual cocos2d::extension::TableViewCell* getNewCell(long index) ;
	virtual long numberOfCellsInTableView(cocos2d::extension::TableView* table) ;
	virtual void onTouchCell(long id);
	
public:
	MinorQuestLayer() ;
	virtual ~MinorQuestLayer() ;
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(MinorQuestLayer, create);
	
	virtual cocos2d::extension::Control::Handler onResolveCCBCCControlSelector(cocos2d::Ref* pTarget,const char* pSelectorName);
	void tappedBack(cocos2d::Ref* pSender,cocos2d::extension::Control::EventType pCCControlEvent);
	
};

#endif /* defined(__koumeChan__MinorQuestLayer__) */
