#include "../board_def.h"
#include "ui_task_list.h"
#include "ui_focus_timer.h"
#include <lvgl.h>

static lv_disp_draw_buf_t s_draw_buf;
static lv_disp_drv_t s_disp_drv;
static lv_indev_drv_t s_indev_drv;
static lv_color_t *s_buf1;
static lv_color_t *s_buf2;

static bool s_touch_pressed;
static uint16_t s_touch_x, s_touch_y;

static enum { PAGE_LIST, PAGE_TIMER } s_page = PAGE_LIST;
static uint32_t s_btn_start;
static bool s_btn_prev;

static void flush_cb(lv_disp_drv_t *drv, const lv_area_t *area, lv_color_t *color_p) {
  int32_t w = area->x2 - area->x1 + 1;
  int32_t h = area->y2 - area->y1 + 1;
  gfx->draw16bitRGBBitmap(area->x1, area->y1, (uint16_t *)color_p, w, h);
  lv_disp_flush_ready(drv);
}
static void touch_cb(lv_indev_drv_t *, lv_indev_data_t *data) { data->state = s_touch_pressed ? LV_INDEV_STATE_PR : LV_INDEV_STATE_REL; data->point.x = s_touch_x; data->point.y = s_touch_y; }

static void goto_list() { ui_focus_timer_destroy(); ui_task_list_create(lv_scr_act()); s_page = PAGE_LIST; }
static void goto_timer() { ui_task_list_destroy(); ui_focus_timer_create(lv_scr_act(), &g_tasks[ui_task_list_get_selected()]); s_page = PAGE_TIMER; }

void lvgl_ui_setup() {
  lv_init();
  const uint32_t draw_size = LCD_WIDTH * LCD_HEIGHT / 10;
  s_buf1 = (lv_color_t *)ps_malloc(draw_size * sizeof(lv_color_t));
  s_buf2 = (lv_color_t *)ps_malloc(draw_size * sizeof(lv_color_t));
  lv_disp_draw_buf_init(&s_draw_buf, s_buf1, s_buf2, draw_size);
  lv_disp_drv_init(&s_disp_drv); s_disp_drv.hor_res = LCD_WIDTH; s_disp_drv.ver_res = LCD_HEIGHT; s_disp_drv.flush_cb = flush_cb; s_disp_drv.draw_buf = &s_draw_buf; lv_disp_drv_register(&s_disp_drv);
  lv_indev_drv_init(&s_indev_drv); s_indev_drv.type = LV_INDEV_TYPE_POINTER; s_indev_drv.read_cb = touch_cb; lv_indev_drv_register(&s_indev_drv);
  ui_task_list_create(lv_scr_act());
}

void lvgl_ui_loop() {
  // placeholder touch: none
  s_touch_pressed = false;
  bool pressed = (digitalRead(BOOT_BTN_PIN) == LOW);
  if (pressed && !s_btn_prev) { s_btn_start = millis(); s_btn_prev = true; }
  if (!pressed && s_btn_prev) {
    uint32_t dur = millis() - s_btn_start;
    if (dur < 1000) {
      if (s_page == PAGE_LIST) goto_timer(); else ui_focus_timer_pause_resume();
    } else if (s_page == PAGE_TIMER) goto_list();
    s_btn_prev = false;
  }
  if (s_page == PAGE_TIMER) {
    ui_focus_timer_tick();
    if (ui_focus_timer_is_done()) { static uint32_t done_ms = 0; if (done_ms == 0) done_ms = millis(); if (millis() - done_ms > 3000) { done_ms = 0; goto_list(); } }
  }
  lv_timer_handler();
}
