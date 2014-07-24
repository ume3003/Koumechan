//
//  KcLayer.cpp
//  kc
//
//  Created by 上野　彰三 on 2014/01/17.
//
//

#include "KCDef.h"
#include "cocos2d.h"
#include "KcLayer.h"
#include "KoumeChan.h"
using namespace cocos2d;
using namespace std;

KcLayer::KcLayer() : m_listener(NULL)
{
    
};

KcLayer::~KcLayer()
{
    CC_SAFE_RELEASE(m_listener);
};

bool KcLayer::init()
{
    if(Layer::init()){
        // Register Touch Event
		auto listener = EventListenerTouchOneByOne::create();
		listener->setSwallowTouches(false);
        
		listener->onTouchBegan = CC_CALLBACK_2(KcLayer::onKCTouchBegan, this);
		listener->onTouchMoved = CC_CALLBACK_2(KcLayer::onKCTouchMoved, this);
		listener->onTouchEnded = CC_CALLBACK_2(KcLayer::onKCTouchEnded, this);
		listener->onTouchCancelled = CC_CALLBACK_2(KcLayer::onKCTouchCancelled, this);
		getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
		setListener(listener);
        
        return true;
    }
    return false;
};

void KcLayer::onExit()
{
	if(getListener() != NULL){
		getEventDispatcher()->removeEventListener(getListener());
		setListener(NULL);
	}
    Layer::onExit();
};

void KcLayer::initControl(Node* pNode,bool bTop,bool bVisible)
{
	if(pNode != NULL){
		if(bTop){
			pNode->setPositionY(pNode->getPositionY() - KoumeChan::getInstance()->getDiffHeight());
		}
		else{
			pNode->setPositionY(pNode->getPositionY() + KoumeChan::getInstance()->getDiffHeight());
		}
		pNode->setVisible(bVisible);
		
	}
};


void KcLayer::updateLabelBMFont(Node* parent,int tag,const char* val)
{
	Label* lFont = (Label*)parent->getChildByTag(tag);
	if(lFont != NULL){
		lFont->setString(val);
	}
	
};