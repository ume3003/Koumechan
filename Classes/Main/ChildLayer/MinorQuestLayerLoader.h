//
//  MinorQuestLayerLoader.h
//  koumeChan
//
//  Created by 上野　彰三 on 2014/03/19.
//
//

#ifndef koumeChan_MinorQuestLayerLoader_h
#define koumeChan_MinorQuestLayerLoader_h

#include "MinorQuestLayer.h"
#include "cocosbuilder/cocosbuilder.h"

class MinorQuestLayerLoader : public cocosbuilder::LayerLoader
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(MinorQuestLayerLoader, loader);
protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(MinorQuestLayer);
	
};



#endif
