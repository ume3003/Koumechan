//
//  NativeCalljni.cpp
//  Koumechan
//
//  Created by 上野　彰三 on 2014/04/23.
//
//

#include "NativeCalljni.h"
#include "platform/android/jni/JniHelper.h"
#include <jni.h>
#include "Native.h"

extern "C"
{
	void GPPSignInJNI()
	{
		cocos2d::JniMethodInfo t;
		if(cocos2d::JniHelper::getStaticMethodInfo(t,"com/smikiegames/Koumechan/AppActivity","gppSignIn","()V")){
			t.env->CallStaticVoidMethod(t.classID,t.methodID);
			t.env->DeleteLocalRef(t.classID);
		}
	}
	void GPPSignOutJNI()
	{
		cocos2d::JniMethodInfo t;
		if(cocos2d::JniHelper::getStaticMethodInfo(t,"com/smikiegames/Koumechan/AppActivity","gppSignOut","()V")){
			t.env->CallStaticVoidMethod(t.classID,t.methodID);
			t.env->DeleteLocalRef(t.classID);
		}
	}
	bool isSignInJNI()
	{
		jboolean ret = false;
		cocos2d::JniMethodInfo t;
		if(cocos2d::JniHelper::getStaticMethodInfo(t,"com/smikiegames/Koumechan/AppActivity","isSignIn","()Z")){
			ret = t.env->CallStaticBooleanMethod(t.classID,t.methodID);
			t.env->DeleteLocalRef(t.classID);
		}
		return ret;
	}
	bool trySilentSignInJNI()
	{
		jboolean ret = false;
		cocos2d::JniMethodInfo t;
		if(cocos2d::JniHelper::getStaticMethodInfo(t,"com/smikiegames/Koumechan/AppActivity","trySilentSignIn","()Z")){
			ret = t.env->CallStaticBooleanMethod(t.classID,t.methodID);
			t.env->DeleteLocalRef(t.classID);
		}
		return ret;
	}
	
	bool JNICALL Java_com_smikiegames_Koumechan_AppActivity_onResult(JNIEnv* env,jobject thiz,jint stat,jstring gppid,jstring gmail ,jstring gurl,jstring gname)
	{
		const char* pzGppId = env->GetStringUTFChars(gppid,NULL);
		const char* pzGmail = env->GetStringUTFChars(gmail,NULL);
		const char* pzGUrl  = env->GetStringUTFChars(gurl ,NULL);
		const char* pzGName = env->GetStringUTFChars(gname,NULL);
		bool result = NativeCall::onResult(stat,pzGppId,pzGmail,pzGUrl,pzGName);
		env->ReleaseStringUTFChars(gppid,pzGppId);
		env->ReleaseStringUTFChars(gmail,pzGmail);
		env->ReleaseStringUTFChars(gurl ,pzGUrl);
		env->ReleaseStringUTFChars(gname,pzGName);
		return result;
	}
}
