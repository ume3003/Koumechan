//
//  IYNDlgReciever.h
//  kc
//
//  Created by 上野　彰三 on 2014/01/14.
//
//

#ifndef kc_IYNDlgReciever_h
#define kc_IYNDlgReciever_h

class IYNDlgReciever
{
public:
	virtual ~IYNDlgReciever() {};
	virtual const char* getDlgTitleMessage() = 0;
	virtual const char* getDlgBodyMessage() = 0;
	virtual const char* getOkButtonText() = 0;
	virtual const char* getCancelButtonText() = 0;
	
	virtual void onOk() = 0;
	virtual void onCancel() = 0;
};

#endif
