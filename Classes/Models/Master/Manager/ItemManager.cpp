//
//  ItemManager.cpp
//  koumeChan
//
//  Created by 上野　彰三 on 2014/04/01.
//
//

#include "ItemManager.h"
using namespace cocos2d;
using namespace std;

ItemManager* ItemManager::create(long version)
{
	ItemManager* pRet = new ItemManager();
	if(pRet && pRet->init(version)){
		pRet->autorelease();
	}
	else{
		CC_SAFE_DELETE(pRet);
		pRet = NULL;
	}
	return pRet;
}

string ItemManager::getTableName()
{
	return string("Item");
};

BaseMaster* ItemManager::createMaster(Json* json)
{
	Item* master = Item::createWithJson(json);
//	log("Item %ld %s:%s:%s",master->getMasterNo(),master->getName().asString().c_str(),
//		master->getDetail().asString().c_str(),master->getImage().asString().c_str());
	return master;
}

Item* ItemManager::getItem(long no)
{
	return (Item*)getMaster(no);
}