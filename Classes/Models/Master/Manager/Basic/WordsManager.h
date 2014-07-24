//
//  WordsManager.h
//  Koumechan
//
//  Created by 上野　彰三 on 2014/06/25.
//
//

#ifndef __Koumechan__WordsManager__
#define __Koumechan__WordsManager__

#include "cocos2d.h"
#include "KoumeChan.h"
#include "Words.h"
#include "BaseMasterManager.h"

class WordsManager : public BaseMasterManager
{
protected:
	
public:
	static WordsManager* create(long version);
	virtual std::string getTableName();
	virtual BaseMaster* createMaster(Json* json);
	virtual int getTableNo()		{ return BaseMaster::WORDS_MASTER;};
	Words* getWords(long no);
};




#endif /* defined(__Koumechan__WordsManager__) */
