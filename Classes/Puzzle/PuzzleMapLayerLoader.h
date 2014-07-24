//
//  PuzzleMapLayerLoader.h
//  koumeChan
//
//  Created by 上野　彰三 on 2014/03/25.
//
//

#ifndef koumeChan_PuzzleMapLayerLoader_h
#define koumeChan_PuzzleMapLayerLoader_h



#include "PuzzleMapLayer.h"
#include "cocosbuilder/cocosbuilder.h"

class PuzzleMapLayerLoader : public cocosbuilder::LayerLoader
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(PuzzleMapLayerLoader, loader);
protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(PuzzleMapLayer);
	
};



#endif
