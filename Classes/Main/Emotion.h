//
//  Emotion.h
//  Koumechan
//
//  Created by 上野　彰三 on 2014/06/30.
//
//

#ifndef __Koumechan__Emotion__
#define __Koumechan__Emotion__

#include "cocos2d.h"

class Emotion : public cocos2d::Ref
{
public:
	enum EMOTION_TYPE {
		NUM_0 = 0,
		NUM_1,
		NUM_2,
		NUM_3,
		NUM_4,
		NUM_5,
		NUM_6,
		NUM_7,
		NUM_8,
		NUM_9,
		ENEMY0,
		ENEMY1,
		BOSS0,
		BOSS1,
		TARGET0,
		TARGET1,
		ITEM0,
		ITEM1,
		TREASURE0,
		TREASURE1,
		CHECK0,
		CHECK1,
		START0,
		START1,
		GOAL0,
		GOAL1,
		EXIT0,
		EXIT1,
		PLAYER0,
		PLAYER1,
		UP_RIGHT0,
		DOWN_LEFT0,
		DOWN_RIGHT0,
		TRIANGLE0,
		TRIANGLE1,
		UP0,
		DOWN0,
		LEFT0,
		RIGHT0,
		UP_LEFT0,
		MARU0,
		BATSU0,
		KIRARI0,
		NIYARI0,
		HOSHI0,
	};
	
private:
	static Emotion* m_singleton;
	static const char* m_fileName[];
	static const Emotion::EMOTION_TYPE m_number[];

protected:
	Emotion();
	virtual ~Emotion();
	void init();
	
	
public:
	static Emotion* getInstance();
	std::string getNumberSpriteFrameName(int n);
	cocos2d::Sprite* getNumberSprite(int n);
	cocos2d::Sprite* getSprite(EMOTION_TYPE type);
	std::string getSpriteFrameName(EMOTION_TYPE type);
};

#endif /* defined(__Koumechan__Emotion__) */
