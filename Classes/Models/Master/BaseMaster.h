//
//  BaseMaster.h
//  koumeChan
//
//  Created by 上野　彰三 on 2014/03/17.
//
//

#ifndef __koumeChan__BaseMaster__
#define __koumeChan__BaseMaster__

#include "cocos2d.h"
#include "spine/json.h"

class BaseMaster : public cocos2d::Ref
{
public:
	enum MASTERNO {
		DIRECT_MASTER = 0,				// 方面マスタ
		MAJOR_QUEST_MASTER,				// メジャークエ
		MINOR_QUEST_MASTER,				// マイナークエ
		MAP_MASTER,						// マップマスタ
		UNIT_MASTER,					// ユニットマスタ
		SPECIAL_ITEM_MASTER,			// 特殊アイテムマスタ
		SCENARIO_MASTER,					// 対戦シナリオ
		COMPETITION_RULE_MASTER,		// 対戦ルール
		
		CONDITION_KIND_MASTER,
		CHARACTER_COL_MASTER,
		RANK_MASTER,
		SKILL_MASTER,
		
		QUEST_UNIT_MASTER,				// クエスト使用ユニット
		QUEST_APPEARANCE_MASTER,			// クエストクリア条件
		QUEST_CLEAR_MASTER,
		QUEST_REWARD_MASTER,
		
		SCENARIO_RULE_MASTER,			// 対戦シナリオルール
		SCENARIO_UNIT_MASTER,			// 対戦使用ユニット
		
		UNIT_SKILL_MASTER,
		FORCE_MASTER,
		NPC_MASTER,
		WORDS_MASTER,
		NPC_WORDS_MASTER,
		BASE_DAMAGE_MASTER,
		MASTER_MAX
	};
protected:
	BaseMaster();
	virtual ~BaseMaster();
	virtual bool initWithJson(Json* data);
	
	CC_SYNTHESIZE(long, masterNo, MasterNo);
public:
	virtual std::string toJsonString();
	virtual void registerToParent() = 0;
	
	virtual void clearChild(MASTERNO masterNo) {};
};

#endif /* defined(__koumeChan__BaseMaster__) */
