//
//  MainUILayerLoader.h
//  koumeChan
//
//  Created by 上野　彰三 on 2014/03/12.
//
//

#ifndef koumeChan_MainUILayerLoader_h
#define koumeChan_MainUILayerLoader_h

#include "MainUILayer.h"
#include "cocosbuilder/cocosbuilder.h"

class MainUILayerLoader : public cocosbuilder::LayerLoader
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(MainUILayerLoader, loader);
protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(MainUILayer);
	
};

#endif
