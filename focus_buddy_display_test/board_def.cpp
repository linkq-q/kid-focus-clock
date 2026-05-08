#include "board_def.h"

Arduino_DataBus *bus = new Arduino_ESP32QSPI(LCD_CS, LCD_SCLK, LCD_SDIO0, LCD_SDIO1, LCD_SDIO2, LCD_SDIO3);
Arduino_GFX *gfx = new Arduino_CO5300(bus, LCD_RESET /* RST */, 0 /* rotation */, LCD_WIDTH, LCD_HEIGHT, 6, 0, 0, 0);

void gfx_init() {
  pinMode(BOOT_BTN_PIN, INPUT_PULLUP);
  Wire.begin(IIC_SDA, IIC_SCL);
  if (!gfx->begin()) {
#if DEBUG_LOG
    Serial.println("[BOARD] gfx begin failed");
#endif
    return;
  }
  gfx->setBrightness(128);
  gfx->fillScreen(BLACK);
}

void gfx_display_test_loop() {
  static uint8_t phase = 0;
  uint16_t color = BLACK;
  const char *name = "BLACK";
  switch (phase) {
    case 0: color = RED; name = "RED"; break;
    case 1: color = GREEN; name = "GREEN"; break;
    case 2: color = BLUE; name = "BLUE"; break;
    case 3: color = WHITE; name = "WHITE"; break;
    default: color = BLACK; name = "BLACK"; break;
  }
  gfx->fillScreen(color);
#if DEBUG_LOG
  Serial.printf("[DISPLAY_TEST] %s\n", name);
#endif
  phase = (phase + 1) % 5;
  delay(1000);
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
