#include "emotion.h"
#include "../board_def.h"

static EmotionState s_state = EMOTION_HAPPY;
static uint8_t s_frame = 0;
static uint32_t s_last_frame_ms = 0;
static uint32_t s_last_state_ms = 0;

static void draw_face() {
  const int16_t ox = (LCD_WIDTH - FRAME_W) / 2;
  const int16_t oy = (LCD_HEIGHT - FRAME_H) / 2;
  gfx->fillRect(ox, oy, FRAME_W, FRAME_H, BLACK);

  if (s_state == EMOTION_HAPPY) {
    gfx->fillCircle(LCD_WIDTH / 2, LCD_HEIGHT / 2, 90, 0xFFE0);
    gfx->fillCircle(LCD_WIDTH / 2 - 35, LCD_HEIGHT / 2 - 25, 10, BLACK);
    gfx->fillCircle(LCD_WIDTH / 2 + 35, LCD_HEIGHT / 2 - 25, s_frame ? 3 : 10, BLACK);
    gfx->drawFastHLine(LCD_WIDTH / 2 - 35, LCD_HEIGHT / 2 + 35, 70, BLACK);
  } else {
    gfx->fillCircle(LCD_WIDTH / 2, LCD_HEIGHT / 2, 90, 0x051F);
    gfx->drawFastHLine(LCD_WIDTH / 2 - 48, LCD_HEIGHT / 2 - 25, 28, WHITE);
    gfx->drawFastHLine(LCD_WIDTH / 2 + 20, LCD_HEIGHT / 2 - 25, 28, WHITE);
    gfx->drawFastHLine(LCD_WIDTH / 2 - 25, LCD_HEIGHT / 2 + 40, 50, s_frame ? WHITE : 0x7BEF);
  }
}

void emotion_setup() {
  s_last_frame_ms = millis();
  s_last_state_ms = millis();
  draw_face();
}

void emotion_loop() {
  const uint32_t now = millis();
  if (now - s_last_frame_ms >= 600) {
    s_last_frame_ms = now;
    uint8_t prev = s_frame;
    s_frame ^= 1;
    draw_face();
#if DEBUG_LOG
    Serial.printf("[FRAME] %s frame %u -> %u at %lums\n", s_state == EMOTION_HAPPY ? "happy" : "focus", prev, s_frame, now);
#endif
  }

  if (now - s_last_state_ms >= 3000) {
    s_last_state_ms = now;
    EmotionState prev_state = s_state;
    s_state = (s_state == EMOTION_HAPPY) ? EMOTION_FOCUS : EMOTION_HAPPY;
    s_frame = 0;
    draw_face();
#if DEBUG_LOG
    Serial.printf("[EMOTION] State: %s -> %s at %lums\n", prev_state == EMOTION_HAPPY ? "HAPPY" : "FOCUS", s_state == EMOTION_HAPPY ? "HAPPY" : "FOCUS", now);
#endif
  }
}

void emotion_set(EmotionState state) { s_state = state; s_frame = 0; draw_face(); }
EmotionState emotion_get() { return s_state; }
