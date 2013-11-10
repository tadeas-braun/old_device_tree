# for cwm touch only

ifeq ($(TARGET_PRODUCT),cm_lotus)
PRODUCT_COPY_FILES += \
    device/sony/lotus/recovery/res/images/stitch_go.png:recovery/root/res/images/stitch_go.png
endif

ifeq ($(TARGET_PRODUCT),cm_pepper)
PRODUCT_COPY_FILES += \
    device/sony/pepper/recovery/res/images/stitch_sola.png:recovery/root/res/images/stitch_sola.png
endif

ifeq ($(TARGET_PRODUCT),cm_kumquat)
PRODUCT_COPY_FILES += \
    device/sony/kumquat/recovery/res/images/stitch_u.png:recovery/root/res/images/stitch_u.png
endif

ifeq ($(TARGET_PRODUCT),cm_nypon)
PRODUCT_COPY_FILES += \
    device/sony/nypon/recovery/res/images/stitch_sola.png:recovery/root/res/images/stitch_p.png
endif
