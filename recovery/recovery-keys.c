/*
 * Copyright (C) 2009 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <linux/input.h>

#include "recovery_ui.h"
#include "common.h"
#include "extendedcommands.h"


int device_toggle_display(volatile char* key_pressed, int key_code) {
    // hold power and press volume-up
    return key_pressed[KEY_POWER] && key_code == KEY_VOLUMEUP;
}

int device_handle_key(int key_code, int visible) {

    extern int __system(const char *command);
    static int fixup_xperia_usb = 0;

    if (!fixup_xperia_usb) {
        __system("/sbin/cat /sys/devices/platform/ab8500-i2c.0/ab8500-usb.0/boot_time_device > /sys/devices/platform/ab8500-i2c.0/ab8500-usb.0/boot_time_device");
        __system("/sbin/killall -9 adbd");
        __system("/sbin/echo 0 >/sys/class/android_usb/android0/enable");
        __system("/sbin/echo 0FCE >/sys/class/android_usb/android0/idVendor");
        __system("/sbin/echo 617E >/sys/class/android_usb/android0/idProduct");
        __system("/sbin/echo 'mass_storage,adb' >/sys/class/android_usb/android0/functions");
        __system("/sbin/echo 1 >/sys/class/android_usb/android0/enable");
        __system("/sbin/setprop sys.usb.state mass_storage,adb");
        __system("/sbin/setprop sys.usb.config mass_storage,adb");
        __system("/sbin/setprop persist.sys.usb.config mass_storage,adb");
        __system("/sbin/start adbd");
        __system("/sbin/setprop ro.build.product lotus");

        fixup_xperia_usb = 1;
    }

    if (visible) {
        switch (key_code) {
            case KEY_CAPSLOCK:
            case KEY_DOWN:
            case KEY_VOLUMEDOWN:
            case KEY_MENU:
                return HIGHLIGHT_DOWN;

            case KEY_LEFTSHIFT:
            case KEY_UP:
            case KEY_VOLUMEUP:
                return HIGHLIGHT_UP;

            case KEY_POWER:
                if (ui_get_showing_back_button()) {
                    return SELECT_ITEM;
                }
                if (!ui_root_menu) {
                    return GO_BACK;
                }
                break;
            case KEY_HOME:
            case KEY_LEFTBRACE:
            case KEY_ENTER:
            case BTN_MOUSE:
            case KEY_CAMERA:
            case KEY_F21:
            case KEY_SEND:
                return SELECT_ITEM;
            case KEY_END:
            case KEY_BACKSPACE:
            case KEY_SEARCH:
                if (ui_get_showing_back_button()) {
                    return SELECT_ITEM;
                }
                if (!ui_root_menu) {
                    return GO_BACK;
                }
            case KEY_BACK:
                if (!ui_root_menu) {
                    return GO_BACK;
                }
        }
    }

    return NO_ACTION;
}
