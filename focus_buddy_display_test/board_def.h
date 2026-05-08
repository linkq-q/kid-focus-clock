#pragma once

/*
 * Tell LVGL to locate lv_conf.h via the normal include path ("-I sketchdir").
 * Without this, lv_conf_internal.h looks for "../../lv_conf.h" relative to
 * the library directory and silently falls back to LV_CONF_SKIP (all defaults),
 * leaving LV_FONT_MONTSERRAT_48 disabled and causing a linker error.
 */
#ifndef LV_CONF_INCLUDE_SIMPLE
#define LV_CONF_INCLUDE_SIMPLE
#endif

#include <Arduino.h>
#include <Arduino_GFX_Library.h>
#include <Wire.h>

#ifndef DEBUG_LOG
#define DEBUG_LOG 1
#endif

#define LCD_WIDTH 466
#define LCD_HEIGHT 466

// RGB565 color definitions (Arduino_GFX uses 16-bit 565 colors)
#define BLACK 0x0000
#define WHITE 0xFFFF
#define RED 0xF800
#define GREEN 0x07E0
#define BLUE 0x001F
#define YELLOW 0xFFE0
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define GRAY 0x7BEF

// Waveshare ESP32-S3-Touch-AMOLED-1.75-B official pin map (adjust from vendor lib if needed)
#define LCD_CS 10
#define LCD_SCLK 12
#define LCD_SDIO0 11
#define LCD_SDIO1 13
#define LCD_SDIO2 14
#define LCD_SDIO3 9

// Match Waveshare 01_Hello_world flow: initialize board I2C before display begin.
// If your local official pin_config.h uses different values, replace these macros with that file's exact values.
#define IIC_SDA 4
#define IIC_SCL 5

// Official demo passes LCD_RESET into Arduino_CO5300 constructor.
// Keep configurable here to avoid hard-coding a wrong board revision pin.
#ifndef LCD_RESET
#define LCD_RESET -1
#endif

#define BOOT_BTN_PIN 0

extern Arduino_GFX *gfx;

void gfx_init();
void gfx_display_test_loop();
void board_log(const char *tag, const char *msg);
