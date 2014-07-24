//
//  NativeCall.h
//  Koumechan
//
//  Created by 上野　彰三 on 2014/04/23.
//
//

#ifndef Koumechan_NativeCall_h
#define Koumechan_NativeCall_h


#include <cocos2d.h>


class NativeCallDelegate {
public:
	virtual bool onResult(int resultType,const char* ggpid,const char* gmail,const char* gurl,const char* gname)	{return true;}
};

class NativeCall
{
public:
	static void addDelegate(NativeCallDelegate* delegate);
	static void GPPSSignIn();
	static void GPPSSingOut();
	static bool isSignIn();
	static bool trySilentSignIn();
	static bool onResult(int resultType,const char* ggpid,const char* gmail,const char* gurl,const char* gname);
	
};



#endif
