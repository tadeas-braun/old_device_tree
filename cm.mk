<<<<<<< HEAD
$(call inherit-product, device/sony/pepper/full_pepper.mk)
=======
$(call inherit-product, device/sony/lotus/full_lotus.mk)
>>>>>>> upstream/cm-11.0

# Inherit CM common GSM stuff.
$(call inherit-product, vendor/cm/config/gsm.mk)

# Inherit CM common Phone stuff.
$(call inherit-product, vendor/cm/config/common_full_phone.mk)

PRODUCT_NAME := cm_pepper
PRODUCT_DEVICE := pepper

