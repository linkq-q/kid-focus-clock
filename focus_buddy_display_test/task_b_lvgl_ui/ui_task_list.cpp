#include "ui_task_list.h"

const TaskItem g_tasks[4] = {{"📖", "语文作业", 25}, {"🔢", "数学练习", 20}, {"🎸", "练钢琴", 30}, {"📖", "英语阅读", 15}};
static lv_obj_t *s_items[4];
static lv_obj_t *s_root;
static int s_selected = 0;

static void refresh_styles() {
  for (int i = 0; i < 4; ++i) {
    lv_obj_set_style_bg_color(s_items[i], i == s_selected ? lv_color_hex(0x2563EB) : lv_color_hex(0x1F2937), 0);
  }
}

void ui_task_list_create(lv_obj_t *parent) {
  s_root = lv_obj_create(parent);
  lv_obj_set_size(s_root, 466, 466);
  lv_obj_set_style_bg_color(s_root, lv_color_black(), 0);
  lv_obj_set_style_border_width(s_root, 0, 0);
  lv_obj_t *title = lv_label_create(s_root);
  lv_label_set_text(title, "今日任务");
  lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 10);
  for (int i = 0; i < 4; ++i) {
    s_items[i] = lv_obj_create(s_root);
    lv_obj_set_size(s_items[i], 430, 72);
    lv_obj_align(s_items[i], LV_ALIGN_TOP_MID, 0, 54 + i * 82);
    lv_obj_set_style_radius(s_items[i], 12, 0);
    lv_obj_set_style_border_width(s_items[i], 0, 0);
    lv_obj_t *txt = lv_label_create(s_items[i]);
    lv_label_set_text_fmt(txt, "%s %s · %u 分钟", g_tasks[i].emoji, g_tasks[i].name, g_tasks[i].duration_min);
    lv_obj_align(txt, LV_ALIGN_LEFT_MID, 12, 0);
  }
  refresh_styles();
}
void ui_task_list_destroy() { if (s_root) lv_obj_del(s_root); s_root = nullptr; }
int ui_task_list_get_selected() { return s_selected; }
void ui_task_list_select_prev() { s_selected = (s_selected + 3) % 4; refresh_styles(); }
void ui_task_list_select_next() { s_selected = (s_selected + 1) % 4; refresh_styles(); }
