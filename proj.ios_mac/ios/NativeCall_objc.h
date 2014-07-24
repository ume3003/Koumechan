//
//  NativeCall.h
//  KingdomCrash
//
//  Created by 上野　彰三 on 2013/10/04.
//
//
#import "Native.h"
#import <Foundation/Foundation.h>

@interface NativeC : NSObject
{
	NativeCallDelegate *m_delegate;
}

@property(readwrite) NativeCallDelegate *m_delegate;
@property(readwrite)bool isSignIn;
@property(readwrite)bool isSlient;

+ (id)sharedNative;
- (void)addDelegate: (NativeCallDelegate *) pDelegate;
- (void)GPPSignIn;
- (void)GPPSignOut;
- (BOOL)trySlientSignIn;


- (void)TellSignInInfomation:(const char *)ggpuid gmail:(const char *)val url:(const char *)val2 userName:(const char *)val3;

@end
