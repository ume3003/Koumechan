//
//  KcSprite.cpp
//  koumeChan
//
//  Created by 上野　彰三 on 2014/04/02.
//
//

#include "KcSprite.h"
#include "KCDef.h"
#include "cocos2d.h"
#include "KoumeChan.h"
using namespace cocos2d;
using namespace std;

KcSprite::KcSprite() : m_listener(NULL)
{
    
};

KcSprite::~KcSprite()
{
    CC_SAFE_RELEASE(m_listener);
};
void KcSprite::registerTouchEvent()
{
	// Register Touch Event
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(false);
	
	listener->onTouchBegan = CC_CALLBACK_2(KcSprite::onKCTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(KcSprite::onKCTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(KcSprite::onKCTouchEnded, this);
	listener->onTouchCancelled = CC_CALLBACK_2(KcSprite::onKCTouchCancelled, this);
	getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	setListener(listener);
	
}
bool KcSprite::init()
{
    if(SSPlayer::init()){
		registerTouchEvent();
        return true;
    }
    return false;
};

void KcSprite::onExit()
{
	if(getListener() != NULL){
		getEventDispatcher()->removeEventListener(getListener());
		setListener(NULL);
	}
    SSPlayer::onExit();
};
