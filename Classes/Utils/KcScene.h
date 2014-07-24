//
//  KcScene.h
//  kc
//
//  Created by 上野　彰三 on 2014/01/14.
//
//

#ifndef __kc__KcScene__
#define __kc__KcScene__

#include "cocos2d.h"
#include "KoumeChan.h"

class KcScene : public cocos2d::Scene
{
	
public:
	enum COMMAND_NO {
		LOGIN = 0,
		MASTER,
		MASTER_VERSION,
		GET_SERVERTIME,
		PUZZLE_INIT,
		PUZZLE_FINISH,
		FRIEND_MATCH_LIST,
		FRIEND_MATCH_CREATE,
		FRIEND_MATCH_GET,
		FRIEND_MATCH_CANCELL,
		FRIEND_MATCH_START,
		FRIEND_MATCH_CHECK,
		COMMAND_MAX
	};
	
	enum IMAGE_NO {
		MY_GOOGLE_PLUS = 0,
		ENEMY_GOOGLE_PLUS,
		TOMOPEN,

	};
	static const char* m_urls[];
	static const char* m_tags[];
	
	// send message to server
	void sendHttpRequest(COMMAND_NO no,const char* sendJson);
	void sendImageHttpRequest(IMAGE_NO no,cocos2d::Value imageUrl);
	
	virtual void onRecieve(COMMAND_NO no,Json* recieveJson) = 0;
	virtual void onImageRecieve(IMAGE_NO no,cocos2d::Image* image) = 0;
	
	const char* getUrl(COMMAND_NO no);
	const char* getCommandTag(COMMAND_NO no);
	COMMAND_NO findCommandNo(const char* strTag);
	bool checkBasicResponse(Json* json);
	
protected:
    void onHttpRequestCompleted(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response);
    void onImageRequestCompleted(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response);
};

#endif /* defined(__kc__KcScene__) */
