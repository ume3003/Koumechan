//
//  KcScene.cpp
//  kc
//
//  Created by 上野　彰三 on 2014/01/14.
//
//
#include "KcScene.h"
#include "KoumeChan.h"
#include "KCDef.h"
#include "cocos2d.h"
#include "JsonKeyString.h"

using namespace cocos2d;
using namespace cocos2d::network;
using namespace std;

const char* KcScene::m_urls[] =
{
	"/login",
	"/master",
	"/masterVersion",
	"/checkTime",
	"/puzzle/init",
	"/puzzle/finish",
	"/compe/friend/list",
	"/compe/friend/set",
	"/compe/friend/get",
	"/compe/friend/cancel",
	"/compe/friend/start",
	"/compe/friend/check"
};
const char* KcScene::m_tags[] =
{
	"LOGIN",
	"MASTER",
	"MASTERVERSION",
	"GETSERVERTIME",
	"PUZZLEINIT",
	"PUZZLEFINISH",
	"FRIEND_MATCH_LIST",
	"FRIEND_MATCH_CREATE",
	"FRIEND_MATCH_GET",
	"FRIEND_MATCH_CANCELL",
	"FRIEND_MATCH_START",
	"FRIEND_MATCH_CHECK"
};
const char* KcScene::getUrl(KcScene::COMMAND_NO no)
{
	assert(no >= 0 && no < COMMAND_MAX);
	if(0 <= no && no < COMMAND_MAX){
		return m_urls[no];
	}
	return NULL;
};
const char* KcScene::getCommandTag(KcScene::COMMAND_NO no)
{
	assert(no >= 0 && no < COMMAND_MAX);
	if(0 <= no && no < COMMAND_MAX){
		return m_tags[no];
	}
	return NULL;
};
KcScene::COMMAND_NO KcScene::findCommandNo(const char *strTag)
{
	for(int i = 0 ;i < COMMAND_MAX;i++){
		if(strcmp(strTag, getCommandTag((COMMAND_NO)i)) == 0){
			return (COMMAND_NO)i;
		}
	}
	return COMMAND_MAX;
};
void KcScene::sendImageHttpRequest(IMAGE_NO no,const Value imageUrl)
{
	
		log("getimage %s",imageUrl.asString().c_str());
		HttpRequest* request = new HttpRequest();
		request->setUrl(imageUrl.asString().c_str());
		request->setTag(StringUtils::format("%d",no).c_str());
		request->setRequestType(HttpRequest::Type::GET);
		request->setResponseCallback(CC_CALLBACK_2(KcScene::onImageRequestCompleted,this));
		HttpClient::getInstance()->send(request);
		request->release();
}

void KcScene::sendHttpRequest(COMMAND_NO no,const char* sendJson)
{
	if(sendJson && getCommandTag(no) && getUrl(no)){
		KoumeChan::getInstance()->send(getCommandTag(no),sendJson,getUrl(no),this,CC_CALLBACK_2(KcScene::onHttpRequestCompleted,this));
	}
}

void KcScene::onImageRequestCompleted(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response)
{
    if (!response)
    {
        log("no response");
        return;
    }
    if (!response->isSucceed())
    {
        log("response failed");
        return;
    }
	
    std::vector<char>* buffer = response->getResponseData();
	
	const char* tag = KoumeChan::getInstance()->getTag(response);
	IMAGE_NO no = (IMAGE_NO)atoi(tag);
    Image* image = new Image();
    if(image->initWithImageData(reinterpret_cast<unsigned char*>(&(buffer->front())), buffer->size())){
		onImageRecieve(no, image);
	}
	else{
		onImageRecieve(no, NULL);
	}
	
}

void KcScene::onHttpRequestCompleted(HttpClient *sender, HttpResponse *response)
{
	const char* tag = KoumeChan::getInstance()->getTag(response);
	if(tag != NULL){
		COMMAND_NO no = findCommandNo(tag);
		if(no != COMMAND_MAX){
			Json* json = KoumeChan::getInstance()->responseToJson(sender, response);
			if(json != NULL){
				onRecieve(no,json);
			}
			else{
				log("response error: %d %s",no,tag);
			}
			if(json != NULL){
				Json_dispose(json);
			}
		}
	}
	
}

bool KcScene::checkBasicResponse(Json *json)
{
	if(json == NULL){
		log("json is null ");
		return false;
	}
	std::string err = Json_getString(json, JS_ERROR, "");
	if(err.length() > 0){
		log("error %s",err.c_str());
		return false;
	}
	std::string sessionid = Json_getString(json,JS_SESSION_ID,"");
	if(sessionid.length() == 0){
		log("error sessionId is null");
		return false;
	}
	return true;
}