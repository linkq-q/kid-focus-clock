#include "concept_carousel.h"
#include "../board_def.h"
#include <lvgl.h>

static lv_obj_t *page1, *page2, *dot1, *dot2;
static ConceptPage cur = CONCEPT_AI_REPORT;
static uint32_t last_switch;

/* LVGL display driver for Task C (carousel has no lvgl_ui_app.cpp helper) */
static lv_disp_draw_buf_t s_draw_buf;
static lv_disp_drv_t      s_disp_drv;
static lv_color_t        *s_buf;

static void carousel_flush_cb(lv_disp_drv_t *drv, const lv_area_t *area, lv_color_t *color_p) {
  int32_t w = area->x2 - area->x1 + 1;
  int32_t h = area->y2 - area->y1 + 1;
  gfx->draw16bitRGBBitmap(area->x1, area->y1, (uint16_t *)color_p, w, h);
  lv_disp_flush_ready(drv);
}

static void update_ind() {
  lv_obj_set_style_bg_color(dot1, cur == CONCEPT_AI_REPORT ? lv_color_white() : lv_color_hex(0x6B7280), 0);
  lv_obj_set_style_bg_color(dot2, cur == CONCEPT_BADGE_WALL ? lv_color_white() : lv_color_hex(0x6B7280), 0);
}

void carousel_goto(ConceptPage page) {
  cur = page;
  if (cur == CONCEPT_AI_REPORT) {
    lv_obj_clear_flag(page1, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(page2, LV_OBJ_FLAG_HIDDEN);
  } else {
    lv_obj_add_flag(page1, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(page2, LV_OBJ_FLAG_HIDDEN);
  }
  update_ind();
#if DEBUG_LOG
  Serial.printf("[CAROUSEL] page -> %s at %lums\n", cur == CONCEPT_AI_REPORT ? "AI_REPORT" : "BADGE_WALL", millis());
#endif
}

ConceptPage carousel_current() { return cur; }

void carousel_setup() {
  lv_init();
  /* Register display driver so lv_scr_act() has a valid screen object */
  const uint32_t draw_size = LCD_WIDTH * LCD_HEIGHT / 10;
  s_buf = (lv_color_t *)ps_malloc(draw_size * sizeof(lv_color_t));
  lv_disp_draw_buf_init(&s_draw_buf, s_buf, NULL, draw_size);
  lv_disp_drv_init(&s_disp_drv);
  s_disp_drv.hor_res  = LCD_WIDTH;
  s_disp_drv.ver_res  = LCD_HEIGHT;
  s_disp_drv.flush_cb = carousel_flush_cb;
  s_disp_drv.draw_buf = &s_draw_buf;
  lv_disp_drv_register(&s_disp_drv);

  page1 = lv_obj_create(lv_scr_act()); lv_obj_set_size(page1, 466, 466); lv_obj_set_style_bg_color(page1, lv_color_hex(0x0F172A), 0);
  lv_obj_t *t1 = lv_label_create(page1); lv_label_set_text(t1, "今日专注报告\n总时长 95 分钟\n次数 4\n最长 32 分钟"); lv_obj_align(t1, LV_ALIGN_TOP_LEFT, 20, 20);
  page2 = lv_obj_create(lv_scr_act()); lv_obj_set_size(page2, 466, 466); lv_obj_set_style_bg_color(page2, lv_color_hex(0x0F172A), 0);
  lv_obj_t *t2 = lv_label_create(page2); lv_label_set_text(t2, "我的徽章\n已获得 3/6\n⭐ 阅读达人 ⭐ 数学专注 ⭐ 钢琴练习"); lv_obj_align(t2, LV_ALIGN_TOP_LEFT, 20, 20);
  dot1 = lv_obj_create(lv_scr_act()); dot2 = lv_obj_create(lv_scr_act()); lv_obj_set_size(dot1, 8, 8); lv_obj_set_size(dot2, 8, 8);
  lv_obj_set_style_radius(dot1, LV_RADIUS_CIRCLE, 0); lv_obj_set_style_radius(dot2, LV_RADIUS_CIRCLE, 0);
  lv_obj_align(dot1, LV_ALIGN_BOTTOM_MID, -10, -16); lv_obj_align(dot2, LV_ALIGN_BOTTOM_MID, 10, -16);
  last_switch = millis(); carousel_goto(CONCEPT_AI_REPORT);
}

void carousel_loop() {
  if (millis() - last_switch > 10000) { carousel_goto((ConceptPage)((cur + 1) % CONCEPT_COUNT)); last_switch = millis(); }
  lv_timer_handler();
}
