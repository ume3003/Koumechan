#include "AppDelegate.h"
#include "AppMacro.h"
#include "KoumeChan.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("KoumeChan");
        director->setOpenGLView(glview);
    }

	glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER);
	
	float fontEx = smallFontEx;
	Size frameSize = glview->getFrameSize();
	std::vector<std::string> searchPath;
	
	if(frameSize.width > largeResource.size.width){	// iPad retina
		searchPath.push_back(xlargeResource.directory);
		director->setContentScaleFactor(xlargeScale);
		fontEx = xlargeFontEx;
		log("xLarge %3.2f/%3.2f framesize %3.2f/%3.2f-%2.1f",xlargeResource.size.width,xlargeResource.size.height,frameSize.width,frameSize.height,director->getContentScaleFactor());
	}
	else if(frameSize.width > smallResource.size.width){ // iPad
		searchPath.push_back(largeResource.directory);
		director->setContentScaleFactor(largeScale);
		fontEx = largeFontEx;
		log("large %3.2f/%3.2f framesize %3.2f/%3.2f-%2.1f",largeResource.size.width,largeResource.size.height,frameSize.width,frameSize.height,director->getContentScaleFactor());
	}
	else{	// iPhone
		searchPath.push_back(smallResource.directory);
		director->setContentScaleFactor(smallScale);
		fontEx = smallFontEx;
		log("small %3.2f/%3.2f framesize %3.2f/%3.2f-%2.1f",smallResource.size.width,smallResource.size.height,frameSize.width,frameSize.height,director->getContentScaleFactor());
	}
	
	std::vector<std::string> paths;
	paths.push_back("published");
	FileUtils::getInstance()->setSearchPaths(paths);
	FileUtils::getInstance()->setSearchResolutionsOrder(searchPath);
	
	float fWidth = frameSize.width / director->getContentScaleFactor();		// 768のはず
	float fHeight = frameSize.height / director->getContentScaleFactor();		// 1024のはず
	float rRate = designResolutionSize.width / fWidth;							// 577 / 768
	float rHeight = designResolutionSize.height / rRate;						// 1024 * 577 / 768 = 1366
	float fDiff = (rHeight - fHeight ) / 2;										// 1366 - 1024 = 342  342 / 2 171のはず
	float rDiff = fDiff * rRate ;												// 171 * 577 / 768 128 のはず
	log("fWidth %3.2f fHeight %3.2f fDiff %3.2f rDiff %3.2f",fWidth,fHeight,fDiff,rDiff);
	KoumeChan* chan = KoumeChan::getInstance();
	chan->setDiffHeight(rDiff);
	
	chan->setSmallFont(baseFont * fontEx * normalFontScale);
	chan->setMidFont(baseFont * fontEx * middleFontScale);
	chan->setLargeFont(baseFont * fontEx * largeFontScale);
	
    // turn on display FPS
    director->setDisplayStats(true);
	
    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);
	
	chan->loadPref();
	log("KoumeChan::Start StartScene");
	chan->showStartScene();
	
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
	log("enter background");
	Director::getInstance()->stopAnimation();
	Director::getInstance()->pause();
    CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    CocosDenshion::SimpleAudioEngine::getInstance()->pauseAllEffects();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
	log("restore from background");
 	Director::getInstance()->resume();
    Director::getInstance()->startAnimation();
    CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    CocosDenshion::SimpleAudioEngine::getInstance()->resumeAllEffects();
}
