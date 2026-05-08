#include "ui_focus_timer.h"
#include <stdio.h>

static lv_obj_t *s_root, *s_time_label, *s_task_label, *s_state_label, *s_arc;
static uint32_t s_total_s, s_left_s, s_last_ms;
static bool s_paused, s_done;

static void render() {
  char buf[16];
  snprintf(buf, sizeof(buf), "%02lu:%02lu", (unsigned long)(s_left_s / 60), (unsigned long)(s_left_s % 60));
  lv_label_set_text(s_time_label, buf);
  lv_arc_set_value(s_arc, s_total_s == 0 ? 0 : (int)((100UL * s_left_s) / s_total_s));
}

void ui_focus_timer_create(lv_obj_t *parent, const TaskItem *task) {
  s_root = lv_obj_create(parent); lv_obj_set_size(s_root, 466, 466);
  lv_obj_set_style_bg_color(s_root, lv_color_black(), 0); lv_obj_set_style_border_width(s_root, 0, 0);
  s_arc = lv_arc_create(s_root); lv_obj_set_size(s_arc, 300, 300); lv_obj_center(s_arc); lv_arc_set_range(s_arc, 0, 100);
  lv_obj_clear_flag(s_arc, LV_OBJ_FLAG_CLICKABLE);
  s_time_label = lv_label_create(s_root); lv_obj_set_style_text_font(s_time_label, &lv_font_montserrat_48, 0); lv_obj_center(s_time_label);
  s_task_label = lv_label_create(s_root); lv_label_set_text(s_task_label, task->name); lv_obj_align(s_task_label, LV_ALIGN_CENTER, 0, 80);
  s_state_label = lv_label_create(s_root); lv_label_set_text(s_state_label, "专注中"); lv_obj_align(s_state_label, LV_ALIGN_BOTTOM_MID, 0, -20);
  s_total_s = (uint32_t)task->duration_min * 60U; s_left_s = s_total_s; s_last_ms = millis(); s_paused = false; s_done = false; render();
}
void ui_focus_timer_destroy() { if (s_root) lv_obj_del(s_root); s_root = nullptr; }
void ui_focus_timer_pause_resume() { if (s_done) return; s_paused = !s_paused; lv_label_set_text(s_state_label, s_paused ? "已暂停" : "专注中"); }
bool ui_focus_timer_is_done() { return s_done; }
void ui_focus_timer_tick() { if (s_paused || s_done) return; uint32_t now = millis(); if (now - s_last_ms >= 1000) { s_last_ms += 1000; if (s_left_s > 0) --s_left_s; if (s_left_s == 0) { s_done = true; lv_label_set_text(s_time_label, "✓ 完成!"); } render(); } }
