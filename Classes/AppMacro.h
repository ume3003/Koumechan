//
//  AppMacros.h
//  KingdomBuild
//
//  Created by 上野 彰三 on 2013/08/03.
//
//

#ifndef KingdomBuild_AppMacros_h
#define KingdomBuild_AppMacros_h

#include "cocos2d.h"


typedef struct tagResource {
	cocos2d::Size size;
	char directory[100];
} Resource;

static Resource smallResource	= {cocos2d::Size( 384, 512) ,"resources-small"};
static Resource largeResource	= {cocos2d::Size( 768,1024) ,"resources-large"};
static Resource xlargeResource	= {cocos2d::Size(1536,2048) ,"resources-xlarge"};

static cocos2d::Size   designResolutionSize = cocos2d::Size(577,1024);

static float smallScale = 0.5f;
static float largeScale = 1.0f;
static float xlargeScale = 2.0f;

static int baseFont = 16;
static float smallFontEx  = 1.00f; // 16
static float largeFontEx  = 1.00f;  // 20
static float xlargeFontEx = 1.25f;  // 24

static int normalFontScale = 1; //  9 12 18 
static int middleFontScale = 2; // 18 24 36
static int largeFontScale  = 3; // 27 36 54

#endif
