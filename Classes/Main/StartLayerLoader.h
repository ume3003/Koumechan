//
//  StartLayerLoader.h
//  koumeChan
//
//  Created by 上野　彰三 on 2014/03/11.
//
//

#ifndef koumeChan_StartLayerLoader_h
#define koumeChan_StartLayerLoader_h

#include "StartLayer.h"
#include "cocosbuilder/cocosbuilder.h"

class StartLayerLoader : public cocosbuilder::LayerLoader
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(StartLayerLoader, loader);
protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(StartLayer);
	
};

#endif
