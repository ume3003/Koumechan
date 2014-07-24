//
//  CharacterColumn.h
//  koumeChan
//
//  Created by 上野　彰三 on 2014/04/01.
//
//

#ifndef __koumeChan__CharacterColumn__
#define __koumeChan__CharacterColumn__


#include "cocos2d.h"
#include "BaseNamedMaster.h"

class CharacterColumn : public BaseNamedMaster
{
protected:
	CharacterColumn();
	virtual ~CharacterColumn();
	
	
public:
	static CharacterColumn* createWithJson(Json* json);
	virtual std::string toJsonString();
	virtual void registerToParent() {};
	
};

#endif /* defined(__koumeChan__CharacterColumn__) */
