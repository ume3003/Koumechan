//
//  FriendMatchLayerLoader.h
//  Koumechan
//
//  Created by 上野　彰三 on 2014/07/08.
//
//

#ifndef Koumechan_FriendMatchLayerLoader_h
#define Koumechan_FriendMatchLayerLoader_h

#include "FriendMatchLayer.h"
#include "cocosbuilder/cocosbuilder.h"

class FriendMatchLayerLoader : public cocosbuilder::LayerLoader
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(FriendMatchLayerLoader, loader);
protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(FriendMatchLayer);
	
};





#endif
