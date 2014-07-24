//
//  KcListCell.h
//  koumeChan
//
//  Created by 上野　彰三 on 2014/03/20.
//
//

#ifndef __koumeChan__KcListCell__
#define __koumeChan__KcListCell__

#include "KCDef.h"
#include "cocos2d.h"
#include "cocos-ext.h"

class KcListCell : public cocos2d::extension::TableViewCell
{
public:
	enum KZORDER {
		KZO_BASE = 0,
		KZO_NAME,
		KZO_COVER
	};
	enum KTAG {
		KTAG_NODE = 0,
		KTAG_BASE,
		KTAG_NAME,
		KTAG_COVER
	};
	
	enum CTAG {
		CTAG_SPRITE = 1,
		CTAG_LABEL,
		CTAG_VAL
	};

	static KcListCell* create(long id,cocos2d::Value name,cocos2d::Value nameImage,cocos2d::Size size);
protected:
	virtual bool init(long id,cocos2d::Value name,cocos2d::Value nameImage,cocos2d::Size size);
	KcListCell();
	virtual ~KcListCell();
	
	virtual const char* getCoverImageName() { return NULL;};
	virtual const char* getCCBFileName() { return BASE_CELL;};
	
	bool createNameLabel();
	bool createCoverSprite();

	CC_SYNTHESIZE(long  ,m_Id,Id);
	CC_SYNTHESIZE(cocos2d::Value ,m_name,Name);
	CC_SYNTHESIZE(cocos2d::Value ,m_nameImage,NameImage);
	CC_SYNTHESIZE(cocos2d::Value ,m_coverImage,CoverImage);
	
	CC_SYNTHESIZE(float ,m_cellWidth,CellWidth);
	CC_SYNTHESIZE(float ,m_cellHeight,CellHeight);
	
	CC_SYNTHESIZE_RETAIN(cocos2d::Sprite*, m_coverSprite, CoverSprite);
	CC_SYNTHESIZE_RETAIN(cocos2d::Sprite*, m_nameSprite, NameSprite);
	CC_SYNTHESIZE_RETAIN(cocos2d::Label*, m_nameLabelTTF,NameLabelTTF);
	CC_SYNTHESIZE_RETAIN(cocos2d::Node*, m_node, Node);
};

#endif /* defined(__koumeChan__KcListCell__) */
