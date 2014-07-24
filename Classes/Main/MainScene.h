//
//  MainScene.h
//  koumeChan
//
//  Created by 上野　彰三 on 2014/03/12.
//
//

#ifndef __koumeChan__MainScene__
#define __koumeChan__MainScene__

#include "cocos2d.h"
#include "KoumeChan.h"
#include "KcScene.h"
#include "IConnectInfoDlgReciever.h"

class MainScene : public KcScene,public IConnectInfoDlgReciever
{
	
public:
	enum LAYER_TAG {
		LTAG_MAIN = 1,
		LTAG_MAJOR,
		LTAG_MINOR,
		LTAG_FRIEND_MATCH
	};
	enum LAYER_ZORDER {
		LZ_CHILD = 98,
		LZ_MAIN = 99,
	};
	static MainScene* create();
	virtual bool init();
	
	void getServerTime();
	void showMajorQuestLayer(bool bShow = true);
	void showMinorQuestLayer(bool bShow = true);
	void showFriendMatchLayer();

	
	CC_SYNTHESIZE(KcScene::COMMAND_NO, m_commandNo, CommandNo);
	CC_SYNTHESIZE(bool,m_waiting,Waiting);
	
protected:
	MainScene();
	virtual ~MainScene();
	
	virtual void onRecieve(KcScene::COMMAND_NO no,Json* recieveJson);
	virtual void onImageRecieve(IMAGE_NO no,cocos2d::Image* image) {};
	
	virtual const char* getConnectInfoDlgTitleMessage();
	virtual const char* getConnectInfoDlgBodyMessage();
	virtual const char* getConnectInfoCancelButtonText();
	virtual void onConnectInfoCancel();
	
	bool gotServerTime(Json* json);
	
	
	
	CC_SYNTHESIZE_RETAIN(cocos2d::Node*, m_Node, Node);
	

};

#endif /* defined(__koumeChan__MainScene__) */
