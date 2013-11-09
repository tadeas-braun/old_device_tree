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

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <dirent.h>
#include <linux/input.h>
#include <string.h>
#include <time.h>
#include <pthread.h>

#include "recovery_ui.h"
#include "common.h"
#include "extendedcommands.h"

extern int __system(const char *command);
static int buttonlight = 0;

int device_toggle_display(volatile char* key_pressed, int key_code) {
    // hold power and press volume-up
    return key_pressed[KEY_POWER] && key_code == KEY_VOLUMEUP;
}

#define VIBRATOR_TIMEOUT_FILE "/sys/class/timed_output/vibrator/enable"
#define VIBRATOR_TIME_MS  10

#define BATTERY_LEVEL_FILE  "/sys/devices/platform/ab8500-i2c.0/ab8500-fg.0/power_supply/ab8500_fg/capacity"
#define BATTERY_STATUS_CHARGING_FILE_USB  "/sys/devices/platform/ab8500-i2c.0/ab8500-charger.0/power_supply/ab8500_usb/online"
#define BATTERY_STATUS_CHARGING_FILE_AC  "/sys/devices/platform/ab8500-i2c.0/ab8500-charger.0/power_supply/ab8500_ac/online"

//#if (defined XPERIA_GO || defined XPERIA_SOLA)
#define RED_LED_FILE "/sys/devices/platform/nmk-i2c.2/i2c-2/2-0040/leds/red/brightness"
#define GREEN_LED_FILE "/sys/devices/platform/nmk-i2c.2/i2c-2/2-0040/leds/green/brightness"
#define BUTTON_BACKLIGHT "/sys/devices/platform/nmk-i2c.2/i2c-2/2-0040/leds/button-backlight/brightness"
//#endif
//#ifdef XPERIA_P
//#define RED_LED_FILE "/sys/devices/platform/nmk-i2c.2/i2c-2/2-0036/leds/red/brightness"
//#define GREEN_LED_FILE "/sys/devices/platform/nmk-i2c.2/i2c-2/2-0036/leds/green/brightness"
//#define BUTTON_BACKLIGHT "/sys/devices/platform/nmk-i2c.2/i2c-2/2-0036/leds/button-backlight/brightness"
//#endif
//#ifdef XPERIA_U
//#define RED_LED_FILE "/sys/devices/platform/nmk-i2c.2/i2c-2/2-0040/leds/pwr-red/brightness"
//#define GREEN_LED_FILE "/sys/devices/platform/nmk-i2c.2/i2c-2/2-0040/leds/pwr-green/brightness"
//#define BUTTON_BACKLIGHT ???????
//#endif

int vibrate(int timeout_ms) {
    char str[20];
    int fd;
    int ret;

    fd = open(VIBRATOR_TIMEOUT_FILE, O_WRONLY);
    if (fd < 0)
        return -1;

    ret = snprintf(str, sizeof(str), "%d", timeout_ms);
    ret = write(fd, str, ret);
    close(fd);

    if (ret < 0)
       return -1;

    return 0;
}

int get_battery_level(void) {
    char buf[4];
    char *str;
    int fd;
    int level;
    ssize_t nbytes;

    fd = open(BATTERY_LEVEL_FILE, O_RDONLY);
    if (fd < 0)
        return 0;

    nbytes = read(fd, buf, sizeof(buf) - 1);
    close(fd);
    if (nbytes < 0)
        return 0;
    buf[nbytes] = '\0';

    str = strndup(buf, nbytes);
    level = atoi(str);

    return level;
}

int battery_charging_usb(void) {
    char buf[2];
    char *str;
    int fd;
    int charging;
    ssize_t nbytes;

    fd = open(BATTERY_STATUS_CHARGING_FILE_USB, O_RDONLY);
    if (fd < 0)
        return 0;

    nbytes = read(fd, buf, sizeof(buf) - 1);
    close(fd);
    if (nbytes < 0)
        return 0;
    buf[nbytes] = '\0';

    str = strndup(buf, 1);
    charging = atoi(str);

    return charging;
}

int battery_charging_ac(void) {
    char buf[2];
    char *str;
    int fd;
    int charging;
    ssize_t nbytes;

    fd = open(BATTERY_STATUS_CHARGING_FILE_AC, O_RDONLY);
    if (fd < 0)
        return 0;

    nbytes = read(fd, buf, sizeof(buf) - 1);
    close(fd);
    if (nbytes < 0)
        return 0;
    buf[nbytes] = '\0';

    str = strndup(buf, 1);
    charging = atoi(str);

    return charging;
}

int command_update_leds(char *led_file, int value) {
    char str[20];
    int fd;
    int ret;

    fd = open(led_file, O_WRONLY);
    if (fd < 0)
        return 0;

    ret = snprintf(str, sizeof(str), "%d", value);
    ret = write(fd, str, ret);
    close(fd);

    if (ret < 0)
       return 0;

    return 1;
}

void update_leds(void) {
    int level = get_battery_level();

    int charging_usb = battery_charging_usb();
    int charging_ac = battery_charging_ac();

    int val = 255;
    int val_thin = 122;
    int val_off = 0;

    int status;

    if (level == 0)
        level = 1;

    if (charging_usb || charging_ac) {
        if (level <= 95) {
            status = command_update_leds(RED_LED_FILE, val);
            status = command_update_leds(GREEN_LED_FILE, val_off);
        } else if (level > 95 && level != 100) {
            status = command_update_leds(RED_LED_FILE, val_thin);
            status = command_update_leds(GREEN_LED_FILE, val_thin);
        } else  {
            status = command_update_leds(RED_LED_FILE, val_off);
            status = command_update_leds(GREEN_LED_FILE, val);
        }
    } else {
            status = command_update_leds(RED_LED_FILE, val_off);
            status = command_update_leds(GREEN_LED_FILE, val_off);
    }

    return;
}

static void *leds_thread(void *cookie) {
    for (;;) {
        sleep(2);
        update_leds();
    }
    return NULL;
}

int device_handle_key(int key_code, int visible) {

    if (visible) {

        if (!buttonlight) {
            char buttonlights_command[100];
            snprintf(buttonlights_command, sizeof(buttonlights_command), "/sbin/echo 255 > %s", BUTTON_BACKLIGHT);
            __system(buttonlights_command);

            pthread_t t;
            pthread_create(&t, NULL, leds_thread, NULL);

            buttonlight = 1;
        }

        switch (key_code) {
            case KEY_CAPSLOCK:
            case KEY_DOWN:
            case KEY_MENU:
                vibrate(VIBRATOR_TIME_MS);
                return HIGHLIGHT_DOWN;

            case KEY_VOLUMEDOWN:
                return HIGHLIGHT_DOWN;

            case KEY_LEFTSHIFT:
            case KEY_UP:
                vibrate(VIBRATOR_TIME_MS);
                return HIGHLIGHT_UP;

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
                vibrate(VIBRATOR_TIME_MS);
                return SELECT_ITEM;
            case KEY_END:
            case KEY_BACKSPACE:
            case KEY_SEARCH:
                if (ui_get_showing_back_button()) {
                    vibrate(VIBRATOR_TIME_MS);
                    return SELECT_ITEM;
                }
                if (!ui_root_menu) {
                    vibrate(VIBRATOR_TIME_MS);
                    return GO_BACK;
                }
            case KEY_BACK:
                if (!ui_root_menu) {
                    vibrate(VIBRATOR_TIME_MS);
                    return GO_BACK;
                }
        }
    }

    return NO_ACTION;
}
