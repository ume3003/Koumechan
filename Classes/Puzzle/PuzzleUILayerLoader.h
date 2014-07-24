//
//  PuzzleUILayerLoader.h
//  koumeChan
//
//  Created by 上野　彰三 on 2014/03/25.
//
//

#ifndef koumeChan_PuzzleUILayerLoader_h
#define koumeChan_PuzzleUILayerLoader_h



#include "PuzzleUILayer.h"
#include "cocosbuilder/cocosbuilder.h"

class PuzzleUILayerLoader : public cocosbuilder::LayerLoader
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(PuzzleUILayerLoader, loader);
protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(PuzzleUILayer);
	
};


#endif
