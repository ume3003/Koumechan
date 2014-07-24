//
//  NativeCall.m
//  KingdomCrash
//
//  Created by 上野　彰三 on 2013/10/04.
//
//
#import <Security/Security.h>
#import "NativeCall_objc.h"
#import <GooglePlus/GooglePlus.h>
#import <PlayGameServices/PlayGameServices.h>

@class GPPSignIn;

@implementation NativeC : NSObject
@synthesize m_delegate;

static NativeC* _instance = nil;
+ (id)sharedNative
{
	if(!_instance){
		_instance = [[NativeC alloc] init];
		_instance.isSignIn = NO;
		_instance.isSlient = NO;
	}
	return _instance;
}

- (void)GPPSignIn{
	GPPSignIn* signIn = [GPPSignIn sharedInstance];
	[signIn authenticate];
}
-(void)GPPSignOut
{
	if([[GPGManager sharedInstance] hasAuthorizer]){
		[[GPGManager sharedInstance] signout];
	}
	[[GPPSignIn sharedInstance] signOut];
	self.isSignIn = NO;
	m_delegate->onResult(-1, Nil, Nil, Nil, Nil);
}
-(BOOL)trySlientSignIn
{
	if(self.isSignIn == NO){
		self.isSlient = true;
		self.isSignIn = [[GPPSignIn sharedInstance] trySilentAuthentication];
	}
	return self.isSignIn;
}

- (void)TellSignInInfomation:(const char *)ggpuid gmail:(const char *)val url:(const char *)val2 userName:(const char *)val3
{
	if(ggpuid != nil){
		self.isSignIn = YES;
	}
	if(m_delegate != nil){
		if(self.isSlient){
			m_delegate->onResult(1,ggpuid ,  val, val2,val3);
			self.isSlient = NO;
		}
		else{
			m_delegate->onResult(0,ggpuid ,  val, val2,val3);
		}
	}
}

- (void)addDelegate:(NativeCallDelegate*)pDelegate
{
	m_delegate = pDelegate;
}



@end
