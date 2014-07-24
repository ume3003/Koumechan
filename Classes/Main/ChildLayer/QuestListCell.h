//
//  QuestListCell.h
//  koumeChan
//
//  Created by 上野　彰三 on 2014/03/25.
//
//

#ifndef __koumeChan__QuestListCell__
#define __koumeChan__QuestListCell__

#include "cocos2d.h"
#include "KcListCell.h"

class QuestListCell : public KcListCell
{
protected:
	virtual bool init(long id);
	
	CC_SYNTHESIZE(long			,m_id		,Id);

	CC_SYNTHESIZE_RETAIN(cocos2d::Node*		,m_NameNode		,NameNode);
	CC_SYNTHESIZE_RETAIN(cocos2d::Node*		,m_StatusNode	,StatusNode);
	CC_SYNTHESIZE_RETAIN(cocos2d::Node*		,m_DetailNode	,DetailNode);
	
	CC_SYNTHESIZE_RETAIN(cocos2d::Sprite*	,m_NameSprite		,NameSprite);
	CC_SYNTHESIZE_RETAIN(cocos2d::Sprite*	,m_DetailSprite	,DetailSprite);
	CC_SYNTHESIZE_RETAIN(cocos2d::Sprite*	,m_OverlapSprite	,OverlapSprite);

	CC_SYNTHESIZE_RETAIN(cocos2d::Label*	,m_NameTTF		,NameTTF);
	CC_SYNTHESIZE_RETAIN(cocos2d::Label*	,m_DetailTTF	,DetailTTF);
	CC_SYNTHESIZE_RETAIN(cocos2d::Label*	,m_OverlapTTF	,OverlapTTF);
	
public:
	static QuestListCell* create(long id,cocos2d::Value name,cocos2d::Value detail,cocos2d::Value status);
	

};

#endif /* defined(__koumeChan__QuestListCell__) */
