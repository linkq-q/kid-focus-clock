#pragma once
#include <lvgl.h>
#include <stdint.h>

typedef struct {
  const char *emoji;
  const char *name;
  uint8_t duration_min;
} TaskItem;

extern const TaskItem g_tasks[4];
void ui_task_list_create(lv_obj_t *parent);
void ui_task_list_destroy();
int ui_task_list_get_selected();
void ui_task_list_select_prev();
void ui_task_list_select_next();
