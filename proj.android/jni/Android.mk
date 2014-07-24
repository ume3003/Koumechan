LOCAL_PATH := $(call my-dir)
PROJECT_DIR := $(LOCAL_PATH)/../
COCOS2DX_ROOT := $(LOCAL_PATH)/../../cocos2d

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

#cppファイルの自動検索設定
CPP_FILES := $(shell find $(LOCAL_PATH)/../../Classes -name *.cpp)                   
LOCAL_SRC_FILES := main.cpp
LOCAL_SRC_FILES += ../../Classes/Models/sqlite3.c
LOCAL_SRC_FILES += $(CPP_FILES:$(LOCAL_PATH)/%=%)

LOCAL_C_INCLUDES := $(shell find $(LOCAL_PATH)/../../Classes -type d) 
#LOCAL_C_INCLUDES += $(COCOS2DX_ROOT)/cocos/editor-support
LOCAL_C_INCLUDES += $(shell find $(COCOS2DX_ROOT)/extensions -type d) 

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += spine_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosbuilder_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_network_static


include $(BUILD_SHARED_LIBRARY)

$(call import-add-path,$(COCOS2DX_ROOT))
$(call import-add-path,$(COCOS2DX_ROOT)/cocos)
$(call import-add-path,$(COCOS2DX_ROOT)/external)
$(call import-add-path,$(COCOS2DX_ROOT)/cocos/platform/android)

$(call import-module,.)
$(call import-module,extensions)
$(call import-module,audio/android)
$(call import-module,editor-support/spine)
$(call import-module,editor-support/cocosbuilder)
$(call import-module,network)



#$(call import-module,platform/android)
#$(call import-module,plugin/protocols/proj.android/jni) 
