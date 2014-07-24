//
//  IConnectInfoDlgReciever.h
//  kc
//
//  Created by 上野　彰三 on 2014/01/14.
//
//

#ifndef kc_IConnectInfoDlgReciever_h
#define kc_IConnectInfoDlgReciever_h

class IConnectInfoDlgReciever
{
public:
	virtual ~IConnectInfoDlgReciever() {};
	virtual const char* getConnectInfoDlgTitleMessage() = 0;
	virtual const char* getConnectInfoDlgBodyMessage() = 0;
	virtual const char* getConnectInfoCancelButtonText() = 0;
	
	virtual void onConnectInfoCancel() = 0;
};

#endif
