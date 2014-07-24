//
//  Modal.cpp
//  kc
//
//  Created by 上野　彰三 on 2014/01/14.
//
//

#include "KCDef.h"
#include "Modal.h"
using namespace cocos2d;

Modal::Modal():m_listener(NULL)
{
	
};

Modal::~Modal()
{
}
bool Modal::init()
{
	if(Layer::init()){
		auto listener = EventListenerTouchOneByOne::create();
		listener->setSwallowTouches(false);

		listener->onTouchBegan = CC_CALLBACK_2(Modal::onKCTouchBegan, this);
		listener->onTouchMoved = CC_CALLBACK_2(Modal::onKCTouchMoved, this);
		listener->onTouchEnded = CC_CALLBACK_2(Modal::onKCTouchEnded, this);
		listener->onTouchCancelled = CC_CALLBACK_2(Modal::onKCTouchCancelled, this);
		getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
		setListener(listener);
		return true;
	}
	return false;
};
void Modal::ExitDlg()
{
	Point endPoint = Point(getParent()->getContentSize().width + getContentSize().width / 2,getParent()->getContentSize().height / 2 - getContentSize().height /2 );
	CallFuncN* cleanup = CallFuncN::create(CC_CALLBACK_1(Modal::removeOwn, this));
	MoveTo* move = MoveTo::create(0.2f,endPoint);
	Sequence* seq = Sequence::create(move,cleanup,NULL);
	runAction(seq);
};

void Modal::removeOwn(Node* pBlock)
{
	Node* parent = getParent();
	pBlock->removeFromParentAndCleanup(true);
	afterExit(parent);
};

void Modal::onExit()
{
	if(getListener() != NULL){
		getEventDispatcher()->removeEventListener(getListener());
		setListener(NULL);
	}
	Layer::onExit();
};

bool Modal::onKCTouchBegan(cocos2d::Touch* pTouch,cocos2d::Event* pEvent)
{
	pEvent->stopPropagation();
	return true;
};
