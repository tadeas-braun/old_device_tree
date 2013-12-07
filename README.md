**Unoficial CM 11.0 (Android 4.4 KitKat) for Sony Xperia Sola**

Getting Started :

    mkdir cm-11.0
    cd cm-11.0
    repo init -u https://github.com/tadeas482/manifest.git -b cm-11.0
    repo sync

Patch android source code :

    patch -p1 < device/sony/pepper/patches/framework_av.patch
    patch -p1 < device/sony/pepper/patches/framework_native.patch
    patch -p1 < device/sony/pepper/patches/framework_base.patch
    patch -p1 < device/sony/pepper/patches/hardware_libhardware.patch
    patch -p1 < device/sony/pepper/patches/hardware_libhardware_legacy.patch
    patch -p1 < device/sony/pepper/patches/system_core.patch
    patch -p1 < device/sony/pepper/patches/bionic.patch
    patch -p1 < device/sony/pepper/patches/bootable_recovery.patch
    patch -p1 < device/sony/pepper/patches/external_bluetooth_bluedroid.patch

Our step is optional!!! Use only if you going to sync CM 11 source code daily, than simple revert each patch before you sync CM 11 source code :

    patch -p1 -R < device/sony/pepper/patches/framework_av.patch
    patch -p1 -R < device/sony/pepper/patches/framework_native.patch
    patch -p1 -R < device/sony/pepper/patches/framework_base.patch
    patch -p1 -R < device/sony/pepper/patches/hardware_libhardware.patch
    patch -p1 -R < device/sony/pepper/patches/hardware_libhardware_legacy.patch
    patch -p1 -R < device/sony/pepper/patches/system_core.patch
    patch -p1 -R < device/sony/pepper/patches/bionic.patch
    patch -p1 -R < device/sony/pepper/patches/bootable_recovery.patch
    patch -p1 -R < device/sony/pepper/patches/external_bluetooth_bluedroid.patch
    repo forall -p -c 'git checkout -f'
    repo sync
    patch -p1 < device/sony/pepper/patches/framework_av.patch
    patch -p1 < device/sony/pepper/patches/framework_native.patch
    patch -p1 < device/sony/pepper/patches/framework_base.patch
    patch -p1 < device/sony/pepper/patches/hardware_libhardware.patch
    patch -p1 < device/sony/pepper/patches/hardware_libhardware_legacy.patch
    patch -p1 < device/sony/pepper/patches/system_core.patch
    patch -p1 < device/sony/pepper/patches/bionic.patch
    patch -p1 < device/sony/pepper/patches/bootable_recovery.patch
    patch -p1 < device/sony/pepper/patches/external_bluetooth_bluedroid.patch

Download CM prebuilts :
   cd vendor/cm
   ./get-prebuilts
   cd ../..

You are ready to build :

    . build/envsetup.sh
    lunch cm_pepper-userdebug
    make otapackage

ENJOY!
