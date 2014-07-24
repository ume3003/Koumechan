//
//  WordsManager.cpp
//  Koumechan
//
//  Created by 上野　彰三 on 2014/06/25.
//
//

#include "WordsManager.h"

using namespace cocos2d;
using namespace std;

WordsManager* WordsManager::create(long version)
{
	WordsManager* pRet = new WordsManager();
	if(pRet && pRet->init(version)){
		pRet->autorelease();
	}
	else{
		CC_SAFE_DELETE(pRet);
		pRet = NULL;
	}
	return pRet;
}

string WordsManager::getTableName()
{
	return string("Words");
};

BaseMaster* WordsManager::createMaster(Json* json)
{
	Words* master = Words::createWithJson(json);
	log("Words %ld %s:%s:%s",master->getMasterNo(),master->getName().asString().c_str(),
		master->getDetail().asString().c_str(),master->getImage().asString().c_str());
	return master;
}

Words* WordsManager::getWords(long no)
{
	return (Words*)getMaster(no);
}