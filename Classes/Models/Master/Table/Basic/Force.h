//
//  Force.h
//  koumeChan
//
//  Created by 上野　彰三 on 2014/04/01.
//
//

#ifndef __koumeChan__Force__
#define __koumeChan__Force__

#include "cocos2d.h"
#include "BaseNamedMaster.h"

class Force : public BaseNamedMaster
{
protected:
	Force();
	virtual ~Force();
	CC_SYNTHESIZE(int ,m_nEnemyForceNo,EnemyForceNo)
	virtual bool initWithJson(Json* json);
	
public:
	static Force* createWithJson(Json* json);
	virtual std::string toJsonString();
	virtual void registerToParent() {};
	
};

#endif /* defined(__koumeChan__Force__) */
