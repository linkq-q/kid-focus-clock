#pragma once

/* LVGL 8.3.x minimal config for ESP32-S3 + Arduino_GFX */

#define LV_COLOR_DEPTH     16
#define LV_COLOR_16_SWAP   0

/* LVGL internal heap – 48 KB is the LVGL default; increase if needed */
#define LV_MEM_SIZE        (48U * 1024U)

/* Tick source is provided by lv_tick_inc() called from the sketch */
#define LV_TICK_CUSTOM     0

/* Logging */
#define LV_USE_LOG         0

/* Font: Montserrat 14 is the default body font; 48 is used by ui_focus_timer */
#define LV_FONT_MONTSERRAT_14  1
#define LV_FONT_MONTSERRAT_48  1

/* Keep the rest at LVGL defaults */
