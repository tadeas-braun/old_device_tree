#
# Copyright 2012 The Android Open Source Project
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

# Sample: This is where we'd set a backup provider if we had one
# $(call inherit-product, device/sample/products/backup_overlay.mk)

# Inherit GSM configuration 
$(call inherit-product, vendor/omni/config/gsm.mk)

# Most specific first.
$(call inherit-product, $(SRC_TARGET_DIR)/product/full_base_telephony.mk)

# Inherit from our custom product configuration
$(call inherit-product, vendor/omni/config/common.mk)

# Inherit from hardware-specific part of the product configuration
$(call inherit-product, device/sony/pepper/full_pepper.mk)

PRODUCT_NAME := omni_pepper
PRODUCT_DEVICE := pepper
PRODUCT_BRAND := sony
PRODUCT_MODEL := Xperia Sola
PRODUCT_MANUFACTURER := Sony

PRODUCT_BUILD_PROP_OVERRIDES += PRODUCT_NAME=MT27i_1262-1120 BUILD_FINGERPRINT=SEMC/MT27i_1262-1120/MT27i:4.0.4/6.1.1.B.1.10/9bt3zw:user/release-keys PRIVATE_BUILD_DESC="MT27i-user 4.0.4 6.1.1.B.1.10 9bt3zw test-keys"


# Kernel inline build
TARGET_KERNEL_CONFIG := xperiasola_defconfig
