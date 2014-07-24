//
//  YNDlgLoader.h
//  kc
//
//  Created by 上野　彰三 on 2014/01/14.
//
//

#ifndef kc_YNDlgLoader_h
#define kc_YNDlgLoader_h


#include "YNDlg.h"
#include "cocosbuilder/cocosbuilder.h"

class YNDlgLoader : public cocosbuilder::LayerLoader
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(YNDlgLoader, loader);
protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(YNDlg);
};

#endif
