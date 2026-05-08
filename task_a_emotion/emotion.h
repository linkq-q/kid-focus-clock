#pragma once

typedef enum {
  EMOTION_HAPPY = 0,
  EMOTION_FOCUS = 1,
  EMOTION_COUNT = 2
} EmotionState;

void emotion_setup();
void emotion_loop();
void emotion_set(EmotionState state);
EmotionState emotion_get();
