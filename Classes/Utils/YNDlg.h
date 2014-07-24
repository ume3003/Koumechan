//
//  YNDlg.h
//  kc
//
//  Created by 上野　彰三 on 2014/01/14.
//
//

#ifndef __kc__YNDlg__
#define __kc__YNDlg__

#include "cocos2d.h"
#include "Modal.h"
#include "cocosbuilder/cocosbuilder.h"

class YNDlg : public Modal,public cocosbuilder::CCBSelectorResolver,public cocosbuilder::CCBMemberVariableAssigner
{
public:
	enum kZOrder {
		
	};
	enum DLG_RESULT {
		DLG_OK = 0,
		DLG_CANCEL
	};
	enum kTag {
		kTabBackground = 1,
		kTagTitleLabelTTF,
		kTagOKBtn,
		kTagCancelBtn,
		kTagBodyLabelTTF,
		kTagBase,
	};
	// CCB virtual functions
	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::Ref* pTarget,const char* pSelectorName) {return NULL;}
	virtual cocos2d::extension::Control::Handler onResolveCCBCCControlSelector(cocos2d::Ref* pTarget,const char* pSelectorName);
	virtual bool onAssignCCBMemberVariable(cocos2d::Ref* pTarget, const char* pMemberVariableName, Node* pNode) {return false;};
	
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(YNDlg, create);

	cocos2d::Node*	getBaseNode()		{ return getChildByTag(kTagBase);};
	cocos2d::extension::ControlButton* getOKbtn()	{ return (cocos2d::extension::ControlButton*)getBaseNode()->getChildByTag(kTagOKBtn);};
	cocos2d::extension::ControlButton* getCancel()	{ return (cocos2d::extension::ControlButton*)getBaseNode()->getChildByTag(kTagCancelBtn);};
	cocos2d::Label* getTitleTTF() { return (cocos2d::Label*)getBaseNode()->getChildByTag(kTagTitleLabelTTF);};
	cocos2d::Label* getBodyTTF()  { return (cocos2d::Label*)getBaseNode()->getChildByTag(kTagBodyLabelTTF);};
	
	
	virtual void tappedOK(cocos2d::Ref* pSender,cocos2d::extension::Control::EventType pCControlEvent);
	void tappedCancel(cocos2d::Ref *pSender, cocos2d::extension::Control::EventType pCCControlEvent);
	virtual void onEnter();
	
	
protected:
	YNDlg() {};
	virtual cocos2d::Rect getBaseBoudingBox();
	virtual void onScrollDown() {};
	virtual void onScrollUp() {};
	virtual void afterExit(cocos2d::Node* parent);
	
	CC_SYNTHESIZE(DLG_RESULT, m_result, Result);
};
#endif /* defined(__kc__YNDlg__) */
