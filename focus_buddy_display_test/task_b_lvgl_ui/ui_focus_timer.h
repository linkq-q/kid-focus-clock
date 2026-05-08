#pragma once
#include <lvgl.h>
#include <stdbool.h>
#include "ui_task_list.h"
void ui_focus_timer_create(lv_obj_t *parent, const TaskItem *task);
void ui_focus_timer_destroy();
void ui_focus_timer_pause_resume();
bool ui_focus_timer_is_done();
void ui_focus_timer_tick();
