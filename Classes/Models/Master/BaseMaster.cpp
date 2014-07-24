//
//  BaseMaster.cpp
//  koumeChan
//
//  Created by 上野　彰三 on 2014/03/17.
//
//
#include "KCDef.h"
#include "BaseMaster.h"
#include "JsonKeyString.h"
#include "KoumeChan.h"

using namespace cocos2d;
using namespace std;

BaseMaster::BaseMaster()
{
	
}
BaseMaster::~BaseMaster()
{
	
}
bool BaseMaster::initWithJson(Json *data)
{
	if(data == NULL){
		return false;
	}
	masterNo = KoumeChan::getLong(data, JS_NO, -1);
	return true;
}

string BaseMaster::toJsonString()
{
	return jsLong(JS_NO,getMasterNo());
}
