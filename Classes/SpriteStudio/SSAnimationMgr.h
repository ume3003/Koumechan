//
//  SSAnimationMgr.h
//  Koumechan
//
//  Created by 上野　彰三 on 2014/07/31.
//
//

#ifndef __Koumechan__SSAnimationMgr__
#define __Koumechan__SSAnimationMgr__

#include "cocos2d.h"
#include "SSAnimationData.h"

class SSAnimationMgr : public cocos2d::Ref
{
public:
	static SSAnimationMgr* getInstance();
	SSAnimationData* loadAnimation(long lNo,int tag,cocos2d::Value& fName,cocos2d::Value& path);
	SSAnimationData* getAnimation(long lNo,int tag);
	void releaseAnimation(long lNo,int tag);
	
protected:
	SSAnimationMgr();
	virtual ~SSAnimationMgr();
	static SSAnimationMgr* m_instance;
	std::map<long,int> m_counter;
	cocos2d::Map<long,SSAnimationData*> m_animations;
};

#endif /* defined(__Koumechan__SSAnimationMgr__) */
