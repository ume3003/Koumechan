APP_STL := gnustl_static
#APP_ABI := armeabi-v7a
APP_PLATFORM := android-9

APP_OPTIM := debug
#APP_OPTIM := release

ifeq ($(APP_OPTIM),debug)
	  APP_CPPFLAGS := -frtti -DCOCOS2D_DEBUG=1 -std=c++11 -fsigned-char -Wno-literal-suffix -Wno-deprecated-declarations
	    LOCAL_LDLIBS := -L$(SYSROOT)/usr/lib -ldl -ldebug -llog
	else
	  APP_CPPFLAGS := -frtti -DCOCOS2D_DEBUG=0 -std=c++11 -fsigned-char -Wno-literal-suffix  -Wno-deprecated-declarations
	    LOCAL_LDLIBS := -L$(SYSROOT)/usr/lib -ldl -llog
	endif

