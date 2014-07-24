//
//  ConnectInfoDlgLoader.h
//  kc
//
//  Created by 上野　彰三 on 2014/01/14.
//
//

#ifndef kc_ConnectInfoDlgLoader_h
#define kc_ConnectInfoDlgLoader_h

#include "ConnectInfoDlg.h"
#include "cocosbuilder/cocosbuilder.h"

class ConnectInfoDlgLoader : public cocosbuilder::LayerLoader
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(ConnectInfoDlgLoader, loader);
protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(ConnectInfoDlg);
};


#endif
