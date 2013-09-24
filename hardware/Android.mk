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

include $(CLEAR_VARS)
SRC := liblights
LOCAL_SRC_FILES := $(SRC)/lights.c
LOCAL_C_INCLUDES += $(LOCAL_PATH)
LOCAL_PRELINK_MODULE := false
LOCAL_MODULE_PATH := $(TARGET_OUT_SHARED_LIBRARIES)/hw
LOCAL_SHARED_LIBRARIES := liblog
LOCAL_MODULE := lights.$(TARGET_BOARD_PLATFORM)
LOCAL_MODULE_TAGS := optional
include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)
SRC := netlink/lib
LOCAL_SRC_FILES := \
   $(SRC)/cache_mngr.c \
   $(SRC)/nl.c \
   $(SRC)/cache.c \
   $(SRC)/error.c \
   $(SRC)/data.c \
   $(SRC)/addr.c \
   $(SRC)/socket.c \
   $(SRC)/msg.c \
   $(SRC)/attr.c \
   $(SRC)/object.c \
   $(SRC)/doc.c \
   $(SRC)/cache_mngt.c \
   $(SRC)/utils.c \
   $(SRC)/handlers.c \
   $(SRC)/fib_lookup/lookup.c \
   $(SRC)/fib_lookup/request.c \
   $(SRC)/genl/ctrl.c \
   $(SRC)/genl/mngt.c \
   $(SRC)/genl/family.c \
   $(SRC)/genl/genl.c \
   $(SRC)/netfilter/log_obj.c \
   $(SRC)/netfilter/log.c \
   $(SRC)/netfilter/queue.c \
   $(SRC)/netfilter/log_msg_obj.c \
   $(SRC)/netfilter/queue_obj.c \
   $(SRC)/netfilter/netfilter.c \
   $(SRC)/netfilter/log_msg.c \
   $(SRC)/netfilter/queue_msg.c \
   $(SRC)/netfilter/nfnl.c \
   $(SRC)/netfilter/queue_msg_obj.c \
   $(SRC)/netfilter/ct.c \
   $(SRC)/netfilter/ct_obj.c \
   $(SRC)/route/tc.c \
   $(SRC)/route/class_api.c \
   $(SRC)/route/qdisc_obj.c \
   $(SRC)/route/nexthop.c \
   $(SRC)/route/route_utils.c \
   $(SRC)/route/cls_api.c \
   $(SRC)/route/cls.c \
   $(SRC)/route/qdisc_api.c \
   $(SRC)/route/link/vlan.c \
   $(SRC)/route/link/api.c \
   $(SRC)/route/link.c \
   $(SRC)/route/sch/dsmark.c \
   $(SRC)/route/sch/red.c \
   $(SRC)/route/sch/netem.c \
   $(SRC)/route/sch/cbq.c \
   $(SRC)/route/sch/blackhole.c \
   $(SRC)/route/sch/sfq.c \
   $(SRC)/route/sch/tbf.c \
   $(SRC)/route/sch/htb.c \
   $(SRC)/route/sch/prio.c \
   $(SRC)/route/sch/fifo.c \
   $(SRC)/route/addr.c \
   $(SRC)/route/neightbl.c \
   $(SRC)/route/rtnl.c \
   $(SRC)/route/route.c \
   $(SRC)/route/class.c \
   $(SRC)/route/rule.c \
   $(SRC)/route/class_obj.c \
   $(SRC)/route/qdisc.c \
   $(SRC)/route/route_obj.c \
   $(SRC)/route/cls/u32.c \
   $(SRC)/route/cls/cgroup.c \
   $(SRC)/route/cls/fw.c \
   $(SRC)/route/cls/police.c \
   $(SRC)/route/cls/basic.c \
   $(SRC)/route/cls/ematch.c \
   $(SRC)/route/neigh.c \
   $(SRC)/route/cls_obj.c

# We need to include out own set of
# linux header files before the bionic ones,
# so we turn off the default compiler flags
# and add them ourselves after our own
# include directory.
LOCAL_NO_DEFAULT_COMPILER_FLAGS := true
LOCAL_C_INCLUDES := \
	$(LOCAL_PATH)/netlink/include \
	$(TARGET_PROJECT_INCLUDES) \
	$(TARGET_C_INCLUDES)
LOCAL_CFLAGS := \
	$(TARGET_GLOBAL_CFLAGS)
ifeq ($(TARGET_ARCH),arm)
	LOCAL_CFLAGS += $(normal_objects_cflags)
endif
LOCAL_PRELINK_MODULE := false
LOCAL_SHARED_LIBRARIES := libc libcutils
LOCAL_MODULE := libnl
LOCAL_MODULE_TAGS := optional
include $(BUILD_SHARED_LIBRARY)

endif # BOARD_USES_STE_HARDWARE
