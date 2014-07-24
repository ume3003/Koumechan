//
//  NativeCalljni.h
//  Koumechan
//
//  Created by 上野　彰三 on 2014/04/23.
//
//

#ifndef __Koumechan__NativeCalljni__
#define __Koumechan__NativeCalljni__


extern "C"
{
	extern void GPPSignInJNI();
	extern void GPPSignOutJNI();
	extern void addDelegateJNI();
	extern bool isSignInJNI();
	extern bool trySilentSignInJNI();
}


#endif /* defined(__Koumechan__NativeCalljni__) */
