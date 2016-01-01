
LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)
LOCAL_LDLIBS :=  -llog -lc

LOCAL_SRC_FILES:=Hooker.cpp Debug.cpp MachMemory.cpp testsub.cpp

LOCAL_CXXFLAGS :=  -Wall -O3 -fPIC -D__arm__
LOCAL_CFLAGS :=  -Wall -O3 -fPIC -D__arm__

LOCAL_PRELINK_MODULE := false  
LOCAL_MODULE    := substrate
include $(BUILD_SHARED_LIBRARY)