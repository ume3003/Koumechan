//
//  NativeCall.mm
//  KingdomCrash
//
//  Created by 上野　彰三 on 2013/10/04.
//
//

#include "Native.h"
#include "NativeCall_objc.h"

void NativeCall::GPPSSignIn()
{
	[[NativeC sharedNative] GPPSignIn];
}

void NativeCall::GPPSSingOut()
{
	[[NativeC sharedNative] GPPSignOut];
}

void NativeCall::addDelegate(NativeCallDelegate* pDelegate)
{
	[[NativeC sharedNative] addDelegate:pDelegate];
}

bool NativeCall::isSignIn()
{
	return [[NativeC sharedNative] isSignIn];
}

bool NativeCall::trySilentSignIn()
{
	return [[NativeC sharedNative] trySlientSignIn];
}

