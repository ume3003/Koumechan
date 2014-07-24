//
//  BaseDamage.h
//  Koumechan
//
//  Created by 上野　彰三 on 2014/06/26.
//
//

#ifndef __Koumechan__BaseDamage__
#define __Koumechan__BaseDamage__

#include "cocos2d.h"
#include "BaseMaster.h"

class BaseDamage : public BaseMaster
{
protected:
	BaseDamage();
	virtual ~BaseDamage();
	CC_SYNTHESIZE(cocos2d::Value		,m_description,Description);
	CC_SYNTHESIZE(int, m_ownHitpoint	, OwnHitPoint);
	CC_SYNTHESIZE(int, m_ownPower		, OwnPower);
	CC_SYNTHESIZE(int, m_EnemyHitpoint	, EnemyHitPoint);
	CC_SYNTHESIZE(int, m_EnemyPower		, EnemyPower);
	virtual bool initWithJson(Json* json);
	
public:
	enum BD_TYPE {
		THREE_OWN = 0,
		FOUR_OWN,
		BORN_OWN,
		FIVE_OWN,
		THREE_NEUTRAL,
		FOUR_NEUTRAL = 5,
		FIVE_NEUTRAL,
		BORN_NEUTRAL,
		THREE_ENEMY,
		FOUR_ENEMY,
		BORN_ENEMY = 10,
		FIVE_ENEMY,
		RAIL_OWN,
		RAIL_NEUTRAL,
		RAIL_ENEMY,
		ELITE_MAGIC = 15,
		ELITE_BUFFER,
		ELITE_TANK,
		ELITE_DPS,
		ELITE_HEALER,
		NONE = 99

	};
	
	static BaseDamage* createWithJson(Json* json);
	virtual std::string toJsonString();
	virtual void registerToParent() {};
	
};

#endif /* defined(__Koumechan__BaseDamage__) */
