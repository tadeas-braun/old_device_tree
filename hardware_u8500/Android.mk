# Copyright (C) 2012 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

ifeq ($(BOARD_USES_STE_HARDWARE), true)

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_PRELINK_MODULE := false
LOCAL_SRC_FILES := display/b2r2lib/src/blt_b2r2.c
LOCAL_MODULE_PATH := $(TARGET_OUT_SHARED_LIBRARIES)
LOCAL_C_INCLUDES += $(LOCAL_PATH)/display/b2r2lib/include
LOCAL_SHARED_LIBRARIES := liblog
LOCAL_MODULE := libblt_hw
LOCAL_MODULE_TAGS := optional
include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := libomxil-bellagio
LOCAL_MODULE_TAGS := optional
SRC := media/libomxil-bellagio/src
BASE := media/libomxil-bellagio/src/base
LOCAL_SRC_FILES := \
   $(SRC)/st_static_component_loader.c \
   $(SRC)/omxcore.c \
   $(SRC)/omx_create_loaders_linux.c \
   $(SRC)/tsemaphore.c \
   $(SRC)/queue.c \
   $(SRC)/utils.c \
   $(SRC)/common.c \
   $(SRC)/content_pipe_inet.c \
   $(SRC)/content_pipe_file.c \
   $(SRC)/omx_reference_resource_manager.c \
   $(SRC)/getline.c \
   $(BASE)/omx_base_component.c \
   $(BASE)/omx_base_port.c \
   $(BASE)/omx_base_filter.c \
   $(BASE)/omx_base_sink.c \
   $(BASE)/omx_base_source.c \
   $(BASE)/omx_base_audio_port.c \
   $(BASE)/omx_base_video_port.c \
   $(BASE)/omx_base_image_port.c \
   $(BASE)/omx_base_clock_port.c \
   $(BASE)/OMXComponentRMExt.c

LOCAL_C_INCLUDES := \
   $(LOCAL_PATH)/media/libomxil-bellagio/include \
   $(LOCAL_PATH)/$(BASE) \
   $(LOCAL_PATH)/$(SRC)

LOCAL_CFLAGS += -DRELEASE -D__RELEASE
LOCAL_SHARED_LIBRARIES := \
   libdl \
   liblog

include $(BUILD_SHARED_LIBRARY)

endif # BOARD_USES_STE_HARDWARE
