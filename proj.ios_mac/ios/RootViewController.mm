/****************************************************************************
 Copyright (c) 2013      cocos2d-x.org
 Copyright (c) 2013-2014 Chukong Technologies Inc.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#import "RootViewController.h"
#import "cocos2d.h"
#import "CCEAGLView.h"
#import <GooglePlus/GooglePlus.h>
#import "GTL/GTLPlus/GTLPlusConstants.h"
#import "GTL/GTLPlus/GTLPlusPerson.h"
#import <PlayGameServices/PlayGameServices.h>
#import "NativeCall_objc.h"

@class GTMOAuth2Authentication;
@class GPPSignIn;
@class GPGManager;

@implementation RootViewController

/*
 // The designated initializer.  Override if you create the controller programmatically and want to perform customization that is not appropriate for viewDidLoad.
- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil {
    if ((self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil])) {
        // Custom initialization
    }
    return self;
}
*/

/*
// Implement loadView to create a view hierarchy programmatically, without using a nib.
- (void)loadView {
}
*/

/*
// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad {
    [super viewDidLoad];
}

*/
// Override to allow orientations other than the default portrait orientation.
// This method is deprecated on ios6
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
	//    return UIInterfaceOrientationIsLandscape( interfaceOrientation );
	return UIInterfaceOrientationIsPortrait(interfaceOrientation);
}

// For ios6, use supportedInterfaceOrientations & shouldAutorotate instead
- (NSUInteger) supportedInterfaceOrientations{
#ifdef __IPHONE_6_0
	//    return UIInterfaceOrientationMaskAllButUpsideDown;
	return UIInterfaceOrientationMaskPortrait;
#endif
}

- (BOOL) shouldAutorotate {
    return YES;
}

- (void)didRotateFromInterfaceOrientation:(UIInterfaceOrientation)fromInterfaceOrientation {
    [super didRotateFromInterfaceOrientation:fromInterfaceOrientation];

    cocos2d::GLView *glview = cocos2d::Director::getInstance()->getOpenGLView();

    if (glview)
    {
        CCEAGLView *eaglview = (CCEAGLView*) glview->getEAGLView();

        if (eaglview)
        {
            CGSize s = CGSizeMake([eaglview getWidth], [eaglview getHeight]);
            cocos2d::Application::getInstance()->applicationScreenSizeChanged((int) s.width, (int) s.height);
        }
    }
}

//fix not hide status on ios7
- (BOOL)prefersStatusBarHidden
{
    return YES;
}

- (void)didReceiveMemoryWarning {
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];

    // Release any cached data, images, etc that aren't in use.
}

- (void)viewDidUnload {
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}


- (void)dealloc {
    [super dealloc];
}

-(void)signInGPGManager
{
	[[GPGManager sharedInstance] signIn:[GPPSignIn sharedInstance] reauthorizeHandler:^(BOOL requiresKeychainWipe, NSError *error) {
		// If we hit this, auth has failed and we need to authenticate.
		// Most likely we can refresh behind the scenes
		if (requiresKeychainWipe) {
			[[GPPSignIn sharedInstance] signOut];
		}
		[[GPPSignIn sharedInstance] authenticate];
	}];
	if([[GPGManager sharedInstance] hasAuthorizer]){
		GPPSignIn *signIn = [GPPSignIn sharedInstance];
		GTLPlusPerson* person = signIn.googlePlusUser;
		NSLog(@"find displayName %@" ,person.displayName);
		[[NativeC sharedNative] TellSignInInfomation:signIn.userID.UTF8String gmail:signIn.userEmail.UTF8String url:person.image.url.UTF8String userName:person.displayName.UTF8String];
		
	}
	
}

-(void)finishedWithAuth:(GTMOAuth2Authentication *)auth error:(NSError *)error
{
	if(error == 0 && auth){
		GPPSignIn *signIn = [GPPSignIn sharedInstance];
		NSLog(@"Player ID is %@", [auth propertyForKey:@"user_id"]);
		NSLog(@"user id %@ email %@",signIn.userID,signIn.userEmail);
		// Our GPPSignIn object has an auth token now. Pass it to the GPGManager.
		[self signInGPGManager];
	}
	else{
		NSLog(@"Failed %@ %@",error,auth);
		[[NativeC sharedNative] TellSignInInfomation:nil gmail:nil url:nil userName:nil];
	}
}

-(void)setGPPSignInInfo
{
	GPPSignIn *signIn = [GPPSignIn sharedInstance];
	signIn.clientID = kClientId ;
	//	signIn.scopes = @[kGTLAuthScopePlusLogin ];
	signIn.scopes = [NSArray arrayWithObjects:
					 kGTLAuthScopePlusLogin,
					 @"https://www.googleapis.com/auth/games",
					 @"https://www.googleapis.com/auth/appstate",
					 nil];
	signIn.language = [[NSLocale preferredLanguages] objectAtIndex:0];
	signIn.delegate = self;
	
	signIn.shouldFetchGoogleUserEmail=YES;
	signIn.shouldFetchGoogleUserID=YES;
	signIn.shouldFetchGooglePlusUser = YES;			// need PlusUser info
}

@end
