//
//  NativeCall.cpp
//  Koumechan
//
//  Created by 上野　彰三 on 2014/04/23.
//
//
#include "Native.h"
#include "NativeCalljni.h"

static NativeCallDelegate* m_delegate = NULL;

void NativeCall::GPPSSignIn()
{
	GPPSignInJNI();
}

void NativeCall::GPPSSingOut()
{
	GPPSignOutJNI();
}

void NativeCall::addDelegate(NativeCallDelegate* pDelegate)
{
	m_delegate = pDelegate;
}

bool NativeCall::isSignIn()
{
	return isSignInJNI();
}

bool NativeCall::trySilentSignIn()
{
	return trySilentSignInJNI();
}

bool NativeCall::onResult(int resultType,const char* ggpid,const char* gmail,const char* gurl,const char* gname)
{
	if(m_delegate){
		return m_delegate->onResult(resultType,ggpid,gmail,gurl,gname);
	}
	return false;
}