//
//  SSAnimationData.cpp
//  sspTest
//
//  Created by 上野　彰三 on 2014/07/29.
//
//

#include "SSAnimationData.h"
#include "KCDef.h"

using namespace cocos2d;
using namespace std;

SSAnimationData::SSAnimationData() : m_ssdata(NULL),m_imageList(NULL),fileData(NULL)
{
	
};

SSAnimationData::~SSAnimationData()
{
	destroy();
};

void SSAnimationData::destroy()
{
	if(fileData){
		delete[] fileData;
	}
};


bool SSAnimationData::initWithFilePath(Value fName,Value path)
{
	fileData = SSPlayerHelper::loadFile(V2C(fName),V2C(path));
	if(fileData){
		m_ssdata = reinterpret_cast<SSData*>(fileData);
		setImageList(SSImageList::create(m_ssdata,V2C(path)));
		if(m_imageList){
			return true;
		}
	}
	return false;
}

SSAnimationData* SSAnimationData::createWithFilePath(Value fName,Value path)
{
	SSAnimationData* pRet = new SSAnimationData();
	if(pRet && pRet->initWithFilePath(fName,path)){
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
};

Texture2D* SSAnimationData::getTexture(size_t index)
{
	if(getImageList()){
		return getImageList()->getTexture(index);
	}
	return NULL;
}