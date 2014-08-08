//
//  SSAnimationData.h
//  sspTest
//
//  Created by 上野　彰三 on 2014/07/29.
//
//

#ifndef __sspTest__SSAnimationData__
#define __sspTest__SSAnimationData__

#include "cocos2d.h"
#include "SSPlayer.h"
#include "SSPlayerData.h"

class SSAnimationData : public cocos2d::Ref
{
protected:
	SSAnimationData();
	virtual ~SSAnimationData();
	virtual bool initWithFilePath(cocos2d::Value fName,cocos2d::Value path);
	
public:
	static SSAnimationData* createWithFilePath(cocos2d::Value fName,cocos2d::Value path);
	
	void destroy();
	unsigned char* fileData;
	SSData*		m_ssdata;
	
	SSData* getSSData()		{ return m_ssdata;};
	
	CC_SYNTHESIZE_RETAIN(SSImageList*	,m_imageList,ImageList);
	
	/* 指定のインデックスのテクスチャを取る　*/
	cocos2d::Texture2D* getTexture(size_t index);
	
};
#endif /* defined(__sspTest__SSAnimationData__) */
