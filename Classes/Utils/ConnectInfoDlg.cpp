//
//  ConnectInfoDlg.cpp
//  kc
//
//  Created by 上野　彰三 on 2014/01/14.
//
//

#include "ConnectInfoDlg.h"
#include "cocos2d.h"
#include "cocos-ext.h"
#include "KCDef.h"
#include "IConnectInfoDlgReciever.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;


void ConnectInfoDlg::tappedCancel(Ref *pSender, Control::EventType pCCControlEvent)
{
	IConnectInfoDlgReciever* pParent = dynamic_cast<IConnectInfoDlgReciever*>(getParent());
	pParent->onConnectInfoCancel();
	ExitDlg();
	
};

Control::Handler ConnectInfoDlg::onResolveCCBCCControlSelector(Ref* pTarget,const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "tappedCancel"	, ConnectInfoDlg::tappedCancel);
	return NULL;
};

void ConnectInfoDlg::onEnter()
{
	Layer::onEnter();
	Node* bNode = getBaseNode();
	Size size = CCDirector::getInstance()->getWinSize();
	
	Size bnSize = bNode->getContentSize();
	bNode->setScale(size.width / bnSize.width * 0.9f);
	bNode->setPosition(size.width / 2,size.height * 0.9f);
	bNode->setAnchorPoint(Point(0.5f,1.0f));
	
	IConnectInfoDlgReciever* pParent = dynamic_cast<IConnectInfoDlgReciever*>(getParent());
	
	Label* titleLabel = getTitleTTF();
	Label* bodyLabel = getBodyTTF();
	ControlButton* ngBtn = getCancel();
	
	const char* c = pParent->getConnectInfoDlgTitleMessage();
	titleLabel->setString(c);
	bodyLabel->setString(pParent->getConnectInfoDlgBodyMessage());
	const char* strNG = pParent->getConnectInfoCancelButtonText() != NULL ? pParent->getConnectInfoCancelButtonText() :"CANCEL";
	
	ngBtn->setTitleForState(strNG, Control::State::NORMAL);
	ngBtn->setTitleForState(strNG, Control::State::HIGH_LIGHTED);
};

void ConnectInfoDlg::updateTTF()
{
	IConnectInfoDlgReciever* pParent = dynamic_cast<IConnectInfoDlgReciever*>(getParent());
	Label* titleLabel = getTitleTTF();
	Label* bodyLabel = getBodyTTF();
	const char* c = pParent->getConnectInfoDlgTitleMessage();
	titleLabel->setString(c);
	bodyLabel->setString(pParent->getConnectInfoDlgBodyMessage());
	
}