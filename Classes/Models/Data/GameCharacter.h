//
//  GameCharacter.h
//  koumeChan
//
//  Created by 上野　彰三 on 2014/03/17.
//
//

#ifndef __koumeChan__GameCharacter__
#define __koumeChan__GameCharacter__

#include "cocos2d.h"
#include "spine/json.h"

class GameCharacter : public cocos2d::Ref
{
protected:
	GameCharacter();
	virtual ~GameCharacter() {};
	
	CC_SYNTHESIZE(long, m_id, Id);	// not use
	CC_SYNTHESIZE(long, m_stamina, Stamina);
	CC_SYNTHESIZE(long, m_maxStamina, MaxStamina);
	CC_SYNTHESIZE(long, m_money, Money);
	CC_SYNTHESIZE(long, m_gold,Gold);
	CC_SYNTHESIZE(long, m_exp, Exp);
	CC_SYNTHESIZE(long, m_hp,HP);
	CC_SYNTHESIZE(long, m_level,Level);
	CC_SYNTHESIZE(long long, m_lastCommand, LastCommand);
	
public:
	static GameCharacter* createWithJson(Json* json);
	virtual bool loadFromSrv(Json* json);
};

#endif /* defined(__koumeChan__GameCharacter__) */
