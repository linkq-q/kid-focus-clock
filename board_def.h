#pragma once

#include <Arduino.h>
#include <Arduino_GFX_Library.h>

#ifndef DEBUG_LOG
#define DEBUG_LOG 1
#endif

#define LCD_WIDTH 466
#define LCD_HEIGHT 466

// Waveshare ESP32-S3-Touch-AMOLED-1.75-B official pin map (adjust from vendor lib if needed)
#define LCD_CS 10
#define LCD_SCLK 12
#define LCD_SDIO0 11
#define LCD_SDIO1 13
#define LCD_SDIO2 14
#define LCD_SDIO3 9

#define BOOT_BTN_PIN 0

extern Arduino_GFX *gfx;

void gfx_init();
void board_log(const char *tag, const char *msg);
