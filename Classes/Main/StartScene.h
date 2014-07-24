//
//  StartScene.h
//  koumeChan
//
//  Created by 上野　彰三 on 2014/03/11.
//
//

#ifndef __koumeChan__StartScene__
#define __koumeChan__StartScene__

#include "Native.h"
#include "cocos2d.h"
#include "KoumeChan.h"
#include "KCID.h"
#include "KcScene.h"
#include "StartScene.h"
#include "IConnectInfoDlgReciever.h"

class StartScene : public KcScene,public IConnectInfoDlgReciever,public NativeCallDelegate
{
	
public:
	enum STARTSTATE {
		NOTHING = 0,
		SIGNINING,
		SIGNOUTING,
		LOGINING,
		LOADVER,
		LOADMASTER,
		LOADING,
	};
	static StartScene* create();
	virtual bool init();
	
	void login();
	void signin();
	
protected:
	StartScene();
	virtual ~StartScene();
	
	virtual bool onResult(int resultType,const char* gguid,const char* gmail,const char* gurl,const char* username);
	virtual void onRecieve(KcScene::COMMAND_NO no,Json* recieveJson);
	virtual void onImageRecieve(IMAGE_NO no,cocos2d::Image* image) {};
	
	virtual const char* getConnectInfoDlgTitleMessage();
	virtual const char* getConnectInfoDlgBodyMessage();
	virtual const char* getConnectInfoCancelButtonText();
	virtual void onConnectInfoCancel();
	
	bool loadedMasterVersion(Json* json);
	bool loadedMasterData(Json* json);
	bool loadedLogin(Json* json);
	
	void loadMaster();

	CC_SYNTHESIZE(std::string ,m_loadingString,LoadingString);

	CC_SYNTHESIZE_RETAIN(Node*, m_layer, Layer);
	CC_SYNTHESIZE(STARTSTATE, m_state, StartState);
	CC_SYNTHESIZE(int ,m_currentLoading,CurrentLoading);
};


#endif /* defined(__koumeChan__StartScene__) */
