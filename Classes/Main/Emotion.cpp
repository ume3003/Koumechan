//
//  Emotion.cpp
//  Koumechan
//
//  Created by 上野　彰三 on 2014/06/30.
//
//

#include "Emotion.h"

using namespace cocos2d;
using namespace std;

Emotion* Emotion::m_singleton = NULL;
const Emotion::EMOTION_TYPE Emotion::m_number[] =
{
	NUM_0,
	NUM_1,
	NUM_2,
	NUM_3,
	NUM_4,
	NUM_5,
	NUM_6,
	NUM_7,
	NUM_8,
	NUM_9,
	
};
const char* Emotion::m_fileName[] =
{
	"number0",
	"number1",
	"number2",
	"number3",
	"number4",
	"number5",
	"number6",
	"number7",
	"number8",
	"number9",
	"enemy0",
	"enemy1",
	"boss0",
	"boss1",
	"target0",
	"target1",
	"item0",
	"item1",
	"treasure0",
	"treasure1",
	"check0",
	"check1",
	"start0",
	"start1",
	"goal0",
	"goal1",
	"exit0",
	"exit1",
	"player0",
	"player1",
	"up_right0",
	"down_left0",
	"down_right0",
	"traiangle0",
	"traiangle1",
	"up0",
	"down0",
	"left0",
	"right0",
	"up_left0",
	"maru0",
	"batsu0",
	"kirari0",
	"niyari0",
	"hoshi0"
};

Emotion::Emotion()
{

};

Emotion::~Emotion()
{
}

Emotion* Emotion::getInstance()
{
	if(m_singleton == NULL){
		m_singleton = new Emotion();
		m_singleton->init();
	}
	return m_singleton;
};

void Emotion::init()
{
	SpriteFrameCache* spriteFrameCache = SpriteFrameCache::getInstance();
	spriteFrameCache->addSpriteFramesWithFile("emotion.plist", "emotion.png");

}

Sprite* Emotion::getSprite(EMOTION_TYPE type)
{
	string str = StringUtils::format("%s0.png",m_fileName[type]);
	Sprite* sp = Sprite::createWithSpriteFrameName(str);
	sp->setAnchorPoint(Point(0,0));
	return sp;
};

string Emotion::getSpriteFrameName(Emotion::EMOTION_TYPE type)
{
	string str = StringUtils::format("%s0.png",m_fileName[type]);
	return str;
}

string Emotion::getNumberSpriteFrameName(int n)
{
	if(n >= 0 && n < 9){
		EMOTION_TYPE type = m_number[n];
		string str = StringUtils::format("%s0.png",m_fileName[type]);
		return str;
	}
	return "";
}
Sprite* Emotion::getNumberSprite(int n)
{
	if(n >= 0 && n < 9){
		EMOTION_TYPE type = m_number[n];
		return getSprite(type);
	}
	return NULL;
}
