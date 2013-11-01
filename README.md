**Unoficial Android 4.4 (KitKat) for Sony Xperia Sola**

Getting Started :

    curl http://commondatastorage.googleapis.com/git-repo-downloads/repo > /root/bin/repo
    chmod 755 /root/bin/repo
    mkdir android4.4
    cd android4.4
    repo init -u https://android.googlesource.com/platform/manifest -b android-4.4_r1
    repo sync
    cd device
    mkdir sony
    cd sony
    git clone https://github.com/tadeas482/android_device_sony_pepper -b aosp-4.4 pepper
    cd pepper

Now connect your phone which have runing FXP CM10 :

    ./extract-files.sh
    cd ../../..
    cd hardware
    git clone https://github.com/munjeni/aosp_4.3_hardware_semc.git -b master semc
    cd ..

Patch android source code :

    patch -p1 < device/sony/pepper/patches/framework_av.patch
    patch -p1 < device/sony/pepper/patches/framework_native.patch
    patch -p1 < device/sony/pepper/patches/hardware_libhardware.patch
    patch -p1 < device/sony/pepper/patches/hardware_libhardware_legacy.patch
    patch -p1 < device/sony/pepper/patches/system_core.patch
    patch -p1 < device/sony/pepper/patches/system_netd.patch

Our step is optional!!! Use only if you going to sync AOSP source code daily, than simple revert each patch before you sync AOSP source code :

    patch -p1 -R < device/sony/pepper/patches/framework_av.patch
    patch -p1 -R < device/sony/pepper/patches/framework_native.patch
    patch -p1 -R < device/sony/pepper/patches/hardware_libhardware.patch
    patch -p1 -R < device/sony/pepper/patches/hardware_libhardware_legacy.patch
    patch -p1 -R < device/sony/pepper/patches/system_core.patch
    patch -p1 -R < device/sony/pepper/patches/system_netd.patch
    repo forall -p -c 'git checkout -f'
    repo sync
    patch -p1 < device/sony/pepper/patches/framework_av.patch
    patch -p1 < device/sony/pepper/patches/framework_native.patch
    patch -p1 < device/sony/pepper/patches/hardware_libhardware.patch
    patch -p1 < device/sony/pepper/patches/hardware_libhardware_legacy.patch
    patch -p1 < device/sony/pepper/patches/system_core.patch
    patch -p1 < device/sony/pepper/patches/system_netd.patch

You are ready to build :

    . build/envsetup.sh
    lunch aosp_pepper-userdebug
    make otapackage

ENJOY!
