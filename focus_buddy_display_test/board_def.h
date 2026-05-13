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
#include "pin_config.h"
#include <Wire.h>

#ifndef DEBUG_LOG
#define DEBUG_LOG 1
#endif

#define BOOT_BTN_PIN 0

extern Arduino_DataBus *bus;
extern Arduino_CO5300 *gfx;

bool gfx_init();
void gfx_display_test_loop();
void board_log(const char *tag, const char *msg);
