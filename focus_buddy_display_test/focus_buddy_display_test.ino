#include "board_def.h"

#define DISPLAY_TEST_ONLY 1
#define TASK_SELECT 1
// BLACK is already defined in board_def.h; removed duplicate define to avoid
// "macro redefined" warning.
// 1 = Task A
// 2 = Task B
// 3 = Task C

#if TASK_SELECT == 1
#include "task_a_emotion/emotion.h"
#define TASK_SETUP() emotion_setup()
#define TASK_LOOP() emotion_loop()
#elif TASK_SELECT == 2
#include "task_b_lvgl_ui/ui_task_list.h"
#include "task_b_lvgl_ui/ui_focus_timer.h"
void lvgl_ui_setup();
void lvgl_ui_loop();
#define TASK_SETUP() lvgl_ui_setup()
#define TASK_LOOP() lvgl_ui_loop()
#elif TASK_SELECT == 3
#include "task_c_concept_carousel/concept_carousel.h"
#define TASK_SETUP() carousel_setup()
#define TASK_LOOP() carousel_loop()
#endif

void setup() {
  Serial.begin(115200);
  if (!gfx_init()) {
    Serial.println("[DISPLAY_INIT] abort");
    return;
  }
#if !DISPLAY_TEST_ONLY
  TASK_SETUP();
#endif
}

void loop() {
#if DISPLAY_TEST_ONLY
  gfx_display_test_loop();
#else
  TASK_LOOP();
#endif
}
