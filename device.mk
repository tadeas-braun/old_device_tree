#
# Copyright (C) 2011 The Android Open-Source Project
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
#

ifeq ($(TARGET_PREBUILT_KERNEL),)
LOCAL_KERNEL := device/sony/pepper/prebuilt/kernel/zImage
else
LOCAL_KERNEL := $(TARGET_PREBUILT_KERNEL)
endif

PRODUCT_COPY_FILES := \
    $(LOCAL_KERNEL):kernel \
    device/sony/pepper/prebuilt/kernel/modules/cifs.ko:system/lib/modules/cifs.ko \
    device/sony/pepper/prebuilt/kernel/modules/cw1200_core.ko:system/lib/modules/cw1200_core.ko \
    device/sony/pepper/prebuilt/kernel/modules/cw1200_wlan.ko:system/lib/modules/cw1200_wlan.ko \
    device/sony/pepper/prebuilt/kernel/modules/mmc_test.ko:system/lib/modules/mmc_test.ko \
    device/sony/pepper/prebuilt/kernel/modules/nls_utf8.ko:system/lib/modules/nls_utf8.ko \
    device/sony/pepper/prebuilt/kernel/modules/oprofile.ko:system/lib/modules/oprofile.ko \
    device/sony/pepper/prebuilt/kernel/modules/pwr.ko:system/lib/modules/pwr.ko \
    device/sony/pepper/prebuilt/kernel/modules/rng-core.ko:system/lib/modules/rng-core.ko \
    device/sony/pepper/prebuilt/kernel/modules/scsi_wait_scan.ko:system/lib/modules/scsi_wait_scan.ko \
    device/sony/pepper/prebuilt/kernel/modules/tun.ko:system/lib/modules/tun.ko \
