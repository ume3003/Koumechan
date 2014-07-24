//
//  Native.h
//  KingdomCrash
//
//  Created by 上野　彰三 on 2013/10/04.
//
//

#ifndef KingdomCrash_Native_h
#define KingdomCrash_Native_h

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
	
};

#endif
