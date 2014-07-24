//
//  MajorQuestLayerLoader.h
//  koumeChan
//
//  Created by 上野　彰三 on 2014/03/19.
//
//

#ifndef koumeChan_MajorQuestLayerLoader_h
#define koumeChan_MajorQuestLayerLoader_h


#include "MajorQuestLayer.h"
#include "cocosbuilder/cocosbuilder.h"

class MajorQuestLayerLoader : public cocosbuilder::LayerLoader
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(MajorQuestLayerLoader, loader);
protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(MajorQuestLayer);
	
};



#endif
