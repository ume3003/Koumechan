//
//  CharacterColumnManager.cpp
//  koumeChan
//
//  Created by 上野　彰三 on 2014/04/01.
//
//

#include "CharacterColumnManager.h"
using namespace cocos2d;
using namespace std;

CharacterColumnManager* CharacterColumnManager::create(long version)
{
	CharacterColumnManager* pRet = new CharacterColumnManager();
	if(pRet && pRet->init(version)){
		pRet->autorelease();
	}
	else{
		CC_SAFE_DELETE(pRet);
		pRet = NULL;
	}
	return pRet;
}

string CharacterColumnManager::getTableName()
{
	return string("CharacterColumn");
};

BaseMaster* CharacterColumnManager::createMaster(Json* json)
{
	CharacterColumn* master = CharacterColumn::createWithJson(json);
	log("CharacterColumn %ld %s:%s:%s",master->getMasterNo(),master->getName().asString().c_str(),
		master->getDetail().asString().c_str(),master->getImage().asString().c_str());
	return master;
}

CharacterColumn* CharacterColumnManager::getCharacterColumn(long no)
{
	return (CharacterColumn*)getMaster(no);
}