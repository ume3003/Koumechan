//
//  MajorQuestLayer.h
//  koumeChan
//
//  Created by 上野　彰三 on 2014/03/19.
//
//

#ifndef __koumeChan__MajorQuestLayer__
#define __koumeChan__MajorQuestLayer__

#include "cocos2d.h"
#include "cocosbuilder/cocosbuilder.h"
#include "KcListLayer.h"

class MajorQuestLayer : public KcListLayer
{
protected:
    virtual void onEnter();
	virtual bool init();

	virtual std::string getHeaderString() ;
	virtual bool enable(long index) ;
	
	virtual bool isSameCell(cocos2d::extension::TableViewCell* preCell,long index) ;
	virtual cocos2d::extension::TableViewCell* getNewCell(long index) ;
	virtual long numberOfCellsInTableView(cocos2d::extension::TableView* table);
	virtual void onTouchCell(long id);
	
	
public:
	MajorQuestLayer();
	virtual ~MajorQuestLayer();
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(MajorQuestLayer, create);
	
};

#endif /* defined(__koumeChan__MajorQuestLayer__) */
