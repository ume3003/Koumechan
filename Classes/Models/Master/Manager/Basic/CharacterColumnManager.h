//
//  CharacterColumnManager.h
//  koumeChan
//
//  Created by 上野　彰三 on 2014/04/01.
//
//

#ifndef __koumeChan__CharacterColumnManager__
#define __koumeChan__CharacterColumnManager__


#include "cocos2d.h"
#include "KoumeChan.h"
#include "CharacterColumn.h"
#include "BaseMasterManager.h"

class CharacterColumnManager : public BaseMasterManager
{
protected:
	
public:
	static CharacterColumnManager* create(long version);
	virtual std::string getTableName();
	virtual BaseMaster* createMaster(Json* json);
	virtual int getTableNo()		{ return BaseMaster::CHARACTER_COL_MASTER;};
	CharacterColumn* getCharacterColumn(long no);
};




#endif /* defined(__koumeChan__CharacterColumnManager__) */
