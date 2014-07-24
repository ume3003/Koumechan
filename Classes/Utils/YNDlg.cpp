//
//  YNDlg.cpp
//  kc
//
//  Created by 上野　彰三 on 2014/01/14.
//
//

#include "YNDlg.h"
#include "cocos2d.h"
#include "cocos-ext.h"
#include "KCDef.h"
#include "IYNDlgReciever.h"
using namespace cocos2d;
using namespace cocos2d::extension;
using namespace std;

void YNDlg::tappedOK(Ref* pSender,Control::EventType pCControlEvent)
{
	setResult(DLG_OK);
	ExitDlg();
};

void YNDlg::tappedCancel(Ref *pSender, Control::EventType pCCControlEvent)
{
	setResult(DLG_CANCEL);
	ExitDlg();
	
};

void YNDlg::afterExit(Node* parent)
{
	IYNDlgReciever* pParent = dynamic_cast<IYNDlgReciever*>(parent);
	if(getResult() == DLG_OK){
		pParent->onOk();
	}
	else{
		pParent->onCancel();
	}
}
Control::Handler YNDlg::onResolveCCBCCControlSelector(Ref* pTarget,const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "tappedCancel"	, YNDlg::tappedCancel);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "tappedOK"		, YNDlg::tappedOK);
	return NULL;
};
cocos2d::Rect YNDlg::getBaseBoudingBox()
{
	Node* bNode = getBaseNode();
	Rect rc = bNode->getBoundingBox();
	return rc;
};

void YNDlg::onEnter()
{
	Layer::onEnter();
	setResult(DLG_CANCEL);
	Node* bNode = getBaseNode();
	Size size = CCDirector::getInstance()->getWinSize();
	
	Size bnSize = bNode->getContentSize();
	bNode->setScale(size.width / bnSize.width * 0.9f);
	bNode->setPosition(size.width / 2,size.height * 0.9f);
	bNode->setAnchorPoint(Point(0.5f,1.0f));
	
	IYNDlgReciever* pParent = dynamic_cast<IYNDlgReciever*>(getParent());
	
	Label* titleLabel = getTitleTTF();
	Label* bodyLabel = getBodyTTF();
	ControlButton* okBtn = getOKbtn();
	ControlButton* ngBtn = getCancel();

	const char* c = pParent->getDlgTitleMessage();
	titleLabel->setString(c);
	bodyLabel->setString(pParent->getDlgBodyMessage());
	const char* strOK = pParent->getOkButtonText() != NULL ? pParent->getOkButtonText() :"OK";
	const char* strNG = pParent->getCancelButtonText() != NULL ? pParent->getCancelButtonText() :"CANCEL";
	
	okBtn->setTitleForState(strOK, Control::State::NORMAL);
	okBtn->setTitleForState(strOK, Control::State::HIGH_LIGHTED);
	ngBtn->setTitleForState(strNG, Control::State::NORMAL);
	ngBtn->setTitleForState(strNG, Control::State::HIGH_LIGHTED);
};