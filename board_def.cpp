#include "board_def.h"

Arduino_DataBus *bus = new Arduino_ESP32QSPI(LCD_CS, LCD_SCLK, LCD_SDIO0, LCD_SDIO1, LCD_SDIO2, LCD_SDIO3);
Arduino_GFX *gfx = new Arduino_CO5300(bus, -1, 0, false, LCD_WIDTH, LCD_HEIGHT);

void gfx_init() {
  pinMode(BOOT_BTN_PIN, INPUT_PULLUP);
  if (!gfx->begin()) {
#if DEBUG_LOG
    Serial.println("[BOARD] gfx begin failed");
#endif
    return;
  }
  gfx->fillScreen(BLACK);
}

void board_log(const char *tag, const char *msg) {
#if DEBUG_LOG
  Serial.print("[");
  Serial.print(tag);
  Serial.print("] ");
  Serial.print(msg);
  Serial.print(" at ");
  Serial.print(millis());
  Serial.println("ms");
#else
  (void)tag;
  (void)msg;
#endif
}
